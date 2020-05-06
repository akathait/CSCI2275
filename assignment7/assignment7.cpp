	/* Anushka Kathait
	 * CSCI 2275 Fall 2019 Anand
	 * Assignment #7
	 */

	#include<iostream>
	#include<sstream>
	#include<fstream>
	#include<string>
	#include<vector>
	#include<stack>
	#include<queue>
	using namespace std;

	struct vertex;
	struct adjVertex;

	struct vertex{
		string name;
		bool visited;
		int distance;
		string path;
		vector<adjVertex> adjacency;
		vertex(string n){
			name = n;
			visited = false;
			distance = 0;
		}
	};

	struct adjVertex{
		vertex *v;
		string name;                                           //Professor Anand said it was okay for me to add this for the sake of cleanliness in my code.
	};

	class Graphville{
		vector<vertex> vertices;

	public:
		Graphville(string filename){
			ifstream inputfilestream;
			inputfilestream.open(filename);

			string input;
			string input2;

			while(getline(inputfilestream, input)){                         //first pass to load the vertex people
				string person;

				stringstream ss(input);
				getline(ss, person, '-');

				insertVertex(person);
			}

			inputfilestream.close();

			inputfilestream.open(filename);

			string line;
			while(getline(inputfilestream,line))                            //second pass to load people edges
			{
				if(line[line.size()-1]=='\r')
				{
					line = line.substr(0,line.size()-1);
				}
				stringstream ss(line);
				string name;
				getline(ss,name,'-');
				string next;
				while(getline(ss,next,','))
				{
					insertEdge(name,next);
				}
			}

			inputfilestream.close();
			mainMenu();
		}

		void mainMenu(){
				bool quit = false;
				while(quit == false){
					cout<<"\n"<<"====MAIN MENU===="<<endl;
					cout<<"1. Print list of people and their acquaintances"<<endl;
					cout<<"2. Print if people know each other"<<endl;
					cout<<"3. Print groups"<<endl;
					cout<<"4. Find the least number of introductions required" <<endl;
					cout<<"5. Quit"<<endl;

					string choice;
					cin>>choice;

					if(choice == "1"){
						printList();
					}
					else if(choice == "2"){
						printIfKnown();
					}
					else if(choice == "3"){
						printGroups();
					}
					else if(choice == "4"){
						printLeastNum();
					}
					else if(choice == "5"){
						cout << "Goodbye!" << endl;
						quit = true;
					}
					else{
						cout<<"Invalid choice.";
					}
				}
			}

			void insertVertex(string name){       //checks if the name already exists in the graph, if it doesn't, adds to the vector of people (vertices)
				for(int i = 0; i < vertices.size(); i++){
					if(vertices[i].name == name){
						return;
					}
				}
				vertex v(name);
				vertices.push_back(v);
			}

			void insertEdge(string person, string buddy){                    //finds the person in the people vector and establishes an edge by adding them to
				for(int i = 0; i < vertices.size(); i++){                    //the adjacency list
					if(vertices[i].name == person){
						for(int j = 0; j < vertices.size(); j++){
							if(vertices[j].name == buddy && i!=j){
								adjVertex temp;
								temp.v = &vertices[j];
								temp.name = buddy;
								vertices[i].adjacency.push_back(temp);
							}
						}
					}
				}
			}

			void printList(){
				for(int i = 0; i < vertices.size(); i++){
					cout<<vertices[i].name<<" - ";
					for(int j = 0; j < vertices[i].adjacency.size(); j++){
						cout<<vertices[i].adjacency[j].name<<", ";
					}
					cout<<endl;
				}
			}

			bool printIfKnown(){
				string person;
				string buddy;
				cout<<"Enter the names of two people: "<<endl;
				cin>>person;
				cin>>buddy;

				for(int i = 0; i < vertices.size(); i++){                     //looks through the person's adjacency list to see if the "buddy" exists in it
					if(vertices[i].name == person){                           //if so, they know each other
						for(int j = 0; j < vertices[i].adjacency.size(); i++){
							if(vertices[i].adjacency[j].name == buddy){
								cout<<"True"<<endl;
								return true;
							}
						}
					}
				}
				cout<<"False"<<endl;
				return false;
			}

			void printGroups(){                                //assuming the first is always the first in the file
				resetVisited();                                //uses a DFS to find groups of people who are connected in the graph
				stack<vertex> DFSstack;
				int groupID = 1;

				for(int i = 0; i < vertices.size(); i++){
					if(vertices[i].visited == false){          //if the person has not been checked yet, add to the stack
						vertices[i].visited = true;
						DFSstack.push(vertices[i]);

						cout<<"Group ID #"<<groupID<<endl;
						while(!DFSstack.empty()){              //check the adjacent people
							vertex dq = DFSstack.top();
							cout<<dq.name<<endl;
							DFSstack.pop();
							vector<adjVertex> adj = dq.adjacency;
							for(int i = 0; i < adj.size(); i++){
								if(adj[i].v->visited==false){
									adj[i].v->visited = true;
									DFSstack.push(*(adj[i].v));
								}
							}
						}

						groupID++;
					}
				}
			}

			void printLeastNum(){
				string p1;
				string p2;
				cout<<"Enter the names of two people: ";
				cin>>p1;
				cin>>p2;

				queue<vertex> BFSqueue;

				resetVisited();

				if(ifPathExists(p1,p2) == false){
					cout<<"No way to introduce them."<<endl;
					return;
				}

				resetVisited();

				for(int i=0;i<vertices.size();++i){                       //if the person we are looking for has been found, add them to the
					if(vertices[i].name == p1){                           //queue and update the parent path
						vertices[i].visited = true;
						vertices[i].path = vertices[i].name;
						BFSqueue.push(vertices[i]);
						break;
					}
				}

				while(!BFSqueue.empty()){
					vertex dq = BFSqueue.front();
					BFSqueue.pop();
					vector<adjVertex> adj = dq.adjacency;
					for(int i=0;i<adj.size();i++){
						if(adj[i].v->name == p2){                         //when the buddy has been found, print the path
							adj[i].v->path = dq.path + ", " + adj[i].v->name;
							cout<<adj[i].v->path<<endl;
							return;
						}
						if(adj[i].v->visited == false){
							adj[i].v->visited = true;                     //if the buddy is not found at this index, update the path and add to the queue
							adj[i].v->path = dq.path + ", " + adj[i].v->name;
							BFSqueue.push(*(adj[i].v));
						}
					}
				}
				resetVisited();
			}

			void resetVisited(){
				for(int i = 0; i < vertices.size(); i++){
					vertices[i].visited = false;
				}
			}

			bool ifPathExists(string person, string buddy){
				queue<vertex> pathQueue;
				for(int i=0;i<vertices.size();++i){
					if(vertices[i].name == person){
						if(person == buddy){
							return true;
						}
						vertices[i].visited = true;
						pathQueue.push(vertices[i]);
						break;
					}
				}

				while(!pathQueue.empty()){
					vertex dq = pathQueue.front();
					pathQueue.pop();
					vector<adjVertex> adj = dq.adjacency;
					for(int i=0;i<adj.size();++i){
						if(adj[i].v->name == buddy){
							return true;
						}

						if(adj[i].v->visited==false){
							adj[i].v->visited = true;
							pathQueue.push(*(adj[i].v));
						}
					}
				}

				return false;
			}
	};

	int main(int argc, char* argv[]){
		//string filename = argv[1];
		Graphville inst(argv[1]);
		//Graphville inst("people.txt");
	}


