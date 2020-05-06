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
		while(quit == false){
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
				getline(cin, fileName);
				//cin<<fileName;
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

		/*head->cityName = "LA";
		head->prev = NULL;
		head->next = tail;*/

		printNetwork();
	}

	void printNetwork(){
		if(head != NULL){
			cout<<"===CURRENT PATH==="<<endl;
			cout<<"NULL <- ";

			cityNode *tmp = head;
			while(tmp != NULL){
				cout<< tmp->cityName << " <-> ";
				tmp = tmp->next;
			}

			cout << tmp->cityName << " -> ";                        //check this line when testing in case something goes wrong...
			cout << "NULL" << endl;
			cout << "==================" << endl;
		}
		else{
			cout<<"There are no cities in the network. Have you built it yet?";
		}

	}

	void transmitMsg(string filename){                              //
		string x;
		string y;

		cout<<"Enter city x: "<<endl;
		cin>>x;
		cout<<"\n"<<"Enter city y: "<<endl;
		cin>>y;

		ifstream inputfilestream;
		inputfilestream.open(filename.c_str());
		string word;

		cityNode *iterator = head;
		//cityNode *startNode;
		//cityNode *stopNode;


		while(iterator != NULL){
			if(iterator->cityName == x){
				//startNode = iterator;
				break;
			}
			iterator = iterator->next;
		}

		//iterator = startNode;

		while(inputfilestream >> word){
			while(iterator != NULL){
				if(iterator->cityName == y){
					//stopNode = iterator;
					iterator->messageData = word;
					cout<<iterator->cityName<<" received "<<iterator->messageData<<endl;
					iterator->messageData = "";
					break;
				}
				else{
					iterator->messageData = word;
					cout<<iterator->cityName<<" received "<<iterator->messageData<<endl;
					iterator->messageData = "";
					iterator = iterator->next;
				}
			}

			//iterator = iterator->prev;

			//iterator = stopNode;

			while(iterator != NULL) {
				if(iterator->cityName == x){
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

	void addCity(string previousCity, string newCity){
		/*if(previousCity == "First"){
			cityNode *add = new cityNode();
			add->cityName = newCity;
			add->messageData = "";
			add->next = NULL;
			add->prev = NULL;

			if(head == NULL){
				head = add;
			}
			else{
				add->next->prev = add;
				head = add;
			}
		}
		else{
			cityNode *add = new cityNode();
			add->cityName = newCity;
			add->messageData = "";
			add->next = NULL;
			add->prev = NULL;

			cityNode *oneBefore = new cityNode();
			cityNode *iterator = head;
			while(iterator != NULL) {
				if(iterator->cityName == previousCity) {
					oneBefore = iterator;
					break;
			    }
			    iterator = iterator->next;
			}

			if(oneBefore == NULL){
				if(head == NULL){
					head = add;
				}
				add->next = head;
				head->prev = add;
				head = add;
			}
			else if(oneBefore->next == NULL){
				oneBefore->next = add;
				add->prev = oneBefore;
				tail = add;
			}
			else{
				oneBefore->next->prev = add;
				add->prev = oneBefore;
				add->next = oneBefore->next;
				oneBefore->next = add;
			}
		}*/




		cityNode *add = new cityNode();
		add->cityName = newCity;
		add->messageData = "";
		add->next = NULL;
		add->prev = NULL;

		cityNode *iterator = head;

		if(head != NULL){
			if(previousCity == "First"){
				cityNode *temp = new cityNode();
				temp = head;                                     //next city (was head, will become next spot)
				head = add;
				head->next = temp;                               //the added city points forward to what used to be head and backward to null
				head->prev = NULL;
			}
			else{
				while(iterator != NULL){
					if(iterator->cityName == previousCity){
						cityNode *temp = new cityNode();
						temp = iterator->next;                   //city after current

						iterator->next = add;
						add->prev = iterator;

						add->next = temp;
						temp->prev = add;                        //wrong

						break;
					}
					iterator = iterator->next;
				}
			}
		}
		else{                                                   //if head == null or if the linked list is empty
			head = add;
			tail = add;
		}
	}

	void deleteCity(string cityNameDelete){                //should also free memory for deleted city
		cityNode *del = new cityNode();

		//search and assign to del based on cityNameDelete

		if(del == tail){
			tail = tail->prev;
			tail->next = NULL;
			delete del;
		}
		else if(del == head) {
			head = head->next;
			head->prev = NULL;
			delete del;
		}
		else{
		    del->prev->next = del->next;
		    del->next->prev = del->prev;
		    delete del;
		}
	}

	void clearNetwork(){
		if(head != NULL){
			cityNode *temp = head;
			while(temp != NULL){
				cityNode *toBeDeleted= temp;
				temp = temp->next;
				delete toBeDeleted;
			}
			head = NULL;
		}
	}

	//INSERT DESTRUCTOR FOR COMMUNICATIONNETWORK HERE, CALL CLEARNETWORK()
};


int main(){
	CommunicationNetwork inst;
	inst.mainMenu();

	return 0;
}




