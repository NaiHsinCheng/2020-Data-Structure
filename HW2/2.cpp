 /*
   Author：B062040027 鄭乃心
   Date：2020.09.08
   Purpose：集合類別五種運算
*/

#include <iostream>
#include <string.h>
using namespace std;

class TSet {

	public:
		TSet(){
			lenA=0;
		}

		TSet(char aa[]){	
			A[0]=aa[0];						//先讓aa第一個元素存入Ａ
			lenA=1;							//Ａ的內容物數量變為1
			int lenaa = strlen(aa);			//當初輸入的字元數
			int check;

			for(int I=1;I<lenaa;I++){		//不重複地將aa的元素存入Ａ
				check=0;
				for(int j=0;j<lenA;j++){
					if(aa[I]==A[j]){
						check=1;
						break;
					}
				}
				if(check==1)
					continue;
				A[lenA]=aa[I];
				lenA++;
			}
			char temp;
			for(int j=lenA-1;j>0;j--){		//排列字元
				for(int I=0;I<=j-1;I++){
					if(A[I]>A[I+1]){
						temp=A[I];
						A[I]=A[I+1];
						A[I+1]=temp;
					}
				}
			}
		  
		}

		void out(){					//打印
			if(lenA==0)
				cout<<"{}"<<endl;
			else{
				cout << "{";
				for(int I=0;I<lenA;I++){
					cout << A[I];
				}
				cout << "}"<< endl;
			}
		}

		TSet operator+(const TSet &aa){		//重載運算子＋
			char all[256]="";				//宣告一個陣列
			for(int I=0;I<lenA;I++){		//把Ａ集合的元素放入all陣列
				all[I]=A[I];
			}
			for(int I=0;I<aa.lenA;I++){		//把Ｂ集合的元素放入all陣列
				all[lenA+I]=aa.A[I];
			}
			TSet temp(all);					//建立一個all陣列的集合
			return temp;
		}

		TSet operator*(const TSet &aa){			//重載運算子＊
			char all[256]="";
			int count=0;
			for(int I=0;I<lenA;I++){			//找出重複的元素放入all陣列
				for(int j=0;j<aa.lenA;j++){
					if(A[I]==aa.A[j]){
						all[count]=A[I];
						count++;
						break;
					}
				}
			}

			if(count==0)		//若無重複 返回空集合
				return TSet();
			return TSet(all);
		}

		TSet operator-(const TSet &aa){			//重載運算子-
			char all[256]="";
			int check=0;						//是否重複
			int count=0;						//重複元素的數量
			for(int I=0;I<lenA;I++){			//檢查是否重複，沒重複就加入all陣列
				check=0;
				for(int j=0;j<aa.lenA;j++){
					if(A[I]==aa.A[j]){
						check=1;
						break;
					}
				}
				if(check==0){
					all[count]=A[I];
					count++;
				}
			}

			if(strlen(all)==0)
				return TSet();
			return TSet(all);
		}

		string operator>=(const TSet &aa){
			int count=0;
			for(int I=0;I<lenA;I++){				//數重複的數量
				for(int j=0;j<aa.lenA;j++){
					if(A[I]==aa.A[j]){
						count++;
						break;
					}
				}
			}
			if(count==aa.lenA)						//數量相等則包含
				return " contains ";
			else
				return " does not contain ";
		}

		string in(char aa){
			int check=0;
			for(int I=0;I<lenA;I++){			//檢查aa是否在集合裡面
				if(A[I]==aa){
					check=1;
					break;
				}
			}
			if(check==0)
				return " is not in ";
			else
				return " is in ";
			
		}
		
	private:
		char A[256];	//長度為256的陣列來表示一個集合
		int lenA;		//內容物數量
};

int main(){
	int N;		//資料組數
	int I=1;
	cin >> N;
	while(I<=N){
		char strA[80]="";			//每一組的第一列與第二列
		char strB[80]="";
		char x;
		cin.get();
		cin.getline(strA,80);	//輸入
		cin.getline(strB,80);
		cin>>x;

		TSet A(strA);			//設成集合
		TSet B(strB);
		TSet C=A+B;
		TSet D=A*B;
		TSet E=A-B;
		TSet F=B-A;

		cout << endl << "Test Case " << I << ":" << endl;
		cout<<"A:";			//打印集合
		A.out();	
		cout<<"B:";
		B.out();
		cout<<"A+B:";
		C.out();
		cout<<"A*B:";
		D.out();
		cout<<"A-B:";
		E.out();
		cout<<"B-A:";
		F.out();
		cout<< "A" << (A>=B) << "B" << endl;
		cout<< "B" << (B>=A) << "A" << endl;
		cout<< "\'" << x << "\'" << (A.in(x)) << "A" << endl;
		cout<< "\'" << x << "\'" << (B.in(x)) << "B" << endl;
		I++;
	}
}