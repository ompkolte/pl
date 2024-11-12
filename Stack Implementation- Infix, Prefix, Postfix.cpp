#include <iostream>
#include<string>
#include<cmath>
#define MAX 20

using namespace std;

class stack{
	public:
	    string s[MAX];
	    int top;
	    stack() { top = -1; }
	
	    bool isempty();
	    bool isfull();
	    void push(string str);
	    string pop();
};

bool stack::isempty(){
    if (top == -1)
        return true;
    else
        return false;
}

bool stack::isfull(){
    if (top == MAX - 1)
        return true;
    else
        return false;
}

void stack::push(string str){
    if (isfull())
        cout << "\n Stack is full!"<<endl;
    else{
        top++;
        s[top] = str;
    }
}
string stack::pop(){
    if (isempty()){
    	cout << "\n Stack is empty!"<<endl;
    	return "";
	}
    else{
        string temp = s[top];
        top--;
        return temp;
    }
}

class expression{
	public:
	    stack st;
	    void prefix_to_infix();
	    void infix_to_posfix();
	    int checkPrecedence(char x);
	    bool isoperator(char x){
	        if (x =='+' || x == '-' || x == '*' || x == '/' || x == '+' || x == '^')
	            return true;
	        else
	            return false;
	    }
};

//Check Precedence
int expression::checkPrecedence(char x){
	if(x=='^')
	return 3;
	
	else if(x=='*' || x=='/')
	return 2;
	
	else if(x=='+' || x=='-')
	return 1;
	
	else
	return 0;
}

// Prefix to Infix Conversion
void expression::prefix_to_infix() {
    string prefix;
    cout<<"Enter Prefix Expression: "<<endl;
    cin>>prefix;
    int count = prefix.length(); 
    for (int i = count-1; i >= 0; i--){
        if (isoperator(prefix[i])){
            string op1 = st.pop(); 
            string op2 = st.pop();

            string temp = "(" + op1 + prefix[i] + op2 + ")";
            st.push(temp);
        }
        else{
            st.push(string (1, prefix[i]));
        }
    }
    cout<<"Infix Expression is: \n"<<st.pop()<<endl;
}

//Infix to Postfix Conversion
void expression::infix_to_posfix(){
	string infix;
	string postfix="";
	cout<<"\nEnter Infix Expression: "<<endl;
	cin>>infix;
	int len= infix.length();
	
	for(int i=0;i<len;i++){
		if((infix[i]>='a' && infix[i]<='z') || (infix[i]>='A' && infix[i]<='Z'))
		postfix= postfix + infix[i];
		
		else if(infix[i]=='(')
		st.push(string(1,infix[i]));
		
		else if(infix[i]==')'){
			while(st.s[st.top] != "("){
				postfix= postfix + st.pop();
			}
			st.pop();
		}
		
		else{
			while(checkPrecedence(infix[i])<=checkPrecedence(st.s[st.top][0])){
				postfix= postfix + st.pop();
			}
			
			st.push(string(1,infix[i]));
		}
	}
	
	while(!st.isempty()){
		postfix= postfix+  st.pop();
	}
	
	cout << "Postfix Expression is: \n" << postfix<<endl;
}

// ---------------------------------------------------- Postfix Evaluation ---------------------------------------------------------------

class stk{
	public:
	    int s[MAX];
	    int top;
	    stk(){ top = -1; }
		
		int operation(int n1, int n2, char op);
	    void postfixEval();
	    void push(int x);
	    int pop();
};

void stk::push(int x){
    s[++top] = x;
}

int stk::pop(){
    int temp = s[top];
    top--;
    return temp;
    
}

void stk::postfixEval(){
	string postfix;
	cout<<"Enter the postfix expression you want to evaluate: ";
	getline(cin,postfix);
	int len= postfix.length();
	
	for(int i=0;i<len;i++){
		if(postfix[i]==' ')
		continue;
		
		else if(isdigit(postfix[i])){
			int num=0;
			while(isdigit(postfix[i])){
				num= num*10 + (postfix[i] - '0');
				i++;
			}
			push(num);
			i--;
		}
		
		else{
			int op_1 = pop();
			int op_2= pop();
			
			int result= operation(op_1, op_2, postfix[i]);
			push(result);
		}
	}
	
	cout<<"The Value of the Expression is: "<<pop()<<endl;
}

int stk::operation(int n1, int n2, char op){
	switch(op){
		case '+':
			return (n2+n1);
			break;
			
		case '-':
			return (n2-n1);
			break;
			
		case '*':
			return (n2*n1);
			break;
			
		case '/':
			return (n2/n1);
			break;
			
		case '^':
			return pow(n2,n1);
			break;
			
		default: return 0;
	}
}




int main(){
    expression exp;    
    stk s1;
    char cont;
    
    do{
    	int ch;
	    cout<<"Enter \n1. Prefix to Infix \n2. Infix to Postfix Conversion \n3. Evaluate Postfix Expression"<<endl;
	    cin>>ch;
	    
	    switch(ch){
	    	case 1:
	    		exp.prefix_to_infix();
	    		break;
	    		
	    	case 2:
	    		exp.infix_to_posfix();
	    		break;
	    		
	    	case 3:
	    		cin.ignore();
	    		s1.postfixEval();
	    		break;
		}
	    
	    cout<<"Do you want to continue? (y/n): ";
	    cin>>cont;
	}
	while(cont!='n');    
    
    return 0;
}
