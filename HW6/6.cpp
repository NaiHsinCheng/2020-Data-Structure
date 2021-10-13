 /*
   Author：B062040027 鄭乃心
   Date：2020.11.11
   Purpose：給予一串數字，找出所有出現次數為奇數之數字
*/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct treeNode{					//節點
	int val;
	treeNode* left;
	treeNode* right;
	treeNode* parent;
	treeNode():left(nullptr),right(nullptr),parent(nullptr){};
	treeNode(int v):val(v),left(nullptr),right(nullptr),parent(nullptr){};
};

class BST{						//二元搜索數的class
	public:
		treeNode* root;
		BST():root(nullptr){};		//根
		treeNode* find(int k);		//尋找節點 有的話返回該節點
		treeNode* successor(int k);	//尋找後繼節點
		void insert(int k);		//插入節點
		void remove(int k);		//移除節點
		void printNode(treeNode* current);		//print node 
		void printLeft(treeNode* current);		//print left
		void printRight(treeNode* current);		//print right
};

int main(){
	while(1){
		vector<int> input;
		int x;
		while(1){
			cin >> x;
			if(x == -1)
				break;
			else
				input.push_back(x);	//用vector記錄輸入節點
		}
		BST* tree = new BST();				//建立一個二元搜索樹
		for(int I=0; I<input.size(); I++){
			if(tree->find(input[I]) != nullptr)		//如果有該節點 代表前面出現基數次 那就刪掉
				tree->remove(input[I]);
			else
				tree->insert(input[I]);		//沒有該節點 代表前面出現偶數次 加入二元搜索樹
		}

		cout << setw(6) << "node:";
		tree->printNode(tree->root);
		cout << endl << setw(6) << "left:";
		tree->printLeft(tree->root);
		cout << endl << setw(6) << "right:";
		tree->printRight(tree->root);	
		cout << endl << endl;	
	}
}

treeNode* BST::find(int k){		//尋找
	treeNode* current = root;
	while(current!=nullptr && current->val !=k){
		if(current->val < k )
			current = current->right;
		else
			current = current->left;
	}
	if(current != nullptr)
		return current;
	else
		return nullptr;
}
treeNode* BST::successor(int k){		//找後繼節點 該節點右子樹中最靠左的節點
	treeNode* current = find(k);
	if(current->right != nullptr){	//如果有右子樹 就找最靠左的節點
		current = current->right;
		while(current->left != nullptr)
			current = current->left;
		return current;
	}
	while(current->parent != nullptr && current->parent->right != current)	//current的右子樹不存在左子樹
		current = current->parent;	//向上找父節點第一個有右孩子且不存在current的祖先
	return current->parent;
	
}
void BST::insert(int k){		//插入
	treeNode* in = new treeNode(k);
	if(root == nullptr)
		root = in;
	else{
		treeNode* current = root;
		while(1){
			if(current->val < in->val){
				if(current->right != nullptr){
					current = current->right;
				}else{
					current->right = in;
					in->parent = current;
					break;
				}
			}else{
				if(current->left != nullptr){
					current = current->left;
				}else{
					current->left = in;
					in->parent = current;
					break;
				}
			}
		}
	}

}
void BST::remove(int k){	//移除
	treeNode* del = find(k);
	treeNode* temp;	//代替del的節點
	if(del->left == nullptr && del->right == nullptr)	//del沒有左右孩子
		temp=nullptr;
	else if(del->right == nullptr){		//del只有右孩子
		temp = del->left;
		temp->parent = del->parent;
	}
	else if(del->left == nullptr){		//del只有左孩子
		temp = del->right;
		temp->parent = del->parent;
	}
	else{			//del有左右孩子
		temp = successor(k);
		treeNode* tempRight = temp->right;
		//用tempRight取代temp
		if(temp->right != nullptr)		//temp的右孩子的parent指針要指到temp的parent
			tempRight->parent = temp->parent;
		if(temp->parent->right == temp)	//如果temp是右孩子 temp的parent的right指針要指向tempRight
			temp->parent->right = tempRight;
		else
			temp->parent->left = tempRight;
		//用temp取代del
		temp->right = del->right;
		temp->left = del->left;
		temp->parent = del->parent;
	}

	if(del->parent != nullptr){	//如果del不是根
		if(del->parent->right == del)		//如果del是右孩子
			del->parent->right = temp;
		else		//如果del是左孩子
			del->parent->left = temp;
	}else
		root = temp;

	delete del;
}
void BST::printNode(treeNode* current){
	if(current != nullptr){
		printNode(current->left);
		cout<< setw(3) << current->val;
		printNode(current->right);
	}
}
void BST::printLeft(treeNode* current){		//print left
	if(current != nullptr){
		printLeft(current->left);
		if(current->left==nullptr)
			cout << setw(3) << '0';
		else
			cout << setw(3) << current->left->val;
		printLeft(current->right);
	}
}
void BST::printRight(treeNode* current){		//print right
	if(current != nullptr){
		printRight(current->left);
		if(current->right==nullptr)
			cout << setw(3) << '0';
		else
			cout << setw(3) << current->right->val;
		printRight(current->right);
	}
}