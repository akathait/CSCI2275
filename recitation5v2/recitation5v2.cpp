#include<iostream>

using namespace std;

struct node
{
    int data;
    node *next;
};


class linked_list
{
private:
    node *head,*tail;
public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }

    bool isempty()
    {
        return head==NULL;
    }

    void insert(int n)
    {
        node *temp = new node();
        temp->data = n;
        temp->next = NULL;

        if(head == NULL)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->next = temp;
            tail = tail->next;
        }
    }

    void sort_llist(){
    	node *new_head = NULL;
    	node *temp = head;

    	while(temp != NULL){
    		if(new_head == NULL){
    			new_head = new node();
    			new_head -> data = temp -> data;
    			new_head -> next = NULL;

    		}
    		else{
    			node *temp1 = new_head;                                //file on canvas week 5
    			while(temp1 != NULL && temp1 -> next != NULL){
    				if(temp)
    			}
    		}
    	}

    }

    void delete_list(node *temp_head)
    {
    	//function to delete original list


    }


    void print()
    {
        node *temp = head;
        cout<<"===CURRENT LIST==="<<endl;
        while(temp!=NULL)
        {
            cout<<temp->data<<"->";
            temp = temp->next;
        }
        cout<<"NULL"<<endl;
    }

    //destructor
    ~linked_list(){
    	node *next;
    	while(head!=NULL)
    	{
    		next = head->next;
    		delete head;
            head = next;
    	}
    }
};

int main()
{
    linked_list a;

    a.insert(6);
    a.insert(3);
    a.insert(2);
    a.insert(8);
    a.insert(7);
    a.insert(1);

    a.sort_llist();

    return 0;
}
