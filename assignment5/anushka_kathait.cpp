/*
 * Anushka Kathait
 * CSCI 2275 Fall 2019 Anand
 * Assignment #5
 */

#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;

struct cityNode{
	string cityName;
	string messageData;
	cityNode *next;
	cityNode *prev;
};

class CommunicationNetwork{
	cityNode *head, *tail;
	string * tempFileArray, *queueArray;     //the former array is for temporary storage of the file's words, the latter for the buffered messages
	int queueSize, front, rear;              //size of the queue, the front of the queue's index, and the end of the queue's index/current index

public:
	CommunicationNetwork(){
		head = NULL;
		tail = NULL;

		queueSize = 10;
		tempFileArray = new string[50];
		queueArray = new string[queueSize];
		front = -1;
		rear = -1;
	}

	void mainMenu(){
		ifstream inputfilestream;
		string openThis;
		cout<<"What file would you like to load?: "<<endl;
		cin>>openThis;

		inputfilestream.open(openThis);
		string word;

		int i = 0;

		while(inputfilestream >> word){                       //loads ALL the contents of the input file into the temporary array
			tempFileArray[i] = word;                          //each index is a separate word from the file
			i++;
		}

		inputfilestream.close();

		int c = 0;

		bool quit = false;
		while(quit == false){                                 //enables the function to keep running until specified otherwise by entering "7"
			cout<<"\n"<<"====MAIN MENU===="<<endl;
			cout<<"1. Build Network"<<endl;
			cout<<"2. Print Network Path"<<endl;
			cout<<"3. Enqueue"<<endl;
			cout<<"4. Dequeue" <<endl;
			cout<<"5. Peek Queue"<<endl;
			cout<<"6. Empty Queue"<<endl;
			cout<<"7. Quit"<<endl;

			string choice;
			cin>>choice;

			if(choice == "1"){
				buildNetwork();
			}
			else if(choice == "2"){
				printNetwork();
			}
			else if(choice == "3"){
				enqueue(tempFileArray[c]);                    //enqueues one at a time from the front
				c++;
			}
			else if(choice == "4"){
				dequeue();
			}
			else if(choice == "5"){
				peekQueue();
			}
			else if(choice == "6"){
				emptyQueue();
			}
			else if(choice == "7"){
				cout << "Goodbye!" << endl;
				quit = true;
			}
			else{
				cout<<"Invalid choice.";
			}
		}
	}

	//methods from assignment 4 start here

	/* Build the initial network from the cities given in this writeup. The cities can be fixed in the function, you do not need to write
	   the function to work with any list of cities. */
	void buildNetwork(){
		addCity("First", "Los Angeles");
		addCity("Los Angeles", "Phoenix");
		addCity("Phoenix", "Denver");
		addCity("Denver", "Dallas");
		addCity("Dallas", "St. Louis");
		addCity("St. Louis", "Chicago");
		addCity("Chicago", "Atlanta");
		addCity("Atlanta", "Washington, D.C.");
		addCity("Washington, D.C.", "New York");
		addCity("New York", "Boston");

		printNetwork();
	}


	/*Start at the head of the linked list and print the name of each city in order to the end of the list. */
	void printNetwork(){
		if(head != NULL){
			cout<<"===CURRENT PATH==="<<endl;
			cout<<"NULL <- ";

			cityNode *tmp = head;
			while(tmp != NULL){
				cout<< tmp->cityName << " <-> ";
				tmp = tmp->next;
			}

			cout << "NULL" << endl;
			cout << "==================" << endl;
		}
		else{
			cout<<"There are no cities in the network. Have you built it yet?";               //if the list is empty/head == NULL
		}

	}

	void transmitMsg(string word){
		if(head == NULL){
			cout<<"Build a network before attempting to transmit a message." << endl;

		}
		else{
			cityNode *iterator = head;

			while(iterator->next != NULL){
				iterator->next->messageData = word;
				cout<<iterator->next->cityName<<" received "<<iterator->next->messageData<<endl;
				iterator->next->messageData = "";
				iterator = iterator->next;
			}

			//iterator = iterator->prev;

			while(iterator->prev != NULL) {
				iterator->prev->messageData = word;
				cout<<iterator->prev->cityName<<" received "<<iterator->prev->messageData<<endl;
				iterator->prev->messageData = "";
				iterator = iterator->prev;
			}
		}
	}

