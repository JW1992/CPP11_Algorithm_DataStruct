#include <iostream>
#include <climits>

class MyArray{
public:
	MyArray(){
		N = 0;
		nums = new int[nSize];
	}
	~MyArray(){
		delete[] nums;
		nums = nullptr;
	}
	bool isEmpty(){
		return N==0;
	}
	void push_back(int n){
		if(N==nSize) resize(nSize*2);
		nums[N++] = n;
	}
	int pop_back(){
		if(isEmpty()) return INT_MIN;
		if(N<=nSize/4) resize(nSize/2);
		return nums[N--];
	}
	bool insert(int n, int index){
		if(index >= N) push_back(n);
		else{
			if(N==nSize) resize(nSize*2);
			for(int i=index; i<N; ++i) nums[i+1] = nums[i];
			nums[index] = n;
		}
	}
	void print(){
		for(int i=0; i<N; ++i) std::cout<<" "<<nums[i];
		std::cout<<std::endl;
	}
private:
	int N;
	
	//Use numbers that are 2^n
	int nSize = 16;
	int* nums;
	void resize(int capacity){
		nSize = capacity;
		int* copy = new int[capacity];
		for(int i=0; i<N; ++i) copy[i] = nums[i];
		delete[] nums;
		nums = copy;
		copy = nullptr;
	}
};

int main(){
	MyArray array;
	for(int i=0; i<20; ++i)
		array.push_back(i);
	array.print();
	for(int i=0; i<17; ++i)
		int temp = array.pop_back();
	array.print();
	for(int i=0; i<20; ++i)
		array.insert(i*2, i);
	array.print();
	return 0;
}
