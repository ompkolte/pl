#include <iostream>
using namespace std;

class node{
	public:
		node *next;
		node *prev;
		
		string item;
		float price;
		int quantity;
		
		node(){
			next = prev = NULL;
		}

};

class dequeue{
	public: 
		node *front;
		node *rear;
		
		void insert_at_front(node *a);
		void insert_at_end(node *a);
		void delete_from_front();
		void delete_from_end();
		void display();
		bool isEmpty();
		dequeue(){
			front = rear = NULL;
		}
};

bool dequeue::isEmpty(){
	if(front == NULL && rear == NULL)
	return true;
	
	else return false;
}

void dequeue::insert_at_end(node *temp){
	if(isEmpty())
	front = rear = temp;
	
	else{
		rear->next=temp;
		temp->prev=rear;
		rear=rear->next; //rear = temp;
	}
}

void dequeue::insert_at_front(node *temp){
	if(isEmpty())
	front = rear = temp;
	
	else{
		temp->next=front;
		front->prev=temp;
		front=temp; //front = front->prev;
	}
}

void dequeue::delete_from_front(){
	if(isEmpty())
	cout<<"Already Empty... Cannot Delete!"<<endl;
	
	else if(front == rear){
		node *p = front;
		front = rear = NULL;
		delete p;
	}
	
	else{
		node *temp = front;
		front = front->next;
		front->prev = NULL;
		delete temp;
	}
}

void dequeue::delete_from_end(){
	if(isEmpty())
	cout<<"Already Empty... Cannot Delete!"<<endl;
	
	else if(front == rear){
		node *p = front;
		front = rear = NULL;
		delete p;
	}
	
	else{
		node *temp = rear;
		rear = rear->prev;
		rear->next = NULL;
		delete temp;
	}
}

void dequeue::display(){
	node *curr=front;
	while(curr!=NULL){
		cout<<"\nItem Name: "<<curr->item<<"\nItem Quantity: "<<curr->quantity<<"\nItem Price: "<<curr->price<<"\nTotal Price: "<<(curr->quantity)*(curr->price)<<endl;
		curr=curr->next;
	}
}

node* newnode(){
	node *temp = new node;
	cout<<"\nEnter item name: ";
	cin>>temp->item;
	cout<<"Enter item quantity: ";
	cin>>temp->quantity;
	cout<<"Enter item price: ";
	cin>>temp->price;
	return temp;
}

int main(){
	int ch;
	char choice;
	dequeue dq;
	
	do{
		cout<<"\nEnter \n1. Insert at Front \n2. Insert at End \n3. Delete from Front \n4. Delete from End \n5. Display \n6. Exit"<<endl;
		cin>>ch;
		
		switch(ch){
			case 1: //insert at front
				dq.insert_at_front(newnode());
				break;
			
			case 2: //insert at end	
				dq.insert_at_end(newnode());
				break;
			
			case 3: //delete at Beginning
				dq.delete_from_front();
				break;
				
			case 4: //delete at Last
				dq.delete_from_end();
				break;
				
			case 5: //display
				dq.display();
				break;
				
			case 6: //exit
				cout<<"Exiting..."<<endl;
				break;
				
			default: cout<<"Enter valid choice!"<<endl;
		}
		
		cout<<"Do you want to continue? (y/n) ";
		cin>>choice;	
	} while(choice!='n');
	
	return 0;
}
