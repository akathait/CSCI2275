#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Book{                                                //parent class book
	string name;
	string genre;
	int rating;

	public:
		Book(){
			this->name = "none provided";                  //default values
			this->genre = "none provided";
			this->rating = -1;
		};

		void setName(string name){
			this->name = name;
		}

		string getName(){
			return name;
		}

		void setGenre(string genre){
			this->genre = genre;
		}

		string getGenre(){
			return genre;
		}

		void setRating(int rating){
			this->rating = rating;
		}

		int getRating(){
			return rating;
		}

};

class Fiction: public Book{                            //class Fiction extends Book and inherits other attributes of a book (name, genre, rating)
	string id;

	public:
		Fiction(){

		};

		void setFictionId(string id){
			this->id = id;
		}

		string getFictionId(){
			return id;
		}

};

class Poetry: public Book{
	int id;

	public:
		Poetry(){
			this->id = -1;
		};

		void setPoetryId(int id){
			this->id = id;
		}

		int getPoetryId(){
			return id;
		}
};

class Horror: public Book{
	float id;

	public:
		Horror(){
			this->id = -1;
		};

		void setHorrorId(float id){
			this->id = id;
		}

		float getHorrorId(){
			return id;
		}

};

int main(){
	ifstream inputfilestream;                                         //takes input from file book.txt
	inputfilestream.open("book.txt");

	if(!inputfilestream.is_open()){
		cout<<"There was an error reading this file."<<endl;
		return 0;
	}

	string input;
	stringstream ss;
	Horror horrorArr[100];                                             //creates initial arrays for unsorted input from file
	Poetry poetryArr[100];
	Fiction fictionArr[100];

	int hi = 0;                                                        //Professor Anand helped with this:
	int pi = 0;                                                        //MUST be outside while loop bc would then reset to zero every time
	int fi = 0;

	while(getline(inputfilestream, input)){
		string name;
		string id;
		string genre;
		string rating;

		stringstream ss(input);
		getline(ss, name, ',');
		getline(ss, id, ',');
		getline(ss, genre, ',');
		getline(ss, rating);

		int intRating = stoi(rating);


		if(genre == "horror"){                             //takes genre to sort into respective array
			float hid = stof(id);
			Horror b;
			b.setHorrorId(hid);
			b.setName(name);
			b.setGenre(genre);
			b.setRating(intRating);
			horrorArr[hi] = b;
			hi++;

		}
		else if(genre == "poetry"){
			int hid = stoi(id);
			Poetry b;
			b.setPoetryId(hid);
			b.setName(name);
			b.setGenre(genre);
			b.setRating(intRating);
			poetryArr[pi] = b;
			pi++;
		}
		else{                                              //if the genre is fiction
			Fiction b;
			b.setFictionId(id);
			b.setName(name);
			b.setGenre(genre);
			b.setRating(intRating);
			fictionArr[fi] = b;
			fi++;;
		}
	}

	Horror sortH[100];                                      //to sort the above horror, poetry, and fiction arrays into
	Poetry sortP[100];
	Fiction sortF[100];

	int highest1 = -1;
	int highestIndex1 = -1;

	for(int i = 0; i < 100; i++){
		highest1 = -1;
		for(int j = 0; j < 100; j++){
			if(horrorArr[j].getRating() > highest1){            //if the rating is higher than the last, it is the new highest
				highest1 = horrorArr[j].getRating();
				highestIndex1 = j;
			}
		}
		if(highest1!=-1){
			sortH[i] = horrorArr[highestIndex1];                //load highest into the first spot of the array, then change rating so it isn't repeated as the highest
			horrorArr[highestIndex1].setRating(-1);
		}
	}

	int highest2 = -1;
	int highestIndex2 = -1;

	for(int i = 0; i < 100; i++){                               //repeat of above
		highest2 = -1;
		for(int j = 0; j < 100; j++){
			if(poetryArr[j].getRating() > highest2){
				highest2 = poetryArr[j].getRating();
				highestIndex2 = j;
			}
		}
			if(highest2!=-1){
				sortP[i] = poetryArr[highestIndex2];
				poetryArr[highestIndex2].setRating(-1);
			}
	}

	int highest3 = -1;
	int highestIndex3 = -1;

	for(int i = 0; i < 100; i++){                               //repeat of above
		highest3 = -1;
		for(int j = 0; j < 100; j++){
			if(fictionArr[j].getRating() > highest3){
				highest3 = fictionArr[j].getRating();
				highestIndex3 = j;
			}
		}
			if(highest3!=-1)
			{
				sortF[i] = fictionArr[highestIndex3];
				fictionArr[highestIndex3].setRating(-1);
			}
	}


	cout<<"Top 10 for Genre Fiction are:"<<endl;              //printing out first ten of sorted array
	for(int i = 0; i < 10; i++){
		cout<<sortF[i].getName()<<endl;
	}

	cout<<"Top 10 for Genre Poetry are:"<<endl;
	for(int i = 0; i < 10; i++){
		cout<<sortP[i].getName()<<endl;
	}

	cout<<"Top 10 for Genre Horror are:"<<endl;
	for(int i = 0; i < 10; i++){
		cout<<sortH[i].getName()<<endl;
	}

	cout<<"Top 10 for all the genres are:"<<endl;
	int count = 0;
	 hi = 0;
	 pi = 0;
	 fi = 0;

	while (count < 10){                                                    //runs ten times, compares the ratings for the highest of the three types, and ups the counter for the array with the highest rating
		if(sortH[hi].getRating() > sortP[pi].getRating()){
			if(sortH[hi].getRating() > sortF[fi].getRating()){             //if H is bigger than P and F
				cout<<sortH[hi].getName()<<endl;
				hi++;
			}
			else{                                                          //if F is bigger than P and H
				cout<<sortF[fi].getName()<<endl;
				fi++;
			}
		}
		else{                                                              //if P is bigger than H
			if(sortP[pi].getRating() > sortF[fi].getRating()){             //if P is bigger than F and H
				cout<<sortP[pi].getName()<<endl;
				pi++;
			}
			else{                                                          //if F is bigger than P and H
				cout<<sortF[fi].getName()<<endl;
				fi++;
			}
		}
		count++;
	}
	return 0;
}




	/*	string outputArr[5];
		int highest = -1;
		int highestIndex = 0;
		for (int i = 0; i <= 5; i++){
			for(int j = 0; j <= (sizeof(allArr)/sizeof(*allArr)); j++){
				if(allArr[j].getRating() > highest){
					highest = allArr[j].getRating();
					highestIndex = j;
					outputArr[i] = allArr[j].getName();                                 //while runs ten times, for i from 0 to 10 for fic and the rest,
				}
			}
			allArr[highestIndex].setRating(-1);
		}

		cout<<"Top 10 for all the genres are:"<<endl;
		cout<<outputArr[0]<<endl;
		cout<<outputArr[1]<<endl;
		cout<<outputArr[2]<<endl;
		cout<<outputArr[3]<<endl;
		cout<<outputArr[4]<<endl;*/

