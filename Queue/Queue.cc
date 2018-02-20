#include <iostream>
#include <climits>

struct Node{
public:
	Node(int n){
		value = n;
		next = nullptr;
	}
	Node(){
		value = 0;
		next = nullptr;
	}
	int value;
	Node* next;
	bool hasNext(){
		return next != nullptr;
	}
	void setNext(Node* nextNode){
		this->next = nextNode;
	}
	Node* getNext(){
		return next;
	}
private:	
	
};

class MyQueue{
public:
	MyQueue(){
		N = 0;
	}
	MyQueue(int n){
		N = 0;
		this->push_back(n);
	}
	~MyQueue(){
		while(header->hasNext()){
			Node* temp = header;
			header = header->next;
			delete temp; temp = nullptr;
		}
		delete header; header = nullptr;
	}
	bool isEmpty(){
		return N==0;
	}
	void push_back(int n){
		Node* temp = new Node(n);
		if(N==0){
			tail = temp;
			header = tail;
		}
		else{
			tail->next = temp;
			tail = tail->next;
		}
		N++;
	}
	int pop_front(){
		if(N==0) return INT_MIN;
		int temp = header->value;
		header = header->next;
		N--;
		if(N==0) tail = nullptr;
		return temp;
	}
	void print(){
		if(N==0){
			std::cout<<"Empty \n";
			return;
		}
		Node* temp = header;
		while(temp->hasNext()){
			std::cout << " " << temp->value;
			temp = temp->next;
		}
		std::cout << " " << temp->value << std::endl;
	}
private:
	int N;
	Node* header=nullptr;
	Node* tail=nullptr;
};

int main(){
	MyQueue* queue = new MyQueue(1);
	for(int i=0; i<20; ++i)
		queue->push_back(i);
	queue->print();
	for(int i=0; i<10; ++i)
		int temp = queue->pop_front();
	queue->print();
	for(int i=0; i<20; ++i)
		int temp = queue->pop_front();
	queue->print();
	return 0;
}
