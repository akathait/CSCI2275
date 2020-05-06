#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct MovieLLNode{
	int imdb_ranking;
	string title;
	int year_released;
	int quantity;
	MovieLLNode *next;
	//this is constructor
	MovieLLNode(){};
	MovieLLNode(int ranking, string title, int year_released, int quantity){
		this->imdb_ranking = ranking;
		this->title = title;
		this->year_released = year_released;
		this->quantity = quantity;
		this->next = NULL;
	}
};

struct MovieBSTNode{
	char MovieFirstLetter;
	MovieBSTNode *parent;
	MovieBSTNode *left;
	MovieBSTNode *right;
	//pointer to the head of the list of the movies starting with letter MovieFirstLetter
	MovieLLNode *head;
	//constructor
	MovieBSTNode(){};
	MovieBSTNode(char first_letter){
		this->MovieFirstLetter = first_letter;
		this->parent = NULL;
		this->left = NULL;
		this->right = NULL;
		this->head = NULL;
	}
};

class MovieTree{
public:
    MovieTree(string filename){         //changed because of the switch from argv to the filename as what is passed
    	root = NULL;
    	readFile(filename);             //changed ^^
    	//print menu
    	//call appropriate function depending on menu printed

    	bool quit = false;
    	while(quit == false){                                 //enables the function to keep running until specified otherwise by entering "7"
    		printMenu();

    		string choice;
    		cin>>choice;

    		if(choice == "1"){
    			cout<<"Enter title:"<<endl;
    			string title;
    			cin>>title;
    			findMovie(title);
    		}
 			else if(choice == "2"){
 				cout<<"Enter title:"<<endl;
 				string title;
 				cin>>title;
 				rentMovie(title);
   			}
 			else if(choice == "3"){
 				printMovieInventory();
   			}
   			else if(choice == "4"){
   				cout<<"Enter title:"<<endl;
   				string title;
   				cin>>title;
   				deleteMovieNode(title);
    		}
   			else if(choice == "5"){
   				int count = 0;
   				countMovieNodes(root, count);
   				cout<<count<<endl;
   			}
   			else if(choice == "6"){
    			cout << "Goodbye!" << endl;
    			quit = true;
    		}
    		else{
   				cout<<"Invalid choice.";
  			}
    	}
    }

    ~MovieTree(){};

    void printMovieInventory(){
    	//call private function printMovieInventory() with root of the node as parameter and do in-order traversal
    	printMovieInventory(root);
    }

    int countMovieNodes(){
    	//call private function countMovieNodes() with root and variable count=0
    	//(count is passed by refference see the private function definition)
    	int count = 0;
    	countMovieNodes(root, count);
    	return count;                                    //might be an issue, pass by reference?

    }

    void deleteMovieNode(std::string title){
    	//search the node starting with first letter of title
        //call the private function searchBST that returns the BST node
    	MovieBSTNode *i = searchBST(root, title);

        //call the private function searchLL to search in the LL attached to BST node found above
        //delete this LL node searched above
    	MovieLLNode *delMovieLL = searchLL(i->head, title);

        //if movie to be deleted is head of the LL, Delete BST node as well
        //NOTE: you are given nodes parent pointer too
    	if(delMovieLL == i->head && i->head->next == NULL){
    		delete delMovieLL;
    	}

    	//Depending on 3 conditions:
    	//when node has no child
    	if (i->left == NULL && i->right == NULL){
    		if(i != root){
    			if(i->parent->left == i){
    				i->parent->left = NULL;
    			}
    			else{
    				i->right->right = NULL;
    			}
    		}
    		else{
    			root = NULL;
    		}

    		delete i;
    	}
    	//when node has just 1 child
    	else if(i->left == NULL){
    		i->right->parent = i->parent;
    		if(i->parent == NULL){
    			root = i->right;
    			delete i;
    			return;
    		}
    	}
    	else if(i->right == NULL){
    		i->left->parent = i->parent;
    		if(i->parent == NULL){
    			root = i->left;
    			delete i;
    			return;
    		}
    	}
    	//when node has two children: you need to find in-order successor. Use function treeMinimum by passing node's right child
    	else if(i->left != NULL && i->right != NULL){
    		MovieBSTNode *successor = treeMinimum(i->right);
    		MovieBSTNode *val = successor;

    		deleteMovieNode(successor->head->title);

    		i = val;

    	}
    }

