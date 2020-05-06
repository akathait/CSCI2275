#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<queue>
#include<random>
#include<vector>
using namespace std;

struct node{
	char eng;
	string morse;
	node *parent;
	node *left;
	node *right;
	int priority;
	node(){}
	node(char eng, node *pNode, string mCode){
		this->eng = eng;
		this->priority = 5;
		this->parent = pNode;
		this->left = NULL;
		this->right = NULL;
    this->morse = mCode;
	}
};

class MorseTree{
private:
	node *root;
	node *trainingArr;
  node *treeArr;

public:
	MorseTree(){
		node *temp = new node('!', NULL, "");
		this->root = temp;
		buildTree();
		trainingArr = new node[10];
		treeArr = new node[31];
		menu();
	}

	void menu(){
		cout<<"Welcome to Woodpecker!"<<endl;

		while(1){
			cout<<"Enter 1 to translate."<<endl;
			cout<<"Enter 2 to start the training game"<<endl;
			cout<<"Enter 3 to exit Woodpecker."<<endl;

			string choice;
			cin>>choice;

			if(choice == "1"){
        string input1;
				cout<<"Enter Morse code to translate"<<endl;
        cin>>input1;
        cout<<getChar(input1)<<endl;

			}
			else if (choice == "2"){
				while(1){
					cout<<"Enter 1 to play or continue playing the training game."<<endl;
					cout<<"Enter 2 to return to the main menu (your progress will not be erased)."<<endl;

					string choice2;
					cin>>choice2;

					if(choice2 == "1"){
						trainingGame();
					}
					else if(choice2 == "2"){
						break;
					}
					else{
						cout<<"Invalid selection."<<endl;
					}
				}
			}
			else if(choice == "3"){
				cout<<"Goodbye!"<<endl;
				exit(1);
			}
			else{
				cout<<"Invalid selection."<<endl;
			}
		}
	}

	//Johnny Boy's stuff
	void buildTree(){
    addNode('!', false, 'e', ".");
    addNode('!', true, 't', "/");
    addNode('e', false, 'i', "..");
    addNode('e', true, 'a', "./");
    addNode('t', false, 'n', "/.");
    addNode('t', true, 'm', "//");
    addNode('i', false, 's', "...");
    addNode('i', true, 'u', "../");
    addNode('a', false, 'r', "./.");
    addNode('a', true, 'w', ".//");
    addNode('n', false, 'd', "/..");
    addNode('n', true, 'k', "/./");
    addNode('m', false, 'g', "//.");
    addNode('m', true, 'o', "///");
    addNode('s', false, 'h', "....");
    addNode('s', true, 'v', ".../");
    addNode('u', false, 'f', "../.");
    addNode('r', false, 'l', "./..");
    addNode('w', false, 'p', ".//.");
    addNode('w', true, 'j', ".///");
    addNode('d', false, 'b', "/...");
    addNode('d', true, 'x', "/../");
    addNode('k', false, 'c', "/./.");
    addNode('k', true, 'y', "/.//");
    addNode('g', false, 'z', "//..");
    addNode('g', true, 'q', "//./");
	}

	void addNode(char pChar, bool lf, char nChar, string mCode){
    node *pNode = search(pChar, root);
    node *temp = new node(nChar, pNode, mCode);
    if(lf)
      pNode->right = temp;
    else
      pNode->left = temp;
	}

	node* search(char val, node *temp){
    if(temp == NULL)
      return NULL;
    if(temp->eng == val)
      return temp;
    node *ans = NULL;
    ans = search(val, temp->left);
    if(ans != NULL)
      return ans;
    else
      ans = search(val, temp->right);
    return ans;
	}

  char getChar(string input){
    char code[input.length()];
		for(int i = 0; i<sizeof(code); i++){
			code[i] = input[i];
			}

			//cout<<sizeof(code)<<endl;
		node *temp = root;
		for(int i = 0; i<sizeof(code); ++i){
			//while(temp != NULL){
				if(code[i] == '.')
					temp = temp->left;
				else
					temp = temp->right;
			}
      if(temp == NULL){
        cout<<"Invalid code"<<endl;
        return '!';
        }
      else
		    return temp->eng;
    }

    string getCode(char aChar){
		node *temp = search(aChar, root);
		if(temp == NULL)
      return "Letter not found";
  	else
			return temp->morse;
	}

    void printTree(){
		inOrder(root);
		cout<<endl;
	}

	void inOrder(node *root){
		if(root==NULL)
			return;
		inOrder(root->left);
		cout<<root->eng<<" ";
		inOrder(root->right);
	}

	//(Anushka) training game code begins here
  	//take morse input from user and compare for the game
  		//increase priority if wrong
  		//decrease priority if right
  	void trainingGame(){
  		loadTrainingArr();

  		for(int i = 0; i < 10; i++){
  			cout<<"Translate "<<trainingArr[i].eng<<endl;

  			string morseTranslate;
  			cin>>morseTranslate;

  			if(morseTranslate == trainingArr[i].morse){                                  
  				cout<<"Correct!"<<endl;
  				trainingArr[i].priority = trainingArr[i].priority - 1;        
  			}
  			else{
  				cout<<"Incorrect."<<endl;
  				trainingArr[i].priority = trainingArr[i].priority + 1;
  			}
  		}
  		cout<<"Great job!"<<endl;
  	}

	void loadTrainingArr(){  //credit for random number generator info: http://www.cplusplus.com/forum/beginner/26611/
		int i = 0;
		loadTreeArr(root, &i);
		srand(time(NULL));

		int insertedCount = 0;
		int trainingInd = 0;

		while(insertedCount < 10){
			int randInd = rand() % 31;

			if(treeArr[randInd].priority != 0){
				trainingArr[trainingInd] = treeArr[randInd];
				trainingInd++;
				insertedCount++;
			}
		}
	}

	void loadTreeArr(node *root, int* i){                      //loaded in order
		if(root == NULL){
			return;
		}

		loadTreeArr(root->left, i);
		treeArr[*i] = *root;
		(*i)++;
		loadTreeArr(root->right, i);
	}
};

int main(){
  MorseTree test;
}
