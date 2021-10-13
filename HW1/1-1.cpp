/*
   Author：B062040027 鄭乃心
   Date：2020.09.07
   Purpose：N階魔方陣
*/

#include <iostream>
using namespace std;

int main(){
	//一階
	cout<< "1" << endl << endl;

	//三 五 七 九階
	for(int I=3;I<=9;I=I+2){
		int ms[I][I];					//建立魔方矩陣
		for(int j=0;j<I;j++){
			for(int k=0;k<I;k++){
				ms[j][k]=0;				//先全部填零
			}
		}
		int number=1;					//要放的數字
		ms[0][I/2]=number;				//第一排中央設好1的位置
		int a=0;							//記錄陣列元素位置
		int b=I/2;
		for(int h=1;h<=I*I-1;h++){
			int tempA=a;					//暫存原始位置
			int tempB=b;

			if(a-1<0)					//下一個位置
				a=a-1+I;
			else
				a=a-1;
			if(b-1<0)
				b=b-1+I;
			else
				b=b-1;

			number++;					//下一個數字

			if(ms[a][b]==0)				//空的話就填入
				ms[a][b]=number;
			else{						//滿的話重新找位置
				if(tempA+1>I-1)					
					a=tempA+1-I;
				else
					a=tempA+1;
				b=tempB;
				ms[a][b]=number;
			}
				
		}
		for(int m=0;m<I;m++){
			for(int n=0;n<I;n++){
				cout << ms[m][n] <<" ";				//打印出來
			}
			cout<< endl;
		}
		cout<< endl;
	}
}