/*
   Author：B062040027 鄭乃心
   Date：2020.09.07
   Purpose：印出 1 到 N 之間所有整數之階乘，N<=50
*/

#include <iostream>
using namespace std;

int main(){
	int pointer;			//最高位的位置
	int a[100];				//用陣列存放資料
	a[0]=1;						//初始為1
	int plus;					//進位
	int N;
	cin >> N;						//輸入Ｎ
	while(N){
		pointer=0;
		for(int j=0;j<100;j++){
				a[j]=0;
		}
		a[0]=1;
		plus=0;

		for(int I=1;I<=N;I++){
			for(int j=0;j<=pointer;j++){	//陣列元素分別乘以Ｉ
				a[j]=a[j]*I;
			}
			for(int j=0;j<=pointer;j++){	//處理進位
				plus=a[j]/10;
				a[j]=a[j]%10;
				a[j+1]=a[j+1]+plus;
				if(j==pointer && plus>0)
					pointer++;
			}
			cout << I << "!=";				//打印
			for(int j=pointer;j>=0;j--){
				cout<<a[j];
			}
			cout<<endl;
		}
		cout << endl;
		cin >> N;
	}
}