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

//Quick sort
int Partition(std::vector<int>& nums, int m, int n){
	int pivot = nums[n-1];
	int i = m-1;//Index of the value that is LARGER than pivot.
	for(int j=m; j<n-1; j++){
		if(nums[j]<=pivot){
			i++;
			Swap(nums, j, i);
		}
	}
	Swap(nums, ++i, n-1);
	return i;
}
void QuickSort(std::vector<int>& nums, int m, int n){
	if(n-m<=1) return;
	int medium = Partition(nums, m, n);
	QuickSort(nums, m, medium);
	QuickSort(nums, medium+1, n);
}

int main(){
	std::vector<int> nums = {9,8,7,6,5,4,3,2,1,0};
	PrintArray(nums);
	//MergeSort(nums, 0, nums.size());
	QuickSort(nums, 0, nums.size());
	PrintArray(nums);
	return 0;
}
