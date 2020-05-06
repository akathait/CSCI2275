/*
 * Anushka Kathait
 * CSCI 2275 Fall 2019 Anand
 * Assignment #3
 *
 *
 *	aight so plan:
 *		store unique words found in file in dynamically allocated array and output the info outlined in problem statement
 *		fill in methods of the class
 *		formatted output (count for each word, how many times array was doubled, unique non-common words, total non-common words, search words count
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct wordItem{
	string word;
	int count;                                                        //how many times each word shows up
};

class WordAnalysis{
	wordItem *uniqueWords = new wordItem[size];
	string stopWords[50];                                              //should be fifty
	int size = 100;
	int wordsAdded;
	int doubled;

public:
	WordAnalysis(wordItem uniqueWords[], string stopWords[]){
		this->uniqueWords = uniqueWords;
		this->stopWords = stopWords;
		size = 100;
		wordsAdded = 0;
	}

	bool isStopWord(string word){
		for(int i = 0; i < size; i++){
			if(stopWords[i]==word){
				return true;
			}
		}
		return false;

	}

	void printTopN(int topN){                                           //param is how many words you want to print
		string returnWords[topN];

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
	}

	void printBottomN(int bottomN){
		string returnWords[bottomN];

		for(int i = 0; i < bottomN; i++){
			int lowestCount = numeric_limits<int>::max();
			int leastFrequentIndex = -1;
			for(int j = 0; j < size; j++){
				if(uniqueWords[j].count < lowestCount){
					lowestCount = uniqueWords[j].count;
					leastFrequentIndex = j;
				}
			}
			returnWords[i] = uniqueWords[leastFrequentIndex].word;
			uniqueWords[leastFrequentIndex].count = -1;
		}

		for(int i = 0; i < bottomN; i++){
			cout<<returnWords[i]<<endl;
		}
	}

	int searchCount(string word, wordItem wordItemList){                   //wait does this need to assign to wordItem counts too
		int count = 0;
		for(int i = 0; i < (sizeof(wordItemList)/sizeof(*wordItemList)); i++){
			if(wordItemList[i] == word){

			}
		}
		if(){
			return count;
		}
		return -1;
	}

	void addWord(string word){                                    //in sorted location?            //sort at end, make sort method
		if(wordsAdded == size){
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
			uniqueWords[wordsAdded].word = word;
			uniqueWords[wordsAdded].count++;
			wordsAdded++;
	}
};


int main(){
	ifstream inputfilestream2;
	string openStopWords;
	cin>>openStopWords;

	inputfilestream2.open(openStopWords);
	if(!inputfilestream2.is_open()){
		cout<<"There was an error reading this file."<<endl;
		return 0;
	}

	string input;
	stringstream ss;
	string stopWordsArr[50];
	int spot = 0;

	while(getline(inputfilestream2, input)){
		string stopWord;
		stringstream ss(input);

		while(getline(ss, stopWord)){
			stopWordsArr[spot] = stopWord;
			spot++;
		}
	}

	ifstream inputfilestream;
	string openThis;
	cin>>openThis;
	inputfilestream.open(openThis);

	if(!inputfilestream.is_open()){
		cout<<"There was an error reading this file."<<endl;
		return 0;
	}

	wordItem fileWordsArr[100];
	string input;
	stringstream ss;

	WordAnalysis ins;
	ins = new WordAnalysis(fileWordsArr, stopWordsArr);

	while(getline(inputfilestream, input)){///////while within for more words
		string word;

		stringstream ss(input);
		getline(ss, word, ' ');

		ins.addWord(word);
	}

	/*cout<<numCount<<” – “<<word<<endl; 
	cout<<”#”<<endl; 
	cout<<”Array doubled: “<<numDoublings<<endl; 
	cout<<”#”<<endl; 
	cout<<”Unique non-common words: “<<numUniqueWords<<endl; 
	cout<<word<<” - ”<<count<<endl; 
	*/
}




