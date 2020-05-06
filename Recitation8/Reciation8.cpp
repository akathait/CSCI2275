#include<iostream>
#include<queue>
using namespace std;

struct Node{
	int data;
	Node *left;
	Node *right;
};

class Tree{
	Node *root;
	Node *parent;
public:
	Tree(){
		root=NULL;
	}
	
	void insert(int value){
		//create a node
		Node *new_n = new Node();
		new_n->data = value;
		new_n->left = NULL;
		new_n->right = NULL;


		if(root==NULL){
			root = new_n;
		}else{
			Node *curr = root;
			Node *parent = NULL;
			while(curr!=NULL){
				parent = curr;
				if(value>curr->data){
					curr=curr->right;
				}
				else if(value<curr->data){
					curr=curr->left;
				}
			}
			if(parent->data>value){
				parent->left = new_n;
			}else{
				parent->right = new_n;
			}
		}
	}

	void print_node(){
		cout<<"Printing inorder"<<endl;
		inorder(root);
		cout<<endl;
	}

	void inorder(Node *root){
		if(root==NULL)
			return;
		inorder(root->left);
		cout<<root->data<<",";
		inorder(root->right);
	}

	//complete the function height
	int height(){
		int height = 0;
		queue<Node *>myq;
		myq.push(root);

		while(1)
		{
			int nodeCount = myq.size();                            //this is number of nodes at current level

			if(nodeCount == 0){
				return height;
			}
			else{
				height++;
			}

			while(nodeCount > 0){
				if(myq.front()->left != NULL){
					myq.push(myq.front()->left);
				}
				if(myq.front()->right != NULL){
					myq.push(myq.front()->right);
				}

				myq.pop();
				nodeCount--;
			}


		}
	}
};

int main()
{

	/*Tree looks like below
			6
		  /  \
		 2    8
		 \   / \
          4  7  9
     */
	Tree t;
	t.insert(6);
	cout<<t.height()<<endl;
	t.insert(2);
	cout<<t.height()<<endl;
	t.insert(8);
	cout<<t.height()<<endl;
	t.insert(7);
	cout<<t.height()<<endl;
	t.insert(9);
	cout<<t.height()<<endl;
	t.insert(4);
	cout<<t.height()<<endl;
	t.print_node();
	
	return 1;
}
