 /*
   Author：B062040027 鄭乃心
   Date：2020.09.17
   Purpose：西洋棋騎士走完棋盤的順序
*/

#include <iostream>
using namespace std;

int backtracking(int chess[7][7],int number, int i,int j,int now);		//backtracking遞迴法
void printOut(int c[7][7],int n);									//打印
bool check(int i, int j, int n, int k, int choosed[7][7]);			//檢查是否可以移動到下一個位置
void move(int* i,int* j, int k);									//移動i,j
	


int main(){
				

	for(int n=1;n<=6;n++){
		cout<<"n="<<n<<endl;
		int i=1;				//目前所在位置(i,j)
		int j=1;
		int ans=0;			//無解=1 有解=0
		int now=1;			//現在進行到的數字
		int chess[7][7];		//為了接下來不用顧慮矩陣是從0開始 所以先加一 讓他從1開始
		for(int m=0;m<7;m++)		//初始化
			for(int l=0;l<7;l++)
				chess[m][l]=0;

		ans=backtracking(chess,n,i,j,now);	//有解return 0 無解return 1
		if(ans==0)
			printOut(chess,n+1);
		else
			cout<<"no solution"<<endl<<endl;
	}

}

void printOut(int c[7][7], int n){
	for(int I=1;I<n;I++){
		for(int j=1;j<n;j++){
			cout<<c[I][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl; 
}

bool check(int i, int j, int n, int k, int choosed[7][7]){
	if(i-2>=1 && j+1<=n && k==1 && choosed[(i-2)*(n+1)+(j+1)]==0){
		return true;
	}else if(i-1>=1 && j+2<=n  && k==2 && choosed[i-1][j+2]==0){	
		return true;
	}else if(i+1<=n && j+2<=n  && k==3 && choosed[i+1][j+2]==0){
		return true;
	}else if(i+2<=n && j+1<=n  && k==4 && choosed[i+2][j+1]==0){
		return true;
	}else if(i+2<=n && j-1>=1  && k==5 && choosed[i+2][j-1]==0){
		return true;
	}else if(i+1<=n && j-2>=1  && k==6 && choosed[i+1][j-2]==0){
		return true;
	}else if(i-1>=1 && j-2>=1  && k==7 && choosed[i-1][j-2]==0){
		return true;
	}else if(i-2>=1 && j-1>=1  && k==8 && choosed[i-2][j-1]==0){
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

int backtracking(int chess[7][7],int number, int i,int j,int now){
			int tempI,tempJ;
			chess[i][j]=now;
			if(now==number*number)				//終止條件
				return 0;
			
			for(int k=1;k<=8;k++){
				if(check(i, j, number, k, chess)){				//如果可以移動到下一個位置
					tempI=i;
					tempJ=j;
					move(&tempI, &tempJ, k);					//移動到下一個位置
					if(backtracking(chess,number, tempI,tempJ,now+1)==1){   	//進行遞迴 如果到後面被return 1 則k＋＋
						if(k==8){										//但如果k=8 後面被return 1 則無解
							chess[i][j]=0;
							return 1;
						}else
							continue;
					}else{
						return 0;							//如果遞迴到最後都return 0 則有解
					}
				}else if(k==8){					//k1~k8都無法
					chess[i][j]=0;				//清除現在的數字 然後return 1
					return 1;
				}else{						//k(x)無法 則continue到k(x+1)
						continue;
				}
			}
			return 0;
		
}