    void addMovieNode(int ranking, std::string title, int releaseYear, int quantity){
    	//    Create MovieNodeLL called newMovie to be added to its LL
    	MovieLLNode *newMovie = new MovieLLNode(ranking, title, releaseYear, quantity);
    	//    Create a BST called newIndex node to be added
    	MovieBSTNode *newIndex = new MovieBSTNode(title[0]);

    	MovieBSTNode *searched = searchBST(root,title);

    	//    If BST is empty, set newIndex as root and set newMovie as head
    	if(searched == NULL){
    		if(root == NULL){
    			root = newIndex;
    			root->head = newMovie;
    			root->head->next = NULL;
    			return;
    		}
    		else{                                                        //if a new node needs to be made bc not in tree already
    			MovieBSTNode *iteratorBST = searched;

    			if(iteratorBST != NULL){                                 //or if? yeah, if
    				if(newMovie->title < iteratorBST->head->title){      //if the movie title comes before the iterator's title
    					newMovie->next = iteratorBST->head;
    					iteratorBST->head = newMovie;
    				}
    				else{
    					MovieLLNode *iteratorLL = iteratorBST->head;

    					if(iteratorLL->next == NULL){
    						newMovie->next = iteratorLL->next;
    						iteratorLL->next = newMovie;
    						return;
    					}

    					while(iteratorLL->title <iteratorLL->next->title){
    						iteratorLL = iteratorLL->next;
    						if(iteratorLL->next == NULL){
    							break;
    						}
    					}

    					if(iteratorLL->next == NULL){
    						newMovie->next = iteratorLL->next;
    						iteratorLL->next = newMovie;
    						return;
    					}

    					newMovie->next = iteratorLL->next;
    					iteratorLL->next = newMovie;
    				}
    			}
    		}
    	}

    	MovieBSTNode *iteratorBST = root;
    	bool keepGoing = true;
    	if(iteratorBST == NULL){
    		while(keepGoing == true){
    			if(newIndex->MovieFirstLetter < iteratorBST->MovieFirstLetter){
    				if(iteratorBST->left == NULL){
    					newIndex->parent = iteratorBST;
    					iteratorBST->left = newIndex;
    					keepGoing = false;
    				}
    				iteratorBST = iteratorBST->left;
    			}
    			else{
    				if(iteratorBST->right == NULL){
    					newIndex->parent = iteratorBST;
    					iteratorBST->right = newIndex;
    					keepGoing = false;
    			    }
    				iteratorBST = iteratorBST->right;
    			}
    		}
    		newIndex->head = newMovie;
    	}

    	/*MovieLLNode *iteratorLL = newIndex->head;

    	    			while(iteratorLL != NULL){
    	    				if(newMovie->title < iteratorLL->title){
    	    					MovieLLNode *temp = new MovieLLNode();
    	    					temp = newIndex->head;
    	    					newIndex->head = newMovie;
    	    			   		newMovie->next = temp;
    	    			   		return;
    	    				}
    	    			   	else if(newMovie->title > iteratorLL->title and (newMovie->title < iteratorLL->next->title or iteratorLL->next == NULL)){
    	    			   		MovieLLNode *temp = new MovieLLNode();
    	    			   		temp = iteratorLL->next;
    	    			   		iteratorLL->next = newMovie;
    	    			   		newMovie->next = temp;
    	    			   		return;
    	    			   	}
    	    			   	iteratorLL = iteratorLL->next;
    	    			}*/


    	/*parent = iteratorBST;
    	    				if(iteratorBST->MovieFirstLetter < newIndex->MovieFirstLetter){
    	    					if(iteratorBST->right==NULL)
    	    					{
    	    						//insert newindex here
    	    						parent->right = newIndex;
    	    						parent->right->right = NULL;
    	    						newIndex->head = newMovie;
    	    						newIndex->head->next = NULL;
    	    						return;
    	    					}
    	    					iteratorBST = iteratorBST->right;
    	    				}
    	    				else{
    	    					if(iteratorBST->left==NULL)
    	    					{
    	    						//insert newIndex here
    	    						parent->left = newIndex;
    	    						parent->left->left = NULL;
    	    						newIndex->head = newMovie;
    	    						newIndex->head->next = NULL;
    	    						return;
    	    					}
    	    					iteratorBST = iteratorBST->left;
    	    				}
    	    				//iteratorBST = iteratorBST->next;
    	    			}
    	    		}
    	    	}
    	    	else{                                           //if the first letter index already exists in the tree
    	   			MovieLLNode *iteratorLL = searched->head;
    	   			if(newMovie->title < searched->head->title){
    	   				MovieLLNode *temp = new MovieLLNode();
    	   				temp = searched->head;
    	   			   	searched->head = newMovie;
    	   			   	newMovie->next = temp;
    	   			   	return;
    	   			}
    	   			while(iteratorLL != NULL){
    	   				if(newMovie->title > iteratorLL->title && (newMovie->title < iteratorLL->next->title || iteratorLL->next == NULL)){
    	   			    	MovieLLNode *temp = new MovieLLNode();
    	   			    	temp = iteratorLL->next;
    	   			    	iteratorLL->next = newMovie;
    	   			    	newMovie->next = temp;
    	   			    	return;
    	   			    }
    	   			    iteratorLL = iteratorLL->next;
    	   			}
    	    	}*/
    	//other attempts at this method at the end of the program
    }

