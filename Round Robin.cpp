#include<iostream>
#define max 50
using namespace std;
class Process
{
	public:
		int process_id;
		int BT;
		int RT;
};
class ProcessQueue{
    public:
    Process data[max];
    int rear,front;
    ProcessQueue(){
        rear=front=-1;
    }

    int isempty(){
        if(rear==-1){
            return 1;
        }
        else{
            return 0;
        }
    }

    int isfull(){
        if((rear+1)%max==front){
            return 1;
        }
        else{
            return 0;
        }
    }
    void enqueue(Process x){
        if(isfull()){
            cout<<"You can not insert the element!!!"<<endl;
        }
        else if(isempty()){
            rear=0;
            front=0;
            data[0]=x;
        }
        else{
            rear=(rear+1)%max;
            data[rear]=x;
        }
    }

    Process dequeue(){
        Process x;
        x=data[front];
        if(isempty()){
            cout<<"Queue is empty"<<endl;
        }
        else if(rear==front){
            front=rear=-1;
        }
        else{
            front=(front+1)%max;
        }
    	return x;

    }
};
 void RoundRobin(ProcessQueue pq, int QT)
{
	Process p;
	int tt =0;
	while(!pq.isempty())
	{
		p = pq.dequeue();
		if(p.RT>QT)
		{
			p.RT=QT;
			pq.enqueue(p);
			cout<<"Process "<<p.process_id<<" sheduled for "<<QT<<" time and remaining time is "<<p.RT<<endl;
			tt=tt+QT;
		}
		else
		{
			p.RT=0;
			tt=tt+QT;	
		}
 	}
 	
}

int main()
{
	ProcessQueue pq;
	int n,f,r;
	cout<<"Enter the no. of processes: ";
	cin>>n;
	for(int i=0 ; i<n ; i++)
	{
		cout<<"Enter the process id and burst time: ";
		cin>>pq.data[i].process_id>>pq.data[i].BT;
		pq.enqueue(pq.data[i]);
	}
	int QT;
	cout<<"Enter the Quantum Time: ";
	cin>>QT;
	RoundRobin(pq,QT);
	
	return 0;
}
