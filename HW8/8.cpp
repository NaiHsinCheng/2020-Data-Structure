 /*
   Author：B062040027 鄭乃心
   Date：2020.12.6
   Purpose：Huffman壓縮軟體
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <deque>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

class Node{		//Huffman tree的節點
	public:
		int val;
		int freq;
		Node* left;
		Node* right;
		Node(char v, int f, Node* L, Node* R){
			val = v;
			freq = f;
			left = L;
			right = R;
		}
};
void Encode(Node* ptr, string s, map<char,string> &e);	//編碼
bool comp(Node* a, Node* b);	//給sort函數使用 定義比較兩個Node大小的方法
float getFileSize(string &sFileName);		//獲取檔案大小
void print_bit(ofstream &out, string s);
vector<char> splitStr(string s, map<string, char> en);		//分割結果

int main(int argh, char* argv[]){
	/*壓縮*/
	if(strcmp(argv[1], "-c") == 0){
		/*開檔*/
		string file_name = argv[3];
		ifstream in(file_name, ios::in | ios::binary);	//以binary模式開檔
		if(!in){
			cout << "無法開啟檔案" << endl;
			return 0;
		}
	
		/*讀檔＆計算頻率*/
		char ch;		//以字元為單位
		map<char, int> count;		//紀錄char 出現的頻率
		map<char, int>::iterator iter;	
		while(!in.eof()){
			in.get(ch);
			if(!in.eof()){
				iter = count.find(ch);		//檢查該字元是否出現過
				if(iter != count.end())
				iter->second++;		//出現過：出現次數＋1
				else
					count[ch] = 1;		//沒出現過：出現次數=1
			}
		}
				/*	//print出現頻率表
				for(map<char, int>::iterator I = count.begin(); I != count.end(); I++){
					cout << I->first << " " << I->second << endl;
				}
				cout<< endl;*/
			
		in.close();
	
		/*利用Huffman求出編碼表*/
		deque<Node*> tree;	//存Nodes
		for(map<char, int>::iterator I = count.begin(); I != count.end(); I++){	//製作節點
			tree.push_back(new Node(I->first, I->second, nullptr, nullptr));
		}
		//按照字元出現頻率排序tree中的節點，取出出現頻率小的兩個將他們合併，在存回tree中
		for(int I = 0; I < count.size()-1; I++){
			sort(tree.begin(), tree.end(), comp);		//先從小到大排序
			Node* ptr1 = tree.front();		//取出最小的兩個節點
			tree.pop_front();
			Node* ptr2 = tree.front();
			tree.pop_front();
			if(ptr1->val < ptr2->val){		//字典順序較小的Node設為左子樹 較大者設為右子樹
				Node* parent = new Node(ptr1->val, ptr1->freq + ptr2->freq, ptr1, ptr2);
				tree.push_back(parent);
			}else{
				Node* parent = new Node(ptr2->val, ptr2->freq + ptr1->freq, ptr2, ptr1);
				tree.push_back(parent);
			}
		}
		map<char, string> encode;		//記錄編碼結果
		Encode(tree.front(), string(""), encode);

		/*檔案頭部寫入*/
		string output_file = argv[5];
		ofstream out(output_file, ios::out | ios::binary);		//創檔
		//第一行寫入原始檔案大小
		out << getFileSize(file_name) << endl;
		//第二行寫入壓縮後檔案大小
		out << getFileSize(output_file) << endl;
		//第三行寫入壓縮率
		out << getFileSize(file_name)/getFileSize(output_file) << endl;
		//第四行寫入編碼表總行數
		out << encode.size() <<endl;		
		//接下來的n行寫入編碼表
		for(map<char, string>::iterator I = encode.begin(); I != encode.end(); I++){		
			out << I->first << " = " << I->second << endl;
		}
		//最後寫入壓縮編碼
		string end = "";
		ifstream in2(file_name, ios::in | ios::binary);
		while(!in2.eof()){
			in2.get(ch);
			if(!in2.eof()){
				end += encode[ch];
			}
		}
		//寫入之後復原要有幾bit
		out << end.length() <<endl;	
		//寫入拼接的輸出
		print_bit(out, end);	//把string 1bit 1 bit輸出
		in2.close();
		out.close();

		//標準輸出內容
		cout << getFileSize(file_name) << endl;
		cout << getFileSize(output_file) << endl;
		cout << getFileSize(file_name)/getFileSize(output_file) << endl;
		cout << encode.size() <<endl;
		for(map<char, string>::iterator I = encode.begin(); I != encode.end(); I++){		
			cout << I->first << " = " << I->second << endl;
		}

	/*解壓縮*/
	}else{
		/*開檔*/
		string file_name = argv[3];
		string output_file = argv[5];
		ifstream in(file_name, ios::in | ios::binary);	//以binary模式開檔
		if(!in){
			cout << "無法開啟檔案" << endl;
			return 0;
		}
		/*讀&創建編碼表*/
		string temp;
		getline(in,temp);		//讀出（跳過）前面三行
		getline(in,temp);
		getline(in,temp);
		getline(in,temp);		//第四行 編碼表有幾行
		map<string, char> encode;		//記錄編碼表
		char in1, t;
		string in2;
		for(int I = 0; I < stoi(temp); I++){
			in.get(in1);
			in.get(t);in.get(t);in.get(t);		//' = '
			getline(in,in2);
			encode[in2]=in1;
		}
		/*把編碼換成字元*/
		getline(in,temp);		//取得復原後該有幾bit
		vector<char> v;		//分割後的每個編碼內容
		string r="";
		char ch;
		int count=0;
		bool flag = false;
		ofstream out(output_file, ios::out | ios::binary);
		while(!in.eof() && !flag){
			in.get(ch);			//讀出壓縮內容	
			ch <<= 1;		//將最高位左移 取有效的7bit
			for(int pos = 0; pos < 7; pos++){
				string tmp = (ch << pos&0x80) ? "1":"0";
				r.append(tmp);		//將取出的bit拼接成string
				++count;
				if(count >= stoi(temp)){
					flag=true;
					break;
				}
			}
		}
		v = splitStr(r, encode);
		for(int I=0; I<v.size(); I++){
			out << v[I];
		}
		out << endl;

		in.close();
		out.close();
	}
}