    void findMovie(std::string title){
    	//BST search to find the node starting from the first letter of title
    	//then once you find BST node, traverse to the LL attached to it to find the node with title and display information
    	//if nothign is found print "Movie not found"]

    	MovieBSTNode *foundMovieBST = searchBST(root, title);
    	if(foundMovieBST == NULL){                                                //have to do it this way bc searchLL depends on foundMovieBST->head
    		cout<<"Movie not found."<<endl;
    		return;
    	}

		MovieLLNode *foundMovieLL = searchLL(foundMovieBST->head, title);
    	if(foundMovieLL == NULL){
    		cout<<"Movie not found."<<endl;
    		return;
    	}

		cout << "Movie Info:" << endl;
		cout << "===========" << endl;
		cout << "Ranking:" << foundMovieLL->imdb_ranking << endl;
		cout << "Title:" << foundMovieLL->title << endl;
		cout << "Year:" << foundMovieLL->year_released << endl;
		cout << "Quantity:" << foundMovieLL->quantity << endl;

    }

    void rentMovie(std::string title){                               //going to need to change for movie not found scenario sooooo yeah
    	//Find node in BST for the first letter of title
    	//If no node found in BST print "Movie Not Found."
    	MovieBSTNode *rentBST = searchBST(root, title);

    	//if BST index is found, search for the movie title in the LL pointed by BST node
    	if(rentBST == NULL){
    		cout<<"Movie not found."<<endl;
    		return;
    	}

    	//Print the LL node information and decrease its quantity
    	//if quantity is 0, call deleteMovieNode() to delete a LL node with the title

		MovieLLNode *rentLL = searchLL(rentBST->head, title);

		if(rentLL == NULL){
			cout<<"Movie not found."<<endl;
			return;
		}
		else{
			cout << "Movie has been rented." << endl;
			cout << "Movie Info:" << endl;
			cout << "===========" << endl;
			cout << "Ranking:" << rentLL->imdb_ranking << endl;
			cout << "Title:" << rentLL->title << endl;
			cout << "Year:" << rentLL->year_released << endl;
			rentLL->quantity -= 1;
			cout << "Quantity:" << rentLL->quantity << endl;
		}

    	if(rentLL->quantity == 0){
    		deleteMovieNode(title);
    	}

    }