	/*Insert a new city into the linked list after the previousCity. The name of the new city is in the argument newCity.*/
	void addCity(string previousCity, string newCity){
		cityNode *add = new cityNode();
		add->cityName = newCity;
		add->messageData = "";
		add->next = NULL;
		add->prev = NULL;

		cityNode *iterator = head;                               //start traversing from head

		if(head != NULL){
			if(previousCity == "First"){
				cityNode *temp = new cityNode();
				temp = head;                                     //next city was head and will become the next spot/node in the list
				head = add;
				head->next = temp;                               //the added city points forward to what used to be head and backward to
				head->prev = NULL;                               //null because it is now the head of the list
			}
			else{
				while(iterator != NULL){
					if(iterator->cityName == previousCity){      //once the city the new city is supposed to go after is found, place it after
						cityNode *next = iterator->next;         //where the iterator is and adjust the pointers
						iterator->next = add;
						add->prev = iterator;
						add->next = next;
					}
					iterator = iterator->next;
				}
			}
		}
		else{                                                   //if head == null/if the linked list is empty
			head = add;
			tail = add;
		}
	}

	/* Delete all cities in the network, starting at the head city.*/
	void clearNetwork(){
		if(head != NULL){
			cityNode *temp = head;
			while(temp != NULL){
				cityNode *toBeDeleted= temp;
				temp = temp->next;
				cout<<"deleting "<<toBeDeleted->cityName<<endl;
				delete toBeDeleted;
			}
			head = NULL;
		}
	}

	//methods unique to this assignment begin here!

	void enqueue(string word){                                    //adds elements/words from the file to the end of the queueArray queue
		if(word == ""){                                           //empty strings exist after the indices with words have been loaded into the array
			cout << "No more words to queue." << endl;
		}
		else{
			if(rear == queueSize-1){                              //when the queue is full, begin array doubling
				queueSize = queueSize*2;
				string *temp = new string[queueSize];

				for (int i = 0; i < queueSize/2; i++){
					temp[i] = queueArray[i];
				}

				delete[] queueArray;

				queueArray = temp;
			}

			if(rear == -1){                                        //if the queue is empty
				front = 0;
				rear = 0;
				queueArray[rear] = word;
			}
			else{                                                  //if not empty, append to the end of the queue
				rear++;
				queueArray[rear] = word;
			}

			cout<<"Enqueued: "<< queueArray[rear]<<endl;
			cout<<"queueFront: "<<front<<endl;
			cout<<"queueRear: "<<rear<<endl;
		}
	}

	void dequeue(){
		if(front == -1 || front > rear){                           //both of these conditions indicate that the queue is empty (the beginning condition v. when the user calls dequeue to the point that the queue empties)
			cout<<"Queue Underflow."<<endl;
		}
		else{
			peekQueue();

			string word = queueArray[front];
			front++;

			transmitMsg(word);

			cout<<"queueFront: <"<<front<<">"<<endl;
			cout<<"queueRear: <"<<rear<<">"<<endl;
		}
	}

	void peekQueue(){
		if(front == -1 || front > rear){                            //same reasoning as above
			cout<<"Queue Underflow."<<endl;
		}
		else{
			cout<< "Peeked Word: "<<queueArray[front]<<endl;        //peek in queues looks at the first element (FIFO)
		}

	}

	void emptyQueue(){
		if(front == -1 || front > rear){            //clarification from Professor Anand: keep going with with the original buffered queue
			cout<<"Queue Underflow."<<endl;         //instead of making a new one to start again from "A liger..."--it would start from "it's"
		}                                           //after emptying the queue
		else{
			int spot = front;                       //starts at front and not 0 because we only want the words that haven't been dequeued already

			while(queueArray[spot] != ""){
				transmitMsg(queueArray[spot]);
				spot++;
			}

			while(front != rear){                   //bc when front = rear, we know that the list is empty
				dequeue();
			}

			front = -1;
			rear = -1;
		}
	}

	~CommunicationNetwork(){
		clearNetwork();
	}
};


int main(){
	CommunicationNetwork inst;
	inst.mainMenu();

	return 0;
}


