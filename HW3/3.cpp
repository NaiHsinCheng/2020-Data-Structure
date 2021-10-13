 /*
   Author：B062040027 鄭乃心
   Date：2020.09.13
   Purpose：西洋棋騎士走完棋盤的順序
*/

#include <iostream>
using namespace std;

class info{									//自製stack
	public:
		int i;
		int j;
		int k;
		info *next;
};

info* push(info* top, int I, int J, int K);			//自製stack.push()
info* pop(info* top);							//自製stack.pop()
void printOut(int *c,int n);
bool check(int i, int j, int n, int k, int *choosed);	//檢查是否可以移動到下一個位置
void move(int* i,int* j, int k);					//移動i,j



int main(){
	int i;						//目前所在位置(i,j)
	int j;						
	int k;						//目前所在位置的接下來可能移動的位置
	int number;					//此棋盤的位置數
	int ans;						//無解=1 有解=0
	info* top=NULL;					

	for(int n=1;n<=6;n++){
		cout<<"n="<<n<<endl;

		int chess[n+1][n+1];		//為了接下來不用顧慮矩陣是從0開始 所以先加一 讓他從一開始
		for(i=1;i<n+1;i++)		//初始化
			for(j=1;j<n+1;j++)
				chess[i][j]=0;

		number=n*n;
		i=1;
		j=1;
		ans=0;
		
		for(int now=1;now<=number;now++){
			chess[i][j]=now;
			if(now==number)			//終止條件
				break;
			
			for(k=1;k<=8;k++){
				if(check(i, j, n, k, chess[0])){		//如果可以移動到下一個位置
					top=push(top, i, j, k);		//把這個位置紀錄進去stack
					//cout<<"("<<i<<","<<j<<","<<k<<")"<<endl;
					move(&i, &j, k);			//移動到下一個位置
					break;
				}else if(k==8){					//k1~k8都無法
					if(now==1){				//移動（1,1）的位置
	 						chess[i][j]=0;
	 						if(j+1<=n){		//往右移
	 							j++;
	 							now=0;
	 							continue;
	 						}
	 						else if(i+1<=n){	//往下移
	 							i++;
	 							j=1;
	 							now=0;
	 							continue;
	 						}
	 						else{
	 							ans=1;		//無法移動（1,1）則無解
	 							break;
	 						}
	 				}
					while(k==8){				//如果退回一格 那格的k如果還是等於8 就會無限循環 為了不要無限循環 所以while(k==8)
						chess[i][j]=0;			
						i=top->i;
						j=top->j;
						k=top->k;
						now=chess[i][j];
						top=pop(top);
						if(now==1){
							ans=1;
							break;
						}
					}
				}else{						//k(x)無法 則continue到k(x+1)
					continue;
				}
			}

			if(ans==1)					//無解
				break;
		}
		if(ans==0)
			printOut(chess[0],n+1);
		else
			cout<<"no solution"<<endl<<endl;
	}

}

info* push(info* top, int I, int J, int K){
	info* temp;
	temp = (info*)malloc(sizeof(info));

	temp->i=I;
	temp->j=J;
	temp->k=K;
	temp->next=NULL;
	temp->next=top;
	top=temp;
	return top;
}

info* pop(info* top){
	info* temp;
	temp=top;
	top=top->next;
	free(temp);
	
	return top;
}

void printOut(int *c, int n){
	for(int I=1;I<n;I++){
		for(int j=1;j<n;j++){
			cout<<c[I*n+j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl; 
}

bool check(int i, int j, int n, int k, int *choosed){
	if(i-2>=1 && j+1<=n && k==1 && choosed[(i-2)*(n+1)+(j+1)]==0){
		return true;
	}else if(i-1>=1 && j+2<=n  && k==2 && choosed[(i-1)*(n+1)+(j+2)]==0){	//因為一開始宣告chess的大小是n+1 所以要*(n+1)
		return true;
	}else if(i+1<=n && j+2<=n  && k==3 && choosed[(i+1)*(n+1)+(j+2)]==0){
		return true;
	}else if(i+2<=n && j+1<=n  && k==4 && choosed[(i+2)*(n+1)+(j+1)]==0){
		return true;
	}else if(i+2<=n && j-1>=1  && k==5 && choosed[(i+2)*(n+1)+(j-1)]==0){
		return true;
	}else if(i+1<=n && j-2>=1  && k==6 && choosed[(i+1)*(n+1)+(j-2)]==0){
		return true;
	}else if(i-1>=1 && j-2>=1  && k==7 && choosed[(i-1)*(n+1)+(j-2)]==0){
		return true;
	}else if(i-2>=1 && j-1>=1  && k==8 && choosed[(i-2)*(n+1)+(j-1)]==0){
		return true;
	}else{
		return false;
	}
}

void move(int* i,int* j, int k){
	if(k==1){
		*i=*i-2;
		*j=*j+1;
	}else if(k==2){
		*i=*i-1;
		*j=*j+2;
	}else if(k==3){
		*i=*i+1;
		*j=*j+2;
	}else if(k==4){
		*i=*i+2;
		*j=*j+1;
	}else if(k==5){
		*i=*i+2;
		*j=*j-1;
	}else if(k==6){
		*i=*i+1;
		*j=*j-2;
	}else if(k==7){
		*i=*i-1;
		*j=*j-2;
	}else if(k==8){
		*i=*i-2;
		*j=*j-1;
	}
}

