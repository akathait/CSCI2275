#include<iostream>
using namespace std; 
  
// Hash table size 
#define TABLE_SIZE 13 
  
  
class DoubleHash 
{ 
    int *hashTable; 
    int curr_size; 
  
public: 
  
    // function to check if hash table is full 
    DoubleHash() 
    { 
        hashTable = new int[TABLE_SIZE]; 
        curr_size = 0; 
        for (int i=0; i<TABLE_SIZE; i++) 
            hashTable[i] = -1; 
    } 
    bool isFull() 
    { 
        return (curr_size == TABLE_SIZE); 
    } 
  
    // function to calculate first hash 
    int hash1(int key) 
    { 
    	return key % TABLE_SIZE;
    } 
  
    // function to calculate second hash 
    int hash2(int key) 
    { 
    	return 29-(key%29);
    } 
  
    
  
    // function to insert key into hash table 
    void insertHash(int key) 
    { 
    	int i = 1;

    	if(hashTable[hash1(key)] != -1){                               //if occupied
    		int new_index;
    		new_index = (hash1(key) + i*hash2(key))%TABLE_SIZE;

    		while(new_index != -1){
    			i++;
    			new_index = (hash1(key) + i*hash2(key))%TABLE_SIZE;
    		}

    		hashTable[new_index] = key;
    		return;
    	}
    	else{                                                           //if not occupied
    		hashTable[hash1(key)] = key;
    	}
        
        curr_size++;//this should be the last line of the function 
    } 
  
    // function to display the hash table 
    void displayHash() 
    { 
        for (int i = 0; i < TABLE_SIZE; i++) 
        { 
            if (hashTable[i] != -1) 
                cout << i << " --> "
                     << hashTable[i] << endl; 
            else
                cout << i << endl; 
        } 
    } 
}; 
  
// Driver's code 
int main() 
{ 
    int a[] = {19, 27, 36, 10, 64}; 
    int n = sizeof(a)/sizeof(a[0]); 
  
    // inserting keys into hash table 
    DoubleHash h; 
    for (int i = 0; i < n; i++) 
        h.insertHash(a[i]); 
  
    // display the hash Table 
    h.displayHash(); 
    return 0; 
} 
