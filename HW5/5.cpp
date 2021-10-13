 /*
   Author：B062040027 鄭乃心
   Date：2020.10.24
   Purpose：處理兩個多項式加法乘法
*/

#include<iostream>
using namespace std;

class Node{
	public:
		int corr;
		int pow;
		Node* next;	//指向下一個node
};

class Poly{
	public:
	Node* first;
	Poly():first(NULL){};		
	void push(int, int);
	void del(Node*);
	void sort(int, int);
	void print();
	Poly operator+(const Poly&);
	Poly operator*(const Poly&);
	
	
};
int main(){
	int count=1;
	while(1){
		int P,Q,corr,pow;
		Poly one,two; 

		cin>>P;
		for(int i=1;i<=P;i++){
			cin >> corr >> pow;			
			one.push(corr,pow);
		}

		cin>>Q;
		for(int i=1;i<=Q;i++){
			cin >> corr >> pow;			
			two.push(corr,pow);
		}

		if(P==0&&Q==0)
			break;
		
		cout<<"case"<<count<<":"<<endl;
		Poly result;
		cout<<"ADD"<<endl;
		result=one+two;
		result.print();
		cout<<"MULTIPLY\n";
		result=one*two;
		result.print();
		
		count++;
	
	}
} 




void Poly::push(int a,int n){
	if(a==0) 	return;		//係數為零 ,不push; 
	if(first==NULL){			//沒node時
		Node* temp=new Node();	//創一個新的node
		temp->next=NULL;			//他的指標指向NUll 
		temp->corr=a;
		temp->pow=n;
		first=temp;				//first換成這個node
	}
	else{					//已經有node時			
		Node* Same=first;		//找次方相同的，係數相加 
		while(Same!=0){
			if(n==Same->pow){		//若係數相同
				Same->corr=Same->corr+a;		//係數相加 
				if(Same->corr==0){	//若相加後係數為零 
					del(Same);
				}
				return;
			}	
			Same=Same->next;		//沒找到相同次方移到下一個node 
		}

		sort(a, n);

	} 		
}

void Poly::del(Node* a){
	Node* current=first;
	while(current!=0){
		if(current==a && a->next==NULL){		//若只有一個node的情況 
			first=0;
			delete a;
			break;
		}
		else if(current->next==a){		//若有兩個node以上的情況 
			current->next=a->next;
			delete a;
		}
						
		current=current->next;		//不符合找下一個 
	}
}

void Poly::sort(int a,int n){
		Node* Sort=first;
		Node* temp=new Node();
		temp->corr=a;
		temp->pow=n;
		while(Sort!=0){		//由次方大到小排序 
			if(Sort->pow<n){		//若大於first
				temp->next=Sort;
				first=temp;		//將first換成這個node	
				return;
			}
			else if(Sort->next==0){	//若順序在最後 
				Sort->next=temp;
				temp->next=0;
				return;		
			}	
			else if(Sort->pow>n && Sort->next->pow<n ){
				temp->next=Sort->next;
				Sort->next=temp;
				return;
			}
			else
				Sort=Sort->next;
		}
}

void Poly::print(){
	Node* printData=first;
	if(printData==0)
		cout<<"0 0"<<endl;
	else if(printData->corr==0)
		cout<<"0 0"<<endl;
	else{	
		while(printData!=0){
			cout<<printData->corr<<" "<<printData->pow<<endl;
			printData=printData->next;
		}
	}
}

Poly Poly::operator+(const Poly& r){
	Poly C;
	Node* A=first;   //指向A的first 
	while(A!=0){       
		C.push(A->corr,A->pow);
		A=A->next;
	}
	Node* B=r.first; //指向B的first
	while(B!=0){
		C.push(B->corr,B->pow);
		B=B->next;
	} 
	return C;
}

Poly Poly::operator*(const Poly& r){
	Poly C;
	Node* A=first;
	Node* B=r.first;
		while(B!=0){
			A=first;
			while(A!=0){
				C.push(A->corr*B->corr,A->pow+B->pow);
				A=A->next;
			}
			B=B->next;	
		}
	return C;
}
