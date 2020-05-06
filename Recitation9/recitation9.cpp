#include<iostream>

using namespace std;
// Data structure to store a Binary Tree node
struct Node
{
	int key;
	struct Node *left, *right;
	Node(int key){
		this->key = key;
		left = NULL;
		right = NULL;
	}
};



// Recursive function to perform inorder traversal of a binary tree
void inorder(struct Node* root)
{
	if (root == NULL)
		return;

	inorder(root->left);
	cout<<root->key<<" ";
	inorder(root->right);
}

// Recursive function to build a BST from a preorder sequence
struct Node* constructBSTfromPreorder(int preorder[], int start, int end)
{
	// base case
	if (start > end)
		return NULL;

	// Construct the root node of the sub-tree formed by keys of the
	// preorder sequence in range [start, end]
	Node *node = new Node(preorder[start]);

	// search the index of first element in current range of preorder
	// sequence which is larger than the value of root node
	int i;
	for (i = start; i <= end; i++) {
		if (preorder[i] > node->key)
			break;
	}

	// recursively construct the left sub-tree
	node->left = constructBSTfromPreorder(preorder, start + 1, i - 1);

	// recursively construct the right sub-tree
	node->right = constructBSTfromPreorder(preorder, i, end);

	// return current node
	return node;
}

struct Node* constructBSTfromPostorder(int postorder[], int start, int end)       //root left right vs left right root
{
	if(start>end){
		return NULL;
	}
	Node *node = new Node(postorder[end]);

	int i;

	for(i = end; i >= start; i--){
		if(postorder[i] < node->key){                            //the first we find or the last?...
			break;
		}
	}

	node->left = constructBSTfromPostorder(postorder, start, i);
	node->right = constructBSTfromPostorder(postorder, i + 1, end-1);

	return node;
}

// main function
int main(void)
{
	/* Construct below BST
              15
            /    \
           /      \
          10       20
         /  \     /  \
        /    \   /    \
       8     12 16    25
	*/

	int preorder[] = { 15, 10, 8, 12, 20, 16, 25 };
	int n = sizeof(preorder)/sizeof(preorder[0]);

	// construct the BST
	struct Node* root_pre = constructBSTfromPreorder(preorder, 0, n - 1);

	// print the BST
	cout<<"\nInorder Traversal of BST after creating tree from preorder: \n";

	// inorder on the BST always returns a sorted sequence
	inorder(root_pre);

	int postorder[] = {8,12,10,16,25,20,15};
	struct Node* root_post = constructBSTfromPostorder(postorder,0,n-1); 

	cout<<"\nInorder Traversal of BST after creating tree from postorder: \n";

	// inorder on the BST always returns a sorted sequence
	inorder(root_post);

	return 0;
}
