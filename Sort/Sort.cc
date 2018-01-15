#include <iostream>
#include <vector>

void PrintArray(std::vector<int>& nums){
	for(int i=0; i<nums.size(); i++){
		std::cout<<nums[i]<<" ";
	}
	std::cout<<std::endl;
}
void Swap(std::vector<int>& nums, int m, int n){
	int nTemp = nums[m];
	nums[m] = nums[n];
	nums[n] = nTemp;
}


//Heap sort
//Merge sort
void Merge(std::vector<int>& nums, int l, int m, int n){
	int temp1[m-l];
	int temp2[n-m];
	for(int i=0; i<m-l; i++) temp1[i] = nums[l+i];
	for(int i=0; i<n-m; i++) temp2[i] = nums[m+i];
	int i=0; int j=0;
	while(i<m-l && j<n-m){
		if(temp1[i]>temp2[j]) nums[l+i+j] = temp2[j++];
		else nums[l+i+j] = temp1[i++];
	}
	while(i<m-l) nums[l+i+j] = temp1[i++];
	while(j<n-m) nums[l+i+j] = temp2[j++];
}
void MergeSort(std::vector<int>& nums, int m, int n){
	if(n-m<=1) return;
	int medium = (m+n+1)/2;
	MergeSort(nums, m, medium);
	MergeSort(nums, medium, n);
	Merge(nums, m, medium, n);
}

//Quick sort (three way): unstable
void Partition(std::vector<int>& nums, int l, int r, int&i, int &j){
	int pivot = nums[r-1];
	int m = l;
	while(m<r){
		if(nums[m]==pivot) m++;
		else if(nums[m]<pivot) Swap(nums, l++, m++);
		else{
			Swap(nums, m, r-1);
			r--;
		}
	}
	i = l;
	j = m;
}
void QuickSort(std::vector<int>& nums, int m, int n){
	if(n-m<=1) return;
	int i, j;
	Partition(nums, m, n, i, j);
	QuickSort(nums, m, i);
	QuickSort(nums, j, n);
}

int main(){
	std::vector<int> nums = {9,8,7,6,0,5,0,4,3,2,1,0};
	PrintArray(nums);
	//MergeSort(nums, 0, nums.size());
	QuickSort(nums, 0, nums.size());
	PrintArray(nums);
	return 0;
}
