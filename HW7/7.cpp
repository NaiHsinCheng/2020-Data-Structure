/*
   Author：B062040027 鄭乃心
   Date：2020.11.15
   Purpose：撰寫三種排序演算法與直接呼叫C/C++兩種排序函式
*/

#include <iostream>
#include <algorithm>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void insertion_sort(int* arr, int size);
void merge_sort(int *A,int n);
void merge(int *A,int *L,int leftCount,int *R,int rightCount);
void quick_sort(int* arr, int front, int end);
int partition(int *arr, int front, int end);
void swap(int &a, int &b);
int cmp(const void *arg1, const void *arg2 );

int main(){
	//檔案讀入
	ifstream fin("input.txt");			
	string s;
	fin >> s;
	int size = atoi(s.c_str());
	int arr[size];
	int I=0;
	do{
		fin >> arr[I];		//建立檔案內的矩陣
		I++;
	}while(!fin.eof());
	fin.close();

	int* arr2 = new int[size];	//複製四個為排序的arr陣列
	int* arr3 = new int[size];
	int* arr4 = new int[size];
	int* arr5 = new int[size];
	for(int i = 0; i < size; i++) {
    		arr2[i] = arr[i];
    		arr3[i] = arr[i];
    		arr4[i] = arr[i];
    		arr5[i] = arr[i];
	}

	double START,END; 		//記錄時間
	cout << "time=>" << endl;
	//A
	START = clock();
	insertion_sort(arr, size);
	END = clock();
	cout << "Insertion sort: " << (END - START) / CLOCKS_PER_SEC << endl;
	//檔案寫出	
	ofstream fout1("outputA.txt");
	fout1 << "Insertion Sort"<< endl;
	for(int I=0; I <size; I++){
		fout1 << arr[I] << endl;
	}
	fout1.close();

	//B
	START = clock();
	merge_sort(arr2, size);
	END = clock();
	cout << "Merge sort: " << (END - START) / CLOCKS_PER_SEC << endl;
	ofstream fout2("outputB.txt");
	fout2 << "Merge Sort"<< endl;
	for(int I=0; I <size; I++){
		fout2 << arr2[I] << endl;
	}
	fout2.close();

	//C
	START = clock();
	quick_sort(arr3, 0, size-1);
	END = clock();
	cout << "Quick sort: " << (END - START) / CLOCKS_PER_SEC << endl;
	//檔案寫出	
	ofstream fout3("outputC.txt");
	fout3 << "Quick Sort"<< endl;
	for(int I=0; I <size; I++){
		fout3 << arr3[I] << endl;
	}
	fout3.close();

	//D
	START = clock();
	qsort(arr4, size, sizeof(arr4[0]), cmp);
	END = clock();
	cout << "qsort: " << (END - START) / CLOCKS_PER_SEC << endl;
	//檔案寫出	
	ofstream fout4("outputD.txt");
	fout4 << "C qsort()"<< endl;
	for(int I=0; I <size; I++){
		fout4 << arr4[I] << endl;
	}
	fout4.close();

	//E
	START = clock();
	sort(arr5, arr5+size);
	END = clock();
	cout << "sort: " << (END - START) / CLOCKS_PER_SEC << endl;
	//檔案寫出	
	ofstream fout5("outputE.txt");
	fout5 << "C++ sort()"<< endl;
	for(int I=0; I <size; I++){
		fout5 << arr5[I] << endl;
	}
	fout5.close();
}

//插入排序
void insertion_sort(int* arr, int size){
	for(int I=1; I <size; I++){				//插入排序
		int key = arr[I];
		int j = I - 1;
		while(key < arr[j] && j>=0){
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = key;
	}
}
//歸併排序
void merge_sort(int *A, int n) {
	int mid, i, *L, *R;
	if(n < 2) return; //小於兩個元素不用排列

	mid = n/2;  // 中間index

	// 分割成兩個陣列
	L = new int[mid];
	R = new int [n - mid];

	for(i = 0;i<mid;i++) L[i] = A[i];
	for(i = mid;i<n;i++) R[i-mid] = A[i];

	merge_sort(L,mid);  // 排列左陣列
	merge_sort(R,n-mid);  // 排列右陣列
	merge(A,L,mid,R,n-mid);  // 把左右兩陣列合併
	
	delete [] R;
	delete [] L;
}
void merge(int *arr, int *L, int leftCount, int *R, int rightCount) {
	int i, j, k;		// i紀錄L的index  j紀錄R的index  k紀錄A的index
	i = 0;
	j = 0;
	k = 0;

	while(i<leftCount && j< rightCount) {
		if(L[i]  < R[j]) arr[k++] = L[i++];
		else arr[k++] = R[j++];
	}
	while(i < leftCount)
		arr[k++] = L[i++];
	while(j < rightCount)
		arr[k++] = R[j++];
}
//快速排序
void quick_sort(int* arr, int front, int end){
	if(front < end){
		int pivot = partition(arr, front, end);
		quick_sort(arr, front, pivot-1);
		quick_sort(arr, pivot+1, end);
	}
}
int partition(int *arr, int front, int end){		//找出分割的主元素
	int pivot = arr[end];		//先假設主元素是最後一個元素
	int I = front-1;
	int j;
	for(j=front; j<end; j++){
		if(arr[j]<pivot){
			I++;
			swap(arr[I],arr[j]);
		}
	}
	I++;
	swap(arr[I],arr[j]);
	return I;
}
void swap(int &a, int &b){		//a b交換
	int temp = a;
	a = b;
	b = temp;
}
//qsort
int cmp(const void *a,const void *b){
	return (*(int*)a-*(int*)b);
}