void Encode(Node* ptr, string s, map<char,string> &e){		//印出編碼
	if(ptr->left == nullptr || ptr->right == nullptr){
		e[ptr->val] = s;
		return;
	}
	if(ptr->left) Encode(ptr->left, string(s+"0"), e);
	if(ptr->right) Encode(ptr->right, string(s+"1"), e);
}

bool comp(Node* a, Node* b){	//給sort函數使用 定義比較兩個Node大小的方法
	if(a->freq < b->freq)
		return true;
	else if(a->freq > b->freq)
		return false;
	else
		return a->val < b->val;
	//兩個node出現相同頻率時 依照字典順序排序
}

float getFileSize(string &sFileName){		//獲取檔案大小
	struct stat buf;
	int iRet = stat(sFileName.c_str(), &buf);
	return buf.st_size;
}

vector<char> splitStr(string s, map<string, char> en){		//分割結果
	vector<char> result;
	while(s.length() != 0){
		for(map<string, char>::iterator I = en.begin(); I != en.end(); I++){
			if(s.find(I->first)==0){
				result.push_back(I->second);
				s.erase(0,I->first.length());
				break;
			}
		}
	}
	return result;
}

void print_bit(ofstream &out, string s){
	int pos = 0, i = 0;//pos记录已经拼接的bit位
	char value = 0;//这里value的ASCII码为000 0000
	for (i = 0; i < s.length(); i++){		//遍历c中的每一个字符
		value <<= 1;	//value左移1位，value为000 0000，右邊補零
		if (s[i] == '1'){  //需要寫入的二進位是1
			value |= 1;	//000 0000 | 000 0001 = 000 0001
		}
		if (++pos == 7){   //寫滿七位寫入文件 最高位是正負符號
			out.put(value);	//將字元value寫入文件
			value = 0;	//把value的ASCII重置為000 0000
			pos = 0;		//bit位再從第一位開始
		}
	}

	if (pos){    //最後的編碼不足7bit時
		value = value << (7 - pos);		//把他左移直到有7bit
		out.put(value);
	}
}
