#include <iostream>
#include <vector>
#include <climits>

void PrintArray(std::vector<int>& nums){
	for(int i=0; i<nums.size(); i++){
		std::cout<<nums[i]<<" ";
	}
	std::cout<<std::endl;
}
void swap(std::vector<int>& nums, int m, int n){
	int nTemp = nums[m];
	nums[m] = nums[n];
	nums[n] = nTemp;
}


class BinaryHeapMax{
public:
	void insert(int n){
		nums.push_back(n);
		swim(nums.size()-1);
	}
	int removeMax(){
		if(nums.size()==0) return INT_MIN;
		int temp = nums[0];
		swap(nums, 0, nums.size()-1);
		nums.pop_back();
		if(nums.size()>0) sink(0);
	}
	int getMax(){
		if(nums.size()>0) return nums[0];
	}
	void heapify(){
		
	}
	void print(){
		PrintArray(nums);
	}
private:
	std::vector<int> nums;
	//sink equals to heapify: it makes sure that the sub-tree with root i becomes a binary heap.
	void sink(int i){
		int l=2*i+1;
		int r=2*i+2;
		int largest = i;
		if(l<nums.size() && nums[l]>nums[largest]) largest = l;
		if(r<nums.size() && nums[r]>nums[largest]) largest = r;
		if(i!=largest){
			swap(nums, i, largest);
			sink(largest);
		}
	}
	void swim(int i){
		if(i==0) return;
		int parent = (i-1)/2;
		if(nums[i]>nums[parent]){
			swap(nums, i, parent);
			swim(parent);
		}
	}
};

int main(){
	BinaryHeapMax bh;
	for(int i=0; i<5; i++) bh.insert(i);
	bh.print();
	for(int i=0; i<2; i++) int temp = bh.removeMax();
	bh.print();
	return 0;
}
