#include <iostream>
using namespace std;

class node{
	public:
		string station;
		int ticketno;
		char gender;
		node *next;
		
		node(){
			next=NULL;
		}
};

class sll{
	node *head;
	public:
		void create();
		void display();
		void del();
		void search();
		void update();
		void sort();
		sll(){
			head=NULL;
		}
};

void sll::create(){
	node *temp, *p;
	char ch;
	
	do{
		temp=new node;
		
		cout<<"Enter the station you want to go to: ";
		cin>>temp->station;
		cout<<"Enter your ticket number: ";
		cin>>temp->ticketno;
		cout<<"Enter your gender (F/M): ";
		cin>>temp->gender;
		
		//check if list is empty
		if(head==NULL)
		head=temp;
		
		else{
			p=head;
			
			//if not empty, go to last node
			while(p->next!=NULL)
			p=p->next;
			
			p->next=temp;
		}
		cout<<"Do you want to add more nodes? (y/n): ";
		cin>>ch;
	}
	while(ch!='n');	
}

void sll::display(){
	node *p;
	p=head;
	
	while(p!=NULL){
		cout<<"Station: "<<p->station<<endl<<"Ticket No.: "<<p->ticketno<<endl<<"Gender: "<<p->gender<<endl;
		p=p->next;
	}
}

void sll::del(){
	int item;
	node *curr,*prev;
	curr=head;
	prev=NULL;
	cout<<"Enter the ticket number you want to delete: ";
	cin>>item;
	
	while(curr!=NULL){
		if(curr->ticketno==item){
			if(curr==head){
				head=head->next;
				delete curr;
				break;
			}
			else if(curr->next==NULL){
				prev->next=NULL;
				delete curr;
				break;
			}
			else{
				prev->next=curr->next;
				delete curr;
				break;
			}
		}
		else{
			prev=curr;
			curr=curr->next;
		}
	}
	if(curr==NULL)
	cout<<"Could not find ticket number. Deletion did not take place!";
}

void sll::search(){
	int item;
	node *curr;
	curr=head;
	cout<<"Enter the ticket number you want to search: ";
	cin>>item;
	
	while(curr!=NULL){
		if(curr->ticketno==item){
			cout<<"Entry Found! \n"<<"Station: "<<curr->station<<endl<<"Ticket No.: "<<curr->ticketno<<endl<<"Gender: "<<curr->gender<<endl;
			break;
		}
		
		else
		curr=curr->next;
	}
	if(curr==NULL)
	cout<<"Could not find ticket number!";
}

void sll::update(){
	int item;
	int ch;
	node *curr;
	curr=head;
	cout<<"Enter the ticket number you want to update: ";
	cin>>item;
	
	while(curr!=NULL){
		if(curr->ticketno==item){
			cout<<"What do you want to update: \n"<<"1. Station "<<endl<<"2. Ticket No. "<<endl<<"3. Gender "<<endl;
			cin>>ch;
			switch(ch){
				case 1:
					cout<<"Enter new Station: ";
					cin>>curr->station;
					break;
					
				case 2:
					cout<<"Enter new Ticket No.: ";
					cin>>curr->ticketno;
					break;
					
				case 3:
					cout<<"Enter new Gender: ";
					cin>>curr->gender;
					break;
			}
			break;
		}
		
		else
		curr=curr->next;
	}
	if(curr==NULL)
	cout<<"Could not find ticket number. Updation did not take place!";
}

void sll::sort(){
	node *curr, *temp;
	curr=head;
	temp=new node;
	while(curr->next!=NULL){
		if(curr->ticketno > curr->next->ticketno){
			temp->ticketno = curr->ticketno;
			curr->ticketno=curr->next->ticketno;
			curr->next->ticketno=temp->ticketno;
			
			temp->station = curr->station;
			curr->station=curr->next->station;
			curr->next->station=temp->station;
			
			temp->gender = curr->gender;
			curr->gender=curr->next->gender;
			curr->next->gender=temp->gender;
		}
		curr=curr->next;
	}
	display();
}

int main(){
	sll s1;
	int ch;
	char choice;
	do{
		cout<<"Enter \n1. Create \n2. Display \n3. 6. Delete \n7. Search \n8. Update \n9. Sort \n10. Exit"<<endl;
		cin>>ch;
		
		switch(ch){
			case 1: //Create
				s1.create();
				break;
			
			case 2: //Display
				s1.display();
				break;
				
			case 6: //Delete
				s1.del();
				break;
				
			case 7: //Search
				s1.search();
				break;
				
			case 8: //Update
				s1.update();
				break;
				
			case 9: //Sort
				s1.sort();
				break;
				
			case 10: //Exit
				cout<<"Exiting...";
				break;
		}
		cout<<"Do you want to continue with program? (y/n): ";
		cin>>choice;
	}
	while(choice!='n');
	
	return 0;
}
