/*
 * Anushka Kathait
 * CSCI 2275 Fall 2019 Anand
 * Assignment #1
 */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

struct item{                                                    //makes a struct "item" with members type, status, and price
	string type;
	string status;
	int price = -1;
};

int findASaleMatch(item inputArray[], item wanted){             //finds a match for the wanted item provided in the main function
	int matchIndex = -1;
	int price = -1;
	for(int i = 0; i < 101; i++){
		if(inputArray[i].price == -1){                          //if the spot passed does not have a value from the items list, break
			break;
		}
		if(inputArray[i].status == " for sale"){                //checks to make sure the item is for sale and of the same type as
			if(inputArray[i].type == wanted.type){              //the wanted item, loops through to find the highest price and prints
				if(inputArray[i].price <= wanted.price){        //the spot in the array where the highest price is found
					if(inputArray[i].price > price){
						matchIndex = i;
						price = inputArray[i].price;
					}
				}
			}
		}
	}
	return matchIndex;
}

void maxProfit(item inputArray[]){           //loop to find max profit made by the seller by summing the prices in the array
	int total = 0;
	for(int i = 0; i < 101; i++){
		if(inputArray[i].status == " for sale"){
			total += inputArray[i].price;
		}
	}
	cout<<"maximum profit: ";
	cout<<total<<endl;
}

int main(){
	ifstream inputfilestream;
	inputfilestream.open("Items.txt");

	if(!inputfilestream.is_open()){
		cout<<"There was an error reading this file."<<endl;
		return 0;
	}

	string inputLine;
	item itemArray[101];
	stringstream ss;
	int i = 0;
	itemArray[100].price = -1;                                  //sets the last spot in the array to a dummy value to handle if
                                                                //deletion makes the index go one too far at the end
	while(getline(inputfilestream, inputLine)){
		string type;
		string status;
		string price;

		stringstream ss(inputLine);            //loads the contents of each line into type, status, and price based on delimiter ","
		getline(ss, type, ',');
		getline(ss, status,',');
		getline(ss, price);

		int intPrice = stoi(price);            //converts price to an int since that is what its type is in the struct

		itemArray[i].type = type;
		itemArray[i].status = status;
		itemArray[i].price = intPrice;

		i++;
	}

	inputfilestream.close();

	for(int i = 0; i < 100; i++){
		if(itemArray[i].price == -1){
			break;
		}
		if(itemArray[i].status == " wanted"){
			int indexMatch = findASaleMatch(itemArray,itemArray[i]);                  //calls function outlined above
			if(indexMatch == -1){
				cout<<"Match not found"<<endl;
				cout<<itemArray[i].type<<" "<<itemArray[i].price<<endl;
			}
			else{
				cout<<itemArray[i].type<<" "<<itemArray[indexMatch].price<<endl;

				for(int j = i; j < 100; j++){                                 //professor anand helped me with this logic:
					itemArray[j] = itemArray[j+1];                            //shifts the array starting at i (the spot where the item wanted is)
				}
				i--;											      	      //reduces i because of the shift in the array so no spot is skipped
				for(int k = indexMatch; k < 100; k++){
					itemArray[k] = itemArray[k+1];                            //shifts the array agains starting at the SaleMatch index for sale item
				}
				if(indexMatch < i){                                           //if the for sale item is found before the wanted item,
					i--;                                                      //decrease the counter again (or else there would be skips)
				}
			}
		}
	}

	maxProfit(itemArray);                                  //call to find the profit made by the seller

	return 0;
}


