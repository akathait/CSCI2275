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

public:
	CommunicationNetwork(){
		head = NULL;
		tail = NULL;
	}

	void mainMenu(){
		bool quit = false;
		while(quit == false){                                  //enables the function to keep running until specified otherwise by entering "7"
			cout<<"\n"<<"====MAIN MENU===="<<endl;
			cout<<"1. Build Network"<<endl;
			cout<<"2. Print Network Path"<<endl;
			cout<<"3. Transmit Message from City X to City Y"<<endl;
			cout<<"4. Add City" <<endl;
			cout<<"5. Delete City"<<endl;
			cout<<"6. Clear Network"<<endl;
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
				string fileName;
				cout<<"Enter the name of the file you would like to open: "<<endl;
				cin>>fileName;
				transmitMsg(fileName);
			}
			else if(choice == "4"){
				string city;
				string prevCity;
				cout<<"Enter a City name: "<<endl;
				cin>>city;
				cout<<"Enter a previous City name: "<<endl;
				cin>>prevCity;

				addCity(prevCity,city);

				printNetwork();
			}
			else if(choice == "5"){
				string delCity;
				cout<<"Enter a city name:"<<endl;
				cin>>delCity;
				deleteCity(delCity);
			}
			else if(choice == "6"){
				clearNetwork();
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

	/* Open the file and transmit the message between all city x and y in the network word by word. Only one city can hold the
	 * message at a time; as soon as it is passed to the next city, it needs to be deleted from the sender city. Once the message
	 * reaches the city y of the network, it needs to be transmitted back the other direction to the city x of the network.  A word
	 * needs to be received back at city x from y  of the network before sending the next word.
	 */

	void transmitMsg(string filename){                                //Professor Anand said it was fine to change the parameter from
		string x;                                                     //a char to a string here
		string y;

		cin.clear();
		cin.ignore();
		cout<<"Enter city x:"<<endl;
		getline(cin, x);
		cout<<"Enter city y:"<<endl;
		getline(cin, y);                                              //specified in the problem statement's appendix

		ifstream inputfilestream;
		inputfilestream.open(filename.c_str());
		string word;

		cityNode *iterator = head;

		while(iterator != NULL){                                      //iterator is used to traverse the list, stopping when it finds city x
			if(iterator->cityName == x){
				break;
			}
			iterator = iterator->next;
		}

		while(inputfilestream >> word){                               //starting from iterator which starts at city x
			while(iterator != NULL){
				if(iterator->cityName == y){                          //if iterator has reached city y, break after printing again
					iterator->messageData = word;
					cout<<iterator->cityName<<" received "<<iterator->messageData<<endl;
					iterator->messageData = "";                       //clears the messageData for each node in the list
					break;
				}
				else{
					iterator->messageData = word;
					cout<<iterator->cityName<<" received "<<iterator->messageData<<endl;
					iterator->messageData = "";
					iterator = iterator->next;
				}
			}

			iterator = iterator->prev;

			while(iterator != NULL) {                                 //same as above but starting with city y, printing the linked list in
				if(iterator->cityName == x){                          //REVERSE, and breaking after city x is printed
					iterator->messageData = word;
					cout<<iterator->cityName<<" received "<<iterator->messageData<<endl;
					iterator->messageData = "";
					break;
				}
				else{
					iterator->messageData = word;
					cout<<iterator->cityName<<" received "<<iterator->messageData<<endl;
					iterator->messageData = "";
					iterator = iterator->prev;
				}
			}
		}

		inputfilestream.close();
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

	/* Find the city in the network where city name matches cityNameDelete. Change the next and previous pointers for the
	 * surrounding cities and free the memory. */
	void deleteCity(string cityNameDelete){
		cityNode *del = new cityNode();

		cityNode *iterator = head;                              //finds the spot/node of the city to delete
		while(iterator != NULL){
			if(iterator->cityName == cityNameDelete){
				del = iterator;
				break;
			}
		}

		if(del == tail){                                        //changes pointers to "go around" the node to be deleted, then deletes this node
			tail = tail->prev;
			tail->next = NULL;
			delete del;
		}
		else if(del == head){
			head = head->next;
			head->prev = NULL;
			delete del;
		}
		else{
			del->prev->next = del->next;
			del->next->prev = del->prev;
			delete del;
		}

		printNetwork();
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

	~CommunicationNetwork(){
		clearNetwork();
	}
};


int main(){
	CommunicationNetwork inst;
	inst.mainMenu();

	return 0;
}
