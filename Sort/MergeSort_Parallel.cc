#include <iostream>
#include <vector>
#include <chrono>
#include <time.h>       /* time */
#include <omp.h>

void PrintArray(std::vector<int>& nums){
	for(int i=0; i<nums.size(); i++){
		std::cout<<nums[i]<<" ";
	}
	std::cout<<std::endl;
}

//Merge sort
void Merge(std::vector<int>& nums, int l, int m, int n){
	std::vector<int> temp1(nums.begin()+l, nums.begin()+m);
	std::vector<int> temp2(nums.begin()+m, nums.begin()+n);
	int i=0, j=0, k=l;
	while(i<m-l && j<n-m){
		if(temp1[i]<=temp2[j]) nums[k++] = temp1[i++];
		else nums[k++] = temp2[j++];
	}
	while(i<m-l) nums[k++] = temp1[i++];
	while(j<n-m) nums[k++] = temp2[j++];
}
void MergeSort(std::vector<int>& nums, int m, int n){
	if(n-m<=1) return;
	// printf("Thread %d is sorting %d through %d\n", omp_get_thread_num(), n, m);
	int nTemp = (m+n)/2;
	#pragma omp parallel if(n-m>1000)
	{
		#pragma omp single
		{
			#pragma omp task
			MergeSort(nums, m, nTemp);			
			#pragma omp task
			MergeSort(nums, nTemp, n);	
		}	
	}
	Merge(nums, m, nTemp, n);
}

void MergeSort_Parallel(std::vector<int>& nums, int start, int end) {
    if(start < end-1) {
        //printf("Thread %d is sorting %d through %d\n", omp_get_thread_num(), start, end);
        int middle = (start + end) / 2;

        /* sort both halves in parallel */
        #pragma omp parallel 
        {
            #pragma omp single
            {
                #pragma omp task
                {
                	//printf("Thread %d is sorting %d through %d\n", omp_get_thread_num(), start, middle);
                	//MergeSort_Parallel(nums, start, middle);
                	MergeSort(nums, start, middle);
                }

                #pragma omp task
                {
                	//printf("Thread %d is sorting %d through %d\n", omp_get_thread_num(), middle, end);
                	//MergeSort_Parallel(nums, middle, end);
                	MergeSort(nums, middle, end);
               	}
            }
        }

        /* merge the two halves */
        Merge(nums, start, middle, end);
    }
}

int main(){
	std::vector<int> nums = {9,8,7,6,0,5,0,4,3,2,1,0};
	
	/* initialize random seed: */
  	srand (time(NULL));
  	for (int i =0; i < 1E6; i++){
        int b = rand();
        nums.push_back(b);
    }
    
	/*
	#pragma omp parallel
  	{
    	// Code inside this region runs in parallel.
    	// N lines of "Hello!" will be printed. N equals to the number of cores.
    	printf("Thread %d is running\n", omp_get_thread_num());
    	printf("Hello!\n");
  	}
  	*/
  	/* enable recursive parallel blocks */
    omp_set_nested(1);
    
	auto start = std::chrono::high_resolution_clock::now();
	
	//MergeSort(nums, 0, nums.size());
	MergeSort_Parallel(nums, 0, nums.size());
	
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout<<"Elapsed time "<< elapsed.count() << "S" <<std::endl;
	
	//PrintArray(nums);
	return 0;
}