    void printMenu(){
    	//just prints the menu
    	cout << "======Main Menu======" << endl;
    	cout << "1. Find a movie" << endl;
    	cout << "2. Rent a movie" << endl;
    	cout << "3. Print the inventory" << endl;
    	cout << "4. Delete a movie" << endl;
    	cout << "5. Count the movies" << endl;
    	cout << "6. Quit" << endl;
    }

    void readFile(std::string filename){
    	//read file
    	//and call addMovieNode(stoi(rank), title, stoi(year), stoi(quantity));

    	//cout<<"readfile started."<<endl;
    	ifstream inputfilestream;
    	inputfilestream.open(filename.c_str());
    	string input;

    	while(getline(inputfilestream, input)){
    		string rank;
			string title;
			string year;
			string quantity;

    		stringstream ss(input);

    		getline(ss, rank, ',');
    		getline(ss, title, ',');
    		getline(ss, year, ',');
    		getline(ss, quantity, ',');

    		//cout<<rank<<title<<year<<quantity<<endl;

    		addMovieNode(stoi(rank), title, stoi(year), stoi(quantity));
    		//cout<<"added from file"<<endl;
    	}

    	inputfilestream.close();
    	//cout<<"readfile ended"<<endl;
    }

private:
    void DeleteAll(MovieBSTNode *node){
    	//recursive function to delete all nodes
    	//same as in-order traversal
    	//instead of printing, you go through the LL pointed by tree node and delete it
    	if(root == NULL){
    	    cout<<"The tree is empty."<<endl;
    		return;
       	}
      	else{
     		while(node->left != NULL){
 	   			DeleteAll(node->left);
       		}

     		MovieLLNode* iterator = node->head;
     		while(iterator != NULL){
     			MovieLLNode *toBeDeleted = iterator;
     			iterator = iterator->next;
     			cout<<"Deleting: "<<toBeDeleted->title<<endl;
     			delete toBeDeleted;
     		}

     		//node->head = NULL;              ??

     		while(node->right != NULL){
     			DeleteAll(node->right);

     		}
      	}
    } //use this for the post-order traversal deletion of the tree

    void printMovieInventory(MovieBSTNode *node){
    	//this is a recursive function to print in-order
    	if(root == NULL){
    		cout<<"The tree is empty."<<endl;
			return;
    	}
    	else{
    		while(node->left != NULL){                                              //left, node, right for in-order traversals recursively
    			printMovieInventory(node->left);
    		}

    		MovieLLNode* iterator = node->head;
    		while(iterator != NULL){
    	    	cout<<"Movie: "<<iterator->title<<" "<<iterator->quantity<<endl;
    		    iterator = iterator->next;
    		}

    		while(node->right != NULL){
    			printMovieInventory(node->right);
    		}

    	}

    	/*if(root == NULL){
    		cout<<"The tree is empty."<<endl;
    		return;
    	}
    	else{
    		if(node == NULL){
    			return;
    		}
        	printMovieInventory(node->left);

        	MovieLLNode* iterator = node->head;
        	while(iterator != NULL){
        		cout<<"Movie: "<<iterator->title<<" "<<iterator->quantity<<endl;
        		iterator = iterator->next;
        	}

        	printMovieInventory(node->right);

    	}*/


    	//you need to print entire LL attached to a particular node
    }

    void countMovieNodes(MovieBSTNode *node, int &count){
    	//write recursive function
    	//recurstion is same as in-order traversal,
    	//instead of printing value you have to increase count by traversing the LL attached to the node
    	if (root == NULL){
    		cout<<"0"<<endl;
    	    return;
    	}
    	if(node->left != NULL){
    		countMovieNodes(node->left , count);
    	}
    	if(node->right != NULL){
    	    countMovieNodes(node->right, count);
    	}
    	MovieLLNode *iterator = node->head;
    	while(iterator != NULL){
    		count++;
    	    iterator = iterator->next;
    	}
    }

