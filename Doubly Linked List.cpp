#include <iostream>
using namespace std;

class node{
	public:
		int ticketno;
		char gender;
		string station;
		node *next;
		node *prev;
		node(){
			next=prev=NULL;
		}
};

class dll{
	public:
		node *head;
		dll(){
			head=NULL;
		}
		
		int create();
		void display();
		void bubblesort(int n);
		node *swap(node *p1, node *p2);
		dll merge(dll l1, dll l2);
};

int dll::create(){
	node *temp,*p;
	char ch;
	int cnt=0;
	do{
		temp=new node;

		cout<<"Enter the ticket number: ";
		cin>>temp->ticketno;
		cnt++;
		
		if(head==NULL)
		head=temp;
		
		else{
			p=head;
			while(p->next!=NULL)
			p=p->next;
			
			p->next=temp;
			temp->prev=p;
			

		}
		
		cout<<"Do you want to add more nodes? (y/n): ";
		cin>>ch;
	}
	while(ch!='n');
	return cnt;
}

void dll::display(){
	int ch;

	node *temp;
	temp=head;
		
		while(temp!=NULL){
			cout<<"Station: "<<temp->station<<endl<<"Ticket No.: "<<temp->ticketno<<endl<<"Gender: "<<temp->gender<<endl;
			temp=temp->next;
		}
}

node *dll::swap(node *p1, node *p2){
	if(p1->prev==NULL){
		node *temp=p2->next;
		p2->next=p1;
		p2->prev=NULL;
		p1->prev=p2;
		p1->next=temp;
		temp->prev=p1;
		return p2;
	}
	
	else if(p2->next==NULL){
		node *temp=p1->prev;
		p2->next=p1;
		p1->next=NULL;
		p1->prev=p2;
		p2->prev=temp;
		temp->next=p2;
		return p2;
	}
	
	else{
		node *temp1=p1->prev;
		node *temp2=p2->next;
		p2->next=p1;
		p1->prev=p2;
		p1->next=temp2;
		temp2->prev=p1;
		p2->prev=temp1;
		temp1->next=p2;
		return p2;
	}
}

void dll::bubblesort(int cnt){
	node **h;
	int swapped;
	for(int i=0;i<cnt;i++){
		h=&(head);
		swapped=0;
		for(int j=0;j<cnt-i-1;j++){
			node *p1=*h;
			node *p2=p1->next;
			if(p1->ticketno > p2->ticketno){
				*h=swap(p1,p2);
				swapped=1;
			}
			h=&(*h)->next;
		}
		if(swapped==0)
			break;
	}
}

dll dll::merge(dll l1, dll l2){
	dll l3;
	node *p, *q, *r;
	p= l1.head;
	q=l2.head;
	
	
	if(p==NULL && q==NULL)
	cout<<"Cannot merge lists... /n Both lists are empty..!";
	
	if(p==NULL){
		l3.head=q;
		return l3;
	}
	
	if(q==NULL){
		l3.head=p;
		return l3;
	}
	

	if(p->ticketno > q->ticketno){
		l3.head=q;
		q=q->next;
	}
	
	else{
		l3.head=p;
		p=p->next;			
	}
	
	r=l3.head;
	r->prev= NULL;
	
	while(p!=NULL && q!=NULL){
		if(p->ticketno > q->ticketno){
			r->next=q;
			q->prev=r;
			r=r->next;
			q=q->next;
		}
		
		else{
			r->next=p;
			p->prev=r;
			r=r->next;
			p=p->next;
		}
	}
	
	if(p != NULL) {
		r->next = p;
		p->prev = r;
	}
	if(q != NULL) {
		r->next = q;
		q->prev = r;
	}
	
	return l3;
}

int main(){
	dll d1,d2,d3;
	
	cout<<"For first list: "<<endl;
	int cnt= d1.create();
	
	cout<<"\nFor second list: "<<endl;
	int cnt2= d2.create();
	
	d1.bubblesort(cnt);
	cout<<"\nSorted List 1: \n"<<endl;
	d1.display();
	
	d2.bubblesort(cnt2);
	cout<<"\nSorted List 2: \n"<<endl;
	d2.display();
	
	d3= d3.merge(d1,d2);
	cout<<"\nMerged List 3: \n"<<endl;
	d3.display();
	return 0;
}











