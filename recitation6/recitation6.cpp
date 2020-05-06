#include<iostream>
#define max_size 5
using namespace std;


class stack{
	int top;
	int stack_array[max_size];

public:
	stack(){
		top = -1;
	}

	void push(int n){
		if(top + 1 == max_size){
			cout<<"Overflow error."<<endl;
			exit(1);
		}
		top++;
		stack_array[top] = n;
	}

	void pop(){
		if(top != -1){
			top--;
		}
		else{
			cout<<"Underflow error."<<endl;
			exit(1);
		}
	}

	int peek(){
		if(top == -1){
			cout<<"Underflow error."<<endl;
			exit(1);
		}
		cout<<stack_array[top]<<endl;
		return stack_array[top];
	}

	int size(){
		int size;
		size = top + 1;
		cout<<size<<endl;
		return size;
	}

	~stack(){
		top = -1;
	}
};

int main(){
	bool quit = false;
	stack inst;

	while(quit != true){
		string choice = "";

		cout<<"==STACK MENU=="<<endl;
		cout<<"1. Push"<<endl;
		cout<<"2. Pop"<<endl;
		cout<<"3. Peek"<<endl;
		cout<<"4. Exit"<<endl;

		cin>>choice;

		if(choice == "1"){
			int n;
			cin>>n;
			inst.push(n);
			inst.size();
		}
		else if(choice == "2"){
			inst.pop();
			inst.size();
		}
		else if(choice == "3"){
			inst.peek();
		}
		else if (choice == "4"){
			inst.~stack();
			exit(1);
		}
		else{
			cout<<"Invalid choice."<<endl;
		}

	}
}