    MovieBSTNode* searchBST(MovieBSTNode *node, std::string title){
    	//this is used by findMovie, deleteMovieNode, rentMovie so that you do not have to repeat this function
    	char firstLetter = title[0];

    	if(node == NULL){
    		return NULL;
    	}
    	else if (node->MovieFirstLetter == firstLetter){           //return when the appropriate index is found, else, recursively call left and right
    		return node;
    	}
    	else if(node->MovieFirstLetter > firstLetter){
    		return searchBST(node->left, title);
    	}
    	else{
    	    return searchBST(node->right, title);
    	}
    } //use this recursive function to find a pointer to a node in the BST, given a MOVIE TITLE first letter

    MovieLLNode* searchLL(MovieLLNode* head, std::string title){
    	//this is used by findMovie, deleteMovieNode, rentMovie so that you do not have to repeat this function
    	if(head == NULL){
    		return NULL;
    	}
    	else if(head->title == title){                            //return when the title is found, else recursively check the next node in the LL
    		return head;
    	}
    	else{
    		return searchLL(head->next, title);
    	}

    } //use this to return a pointer to a node in a linked list, given a MOVIE TITLE and the head of the linked list

    MovieBSTNode* treeMinimum(MovieBSTNode *node){
        //use this to find the leftmost (or minimum) leaf node of the BST, you'll need this in the delete function
    	while(node->left != NULL){
    		node = node->left;
    	}
    	return node;
    }

    MovieBSTNode* root;
};

int main() {
	//TA said it's okay to pass file name instead
	MovieTree mt("Assignment6Movies.txt");
	return 0;
}




/* //    Create MovieNodeLL called newMovie to be added to its LL
    	MovieLLNode *newMovie = new MovieLLNode(ranking, title, releaseYear, quantity);

    	//    Create a BST called newIndex node to be added
    	MovieBSTNode *newIndex = new MovieBSTNode(title.substr(0,1));

    	//    If BST is empty, set newIndex as root and set newMovie as head
    	if(root == NULL){
    	  root = newIndex;
    		root->head = newMovie;
    		root->head->next = newMovie;
        cout<<"first root assigned"<<endl;
    		return;
    	}
    	MovieBSTNode *iterator = root;
    	MovieBSTNode *parent = NULL;

      //or is it parent == null? already there? idk

    	//    Find if newIndex is already in BST, add newMovie to the LL pointed by newIndex alphabetically
    	while(iterator != NULL){
    		if(iterator->MovieFirstLetter == newIndex->MovieFirstLetter){
    			newIndex = iterator;
          cout<<"entered here 1"<<endl;
    			//add linked list traversal as a sort thing here
    			MovieLLNode *current = newIndex->head;
    			while(current->next != NULL){
    				if(newMovie->title > current->title && newMovie->title < current->next->title){
    					MovieLLNode *temp = new MovieLLNode();
    					temp = current->next;
    					current->next = newMovie;
    					newMovie->next = temp;
    				}
    				current = current->next;
    			}
    			current = newMovie;

    			break;
    		}
    		else if(iterator->MovieFirstLetter > newIndex->MovieFirstLetter){            //i think?
          cout<<"entered here 2"<<endl;
    			iterator = iterator->left;
    		}
    		else{
          cout<<"entered here 3"<<endl;
    			iterator = iterator->right;
          cout<<"entered here 3 pt2"<<endl;
    		}
    	}

    	//    if newIndex is not already present, add it in appropriate postition and set newMovie as head
    	//    remeber you are given a parent pointer too, so you need to set parent too

      cout<<"got here"<<endl;
    	if(newIndex != iterator){
        if(newIndex->MovieFirstLetter == parent->MovieFirstLetter){
          cout<<"if the same, append to linked list"<<endl;
        }
        else{
          cout<<"got here 2"<<endl;
    		  if(newIndex->MovieFirstLetter > parent->MovieFirstLetter) {
    			  parent->right = newIndex;
    			  newIndex->parent = parent;
    			  newIndex->head = newMovie;
    		  }
    		  else{
    			  parent->left = newIndex;
    		    newIndex->parent = parent;
    		    newIndex->head = newMovie;
    		  }
        }
    	}
 */














