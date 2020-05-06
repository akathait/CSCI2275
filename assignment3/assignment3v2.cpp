/*
 * Anushka Kathait
 * CSCI 2275 Fall 2019 Anand
 * Assignment #3
 */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct wordItem{
	string word;
	int count;                         //how many times each word shows up in the text
};

class WordAnalysis{
public:
	int n;                             //how many words you want for topN and bottomN parameters
	int size;						   //current size of uniqueWords array
	int wordsAdded;                    //how many unique wordItems have been added to the array
	int doubled;                       //how many times the array has been doubled
	int totalWords;                    //how many words exist in the file provided
	wordItem *uniqueWords;
	string stopWords[50];

	WordAnalysis(){
		n = 0;
		size = 100;
		wordsAdded = 0;
		doubled = 0;

		uniqueWords = new wordItem[size];
	}

	void makeWordsArr(string file){                           //constructs array of strings from the Hunger Games file, taking this file as input
		ifstream inputfilestream;
		inputfilestream.open(file.c_str());
		string word;
		while(inputfilestream >> word){                       //>> operator separates on spaces
			addWord(word);
		}
		inputfilestream.close();

	}

	void makeStopArr(string file){                            //constructs array of words to ignore from the ignore words file, taking this file's name as input
		ifstream inputfilestream;
		inputfilestream.open(file.c_str());
		string word;
		int i = 0;
		while(inputfilestream >> word){
			stopWords[i] = word;
			i++;
		}
		inputfilestream.close();
	}

	void weSortin(){                                        //using bubble/swapping sort if the previous word's count is less than the next's
		for(int i = 0; i < size-1; i++) {                   //method called in main()
			for(int j = 0; j < size-1-i; j++) {
				if (uniqueWords[j].count < uniqueWords[j + 1].count) {
					wordItem temp = uniqueWords[j+1];
		            uniqueWords[j+1] = uniqueWords[j];
		            uniqueWords[j] = temp;
		        }
		    }
		}
	}

	bool isStopWord(string word){                            //using the stopWords[] array, this function returns whether a given word is a stop word or not
		for(int i = 0; i < 50; i++){                         //size of stopWords array is always 50
			if(stopWords[i]==word){
				return true;
			}
		}
		return false;
	}

	void printTopN(int topN){                                //since the array is sorted in descending order, this method just outputs the first n requested for the n most frequent words
		for(int i = 0; i < topN; i++){
			cout<<uniqueWords[i].count << "-" << uniqueWords[i].word << endl;
		}
	}

	void printBottomN(int bottomN){                        	 //same as above, but the last n are produced
		int end = size;                                      //this method will output any of the unique words with only one occurrence in the file
		int i = 0;

		while(i <= bottomN){
			if(uniqueWords[end-1].word != ""){
				cout<<uniqueWords[end-1].count << "-" << uniqueWords[i].word << endl;
				i++;
			}
			end--;
		}
	}

	int searchCount(string words){                //takes the words provided and splits on commas to then print the counts of the requested words
		string wordsArr[10];                      //change later but for now it only takes ten words separated by commas
		int spot = 0;

		for(int i = 0; i < words.length() - 1; i++){
			if(words.at(i) ==','){
				wordsArr[spot] = words.substr(0,i);
				words.erase(0,i+1);
			}
			spot++;
		}

		for(int i = 0; i < 10; i++){
			for(int j = 0; j < size; j++){        //exits this loop and looks for the next word in wordArr's match if current word's match is found
				if(wordsArr[i] != ""){
					if(uniqueWords[j].word == wordsArr[i]){                   //checks the entire word stored in the spot for uniqueWords for a match
						cout<<uniqueWords[j].word<<" - "<<uniqueWords[j].count<<endl;
						break;
					}
				}
			}
			return -1;
		}
		return 0;
	}
	//this method adds the given word to the uniqueWords array if they are unique or increases the count of the word if it is not unique
	void addWord(string word){                                      //Professor Anand recommended keeping count of words added to the array
		if(wordsAdded == size){                                     //to check if the array is now full
			size = size*2;
			wordItem *temp = new wordItem[size];

			for (int i = 0; i < size/2; i++){
				temp[i] = uniqueWords[i];
			}

			delete[] uniqueWords;

			uniqueWords = temp;
			doubled++;
		}

		if(isStopWord(word) == false){
			int loc = findLoc(word);
			if(loc != -1) {
				uniqueWords[loc].count++;                  //if word is already present in uniqueWords, just up the count of the word
				totalWords++;
			}
			else{							 			   //if word is unique, add it to uniqueWords
				uniqueWords[wordsAdded].word = word;
				uniqueWords[wordsAdded].count++;
				wordsAdded++;                              //only increases this counter if the word is unique
				totalWords++;
			}
		}
	}

	int findLoc(string word){                              //finds if the word is already in the uniqueWords array for the above method
		for(int i = 0; i < size; i++) {
			if(uniqueWords[i].word == word) {
				return i;
		    }
		}
		return -1;
	}
};


int main(){
	WordAnalysis ins;
	//ins = new WordAnalysis();

	int n;
	string wordFile;
	string stopFile;
	string returnCountWords;

	cin>> n >> wordFile >> stopFile >> returnCountWords;          //takes input from the user in the order specified in the problem statement

	ins.makeStopArr(stopFile);
	ins.makeWordsArr(wordFile);

	ins.weSortin();

	ins.printTopN(n);
	cout<<"#"<<endl;
	ins.printBottomN(n);
	cout<<"#"<<endl;
	cout<<"Array Doubled: "<<ins.doubled<<endl;
	cout<<"#"<<endl;
	cout<<"Unique non-common words: " << ins.wordsAdded <<endl;
	cout<<"#"<<endl;
	cout<<"Total number of non-common words: " << ins.totalWords <<endl; 
	cout<<"#"<<endl;
	ins.searchCount(returnCountWords);

}

//All methods are functional and are producing the correct output according to the provided test case except my .searchCount() prints.
















//deleted bc I didn't realize that we had to sort our list
/*string returnWords[topN];

		for(int i = 0; i < topN; i++){
			int highestCount = -1;
			int mostFrequentIndex = -1;
			for(int j = 0; j < size; j++){
				if(uniqueWords[j].count > highestCount){
					highestCount = uniqueWords[j].count;
					mostFrequentIndex = j;
				}
			}
			returnWords[i] = uniqueWords[mostFrequentIndex].word;
			uniqueWords[mostFrequentIndex].count = -1;
		}

		for(int i = 0; i < topN; i++){
			cout<<returnWords[i]<<endl;
		}
		*/
