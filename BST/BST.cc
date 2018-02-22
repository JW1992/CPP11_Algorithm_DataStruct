#include <iostream>
#include <vector>
#include <climits>

class Node{
public:
	int key;
	int val;
	Node *left, *right;
	int count;
	Node(int key, int val){
		this->key = key;
		this->val = val;
	}
};

class BST{
public:
	int get(int key){
		Node* x = root;
		while(x!=nullptr){
			if(key==x->key) return x->val;
			if(key<x->key) x=x->left;
			else x=x->right;
		}
		return INT_MIN;
	}
	void put(int key, int val){
		root = put(key, val, root);
	}
private:
	Node* root = nullptr;
	//The trick here is that by returning the pointer to the node, the whole tree gets recursively updated with new information about the children.
	Node* put(int key, int val, Node* x){
		if(x==nullptr) return new Node(key, val);
		if(key==x->key) x->val = val;
		else if(key < x->key) x->left = put(key, val, x->left);
		else x->right = put(key, val, x->right);
		return x;
	}
};

int main(){
	BST bst;
	for(int i=0; i<5; i++) bst.put(i, i);
	for(int i=0; i<2; i++) std::cout<<bst.get(i)<<std::endl;;
	return 0;
}
