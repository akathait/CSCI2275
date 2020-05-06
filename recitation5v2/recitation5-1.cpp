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
        node *tmp = new node();
        tmp->data = n;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }
    
    void sort_llist()
    {
      //fill in insertion sort code
    	node *new_head = NULL;
    	node *temp = head;
    	while(temp!=NULL)
    	{
    		if(new_head==NULL)
    		{
    			new_head = new node();
    			new_head->data = temp->data;
    			new_head->next = NULL;
    		}else
    		{
    			if(new_head->data>temp->data)
    			{
    				node *temp1 = new node();
    				temp1->data = temp->data;
    				temp1->next = new_head;
    				new_head = temp1;
    			}else
    			{
    				node *temp1 = new_head;
    				while(temp1!=NULL && temp1->next!=NULL){
    				if(temp1->data<temp->data && temp1->next->data>temp->data)
    				{
    					node *k = new node();
    					k->data = temp->data;
    					k->next = temp1->next;
    					temp1->next = k;
    					break;
    				}
    				temp1 = temp1->next;
    			   }

    			   //This is possible only when node has greatest value
    			   if(temp1->next==NULL)
    			   {
    			   	node *k = new node();
    					k->data = temp->data;
    					k->next = temp1->next;
    					temp1->next = k;
    			   }

    			}
    		}
    		temp = temp->next;
    	}
    	head = new_head;

    }

    void delete_list(node *temp_head)
    {
    	//function to delete original list
    	node *next;
    	while(head!=NULL)
    	{
    		next = temp_head->next;
    		delete temp_head;
            temp_head = next;
    	}
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
    a.print();
    return 0;
}