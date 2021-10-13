 /*
   Author：B062040027 鄭乃心
   Date：2020..
   Purpose：HW7產生亂數
*/

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>
using namespace std;

int main(){
	srand(time(NULL));
	ofstream fout("input.txt");
	int I=100, d;
	fout<< I << endl;
	while(I){
		d = rand();
		fout << d << endl;
		I--;
	}
	fout.close();
}