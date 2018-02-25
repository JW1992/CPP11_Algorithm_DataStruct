#include <iostream>
#include <vector>
#include <climits>
#include <cassert>

//Left-leaning Red-black tree.




class BST{
public:
	const static bool RED = true;
	const static bool BLACK = false;
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
	int min(){
		if(root==nullptr) return INT_MIN;
		Node *x = root;
		while(x->left!=nullptr) x=x->left;
		return x->val;
	}
	int max(){
		if(root==nullptr) return INT_MAX;
		Node *x = root;
		while(x->right!=nullptr) x=x->right;
		return x->val;
	}
	//return the KEY of the node with largest (inclusive) key, smaller than the input key.
	int floor(int key){
		Node *x = floor(key, root);
		if(x==nullptr) return INT_MIN;
		return x->val;
	}
	//return the KEY of the node with smallest (inclusive) key, Larger than the input key.
	int ceiling(int key){
		Node *x = ceiling(key, root);
		if(x==nullptr) return INT_MAX;
		return x->val;
	}
	//Num of nodes with key smaller (exclusive) than input key
	int rank(int key){
		return rank(key, root);
	}
	//Delete node with key
	void remove(int key){
		root = remove(key, root);
	}
	//Delete node with smallest key
	void removeMin(){
		root = removeMin(root);
	}
	int size(){
		return size(root);
	}
private:
	class Node{
		friend class BST;
		
	public:
		bool color;
		int key;
		int val;
		Node *left=nullptr, *right=nullptr;
		int count;
		Node(int key, int val){
			this->key = key;
			this->val = val;
			this->color = RED;
		}
		Node(int key, int val, bool color){
			this->key = key;
			this->val = val;
			this->color = color;
		}
	};
	
	Node* root = nullptr;
	//The trick here is that by returning the pointer to the node, the whole tree gets recursively updated with new information about the children.
	//Note: I also must update the information about root!
	Node* put(int key, int val, Node* x){
		if(x==nullptr) return new Node(key, val, RED);
		if(key==x->key) x->val = val;
		else if(key < x->key) x->left = put(key, val, x->left);
		else x->right = put(key, val, x->right);
		x->count = 1+size(x->left)+size(x->right);
		
		if(isRed(x->right) && !isRed(x->left)) x = rotateLeft(x);
		if(isRed(x->left) && isRed(x->left->left)) x = rotateRight(x);
		if(isRed(x->left) && isRed(x->right)) flipColors(x);
		
		return x;
	}
	Node* floor(int key, Node *x){
		if(x == nullptr) return nullptr;
		if(key == x->key) return x;
		if(key < x->key) return floor(key, x->left);
		Node *t = floor(key, x->right);
		if(t==nullptr) return x;
		else return t;
	}
	Node* ceiling(int key, Node *x){
		if(x == nullptr) return nullptr;
		if(key == x->key) return x;
		if(key > x->key) return ceiling(key, x->right);
		Node *t = ceiling(key, x->left);
		if(t==nullptr) return x;
		else return t;
	}
	int rank(int key, Node *x){
		if(x==nullptr) return 0;
		if(key==x->key) return size(x->left);
		if(key < x->key) return rank(key, x->left);
		return 1 + size(x->left) + rank(key, x->right);
	}
	int size(Node *x){
		if(x==nullptr) return 0;
		return x->count;
	}
	Node* removeMin(Node *x){
		if(x==nullptr) return nullptr;
		if(x->left==nullptr){
			Node *temp = x->right;
			delete x;
			return temp;
		}
		x->left = removeMin(x->left);
		x->count = 1 + size(x->left) + size(x->right);
		return x;
	}
	Node* remove(int key, Node *x){
		if(x==nullptr) return nullptr;
		if(key < x->key){
			x->left = remove(key, x->left);
			return x;
		}
		if(key > x->key){
			x->right = remove(key, x->right);
			return x;
		}
		if(key == x->key){
			if(x->left == nullptr){
				Node *temp = x->right;
				delete x;
				return temp;
			}
			if(x->right == nullptr){
				Node *temp = x->left;
				delete x;
				return temp;
			}
			Node *t = min(x->right);
			x->val = t->val;
			x->key = t->key;
			x->right = removeMin(x->right);
		}
		x->count = 1 + size(x->left) + size(x->right);
	}
	Node* min(Node *x){
		if(x==nullptr) return nullptr;
		Node *t = min(x->left);
		if(!t) return x;
		return t;
	}
	Node* rotateLeft(Node *h){
		assert(isRed(h->right));
		Node *x = h->right;
		h->right = x->left;
		x->left = h;
		x->color = h->color;
		h->color = RED;
		return x;
	}
	Node* rotateRight(Node *h){
		assert(isRed(h->left));
		Node *x = h->left;
		h->left = x->right;
		x->right = h;
		x->color = h->color;
		h->color = RED;
		return x;
	}
	bool isRed(Node* x){
		if(x==nullptr) return false;
		return x->color==RED;
	}
	void flipColors(Node *h){
		//assert(!isRed(h));
		assert(isRed(h->left));
		assert(isRed(h->right));
		h->color = RED;
		h->left->color = BLACK;
		h->right->color = BLACK;
	}
};

int main(){
	BST bst;
	for(int i=0; i<5; i++) bst.put(i, i);
	std::cout<<bst.min()<<std::endl;
	std::cout<<bst.max()<<std::endl;
	std::cout<<bst.ceiling(3)<<std::endl;
	bst.remove(0);
	std::cout<<bst.min()<<std::endl;
	std::cout<<bst.max()<<std::endl;
	std::cout<<bst.floor(3)<<std::endl;
	return 0;
}
