#include <iostream>
using namespace std;

int count_vowel(char *str){
	int count = 0;
	while(*str != '\0'){
		if(*str == 'a'){
			count++;
		}
		(*str)++;
	}
	return count;
}

int main(){
	char str[] = "datastructuresandprogramming";
	cout<<"Numbers of Vowel in "<<str<<" is"<<endl;
	cout<<count_vowel(str)<<endl;
	return 0;
}