/*bool wentRight = false;                                  //to determine the direction of the child to be added relative to the parent

    	if(root == NULL){                                        //if the BST is empty, make the new one the root
    		root = newIndex;
    		root->head = newMovie;
    		root->head->next = NULL;
    		return;
    	}
    	else{                                                    //if the BST isn't empty (there will be a movie already in its list too, ofc)
    		MovieBSTNode *iteratorBST = root;
    		MovieBSTNode *parent = NULL;

    		while(iteratorBST != NULL){
    			if(iteratorBST->MovieFirstLetter == newIndex->MovieFirstLetter){          //if the first letter matches
    				newIndex = iteratorBST;
    				MovieLLNode *iteratorLL = newIndex->head;
    				                                                              //since there are movies in the list, add newMovie alphabeticaly
    				while(iteratorLL != NULL){
    					if(newMovie->title < iteratorLL->title){
    						MovieLLNode *temp = new MovieLLNode();
    						temp = newIndex->head;
    						newIndex->head = newMovie;
    						newMovie->next = temp;
    						return;
    					}
    					else if(newMovie->title > iteratorLL->title and (newMovie->title < iteratorLL->next->title or iteratorLL->next == NULL)){
    						MovieLLNode *temp = new MovieLLNode();
    						temp = iteratorLL->next;
    						iteratorLL->next = newMovie;
    						newMovie->next = temp;
    						return;
    					}
    					iteratorLL = iteratorLL->next;
    				}
    			}
    			else if(iteratorBST->MovieFirstLetter < newIndex->MovieFirstLetter){
    				iteratorBST = iteratorBST->right;
    				wentRight = true;
    			}
    			else{
    				iteratorBST = iteratorBST->left;
    				wentRight = false;
    			}
    		}

    		//do this if the node with the first letter we're looking for doesn't already exist
    		iteratorBST = iteratorBST->parent;

    		if(wentRight == true){
    			iteratorBST->right = newIndex;
    			newIndex = iteratorBST;

    			MovieLLNode *iteratorLL = newIndex->head;

    			while(iteratorLL != NULL){
    			    if(newMovie->title < iteratorLL->title){
    			    	MovieLLNode *temp = new MovieLLNode();
    			    	temp = newIndex->head;
    			    	newIndex->head = newMovie;
    			    	newMovie->next = temp;
    			    	return;
    			    }
    			    else if(newMovie->title > iteratorLL->title and (newMovie->title < iteratorLL->next->title or iteratorLL->next == NULL)){
    			    	MovieLLNode *temp = new MovieLLNode();
    			    	temp = iteratorLL->next;
    			    	iteratorLL->next = newMovie;
    			    	newMovie->next = temp;
    			    	return;
    			    }
    			    iteratorLL = iteratorLL->next;
    			}
    		}
    		else{
    			iteratorBST->left = newIndex;
    			newIndex = iteratorBST;

    			MovieLLNode *iteratorLL = newIndex->head;

    			while(iteratorLL != NULL){
    			    if(newMovie->title < iteratorLL->title){
    			    	MovieLLNode *temp = new MovieLLNode();
    			    	temp = newIndex->head;
    			    	newIndex->head = newMovie;
    			    	newMovie->next = temp;
    			    	return;
    			    }
    			    else if(newMovie->title > iteratorLL->title and (newMovie->title < iteratorLL->next->title or iteratorLL->next == NULL)){
    			    	MovieLLNode *temp = new MovieLLNode();
    			    	temp = iteratorLL->next;
    			    	iteratorLL->next = newMovie;
    			    	newMovie->next = temp;
    			    	return;
    			    }
    			    iteratorLL = iteratorLL->next;
    			}
    		}
    	}*/








