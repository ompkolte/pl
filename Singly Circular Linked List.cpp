#include <iostream>
using namespace std;

class node{
	public:
		int orderno;
		string name;
		string order;
		
		node *next;
		
		node(){
			next=NULL;
		}		
};

class PizzaOrders{
		public:
			void takeOrder();
			void display();
			void del();
			
			node *head;
			PizzaOrders(){
				head=NULL;
			}
};

void PizzaOrders::takeOrder(){
	node *p,*temp;
	char ch;
	int cnt = 1000;
	p= head;
	
	do{
		temp=new node;
		cout<<"Please enter your name: ";
		cin>>temp->name;
		cin.ignore();
		
		cout<<"Enter your order: ";
		getline(cin, temp->order);
		
		temp->orderno= ++cnt;
		cout<<"Your order number is: "<<temp->orderno<<endl;
		
		if(head==NULL){
			head=temp;
			temp->next=head;
		}
			
			
		else{
			p=head;
			while(p->next!=head){
				p=p->next;
			}
			
			
			p->next=temp;
			temp->next=head;
		}
		
		cout<<"Do you want to place more orders? (y/n): ";
		cin>>ch;
	}
	while(ch!='n');
}

void PizzaOrders::display(){
	node *p;
	
	
	if (head == NULL) {
        cout << "No orders to display!" << endl;
        return;
    }
	
	else{
        p = head;
        do{
            cout << "\nCustomer: " << p->name
                 << "\nOrder: " << p->order
                 << "\nOrder Number: " << p->orderno << endl;
            p = p->next;
        } while(p != head);
		
		cout<<"\nThank You for Ordering Here! \nPlease Visit Again!"<<endl;
	}
	
}

void PizzaOrders::del(){
	node *temp,*p;
	
	if (head == NULL) {
        cout << "No orders to delete!" << endl;
        return;
    }
	
	if(head->next==head){
		p=head;
		head=NULL;
		delete p;
	}
	
	else{
		p=head;
		temp=head;
		while(p->next!=head){
			p=p->next;
		}
		
		head=head->next;
		p->next=head;
		delete temp;
	}
}

int main(){
	PizzaOrders PO;
	cout<<"Welcome!\n"<<endl;
	PO.takeOrder();
	
	PO.display();
	
	PO.del();
	cout<<"\nAfter Deletion: \n"<<endl;
	PO.display();
}
