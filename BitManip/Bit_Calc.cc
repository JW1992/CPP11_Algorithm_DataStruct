#include <iostream>
#include <climits>

int Add(int a, int b){
	int adv = 0;
	while(b != 0){
		adv = a & b;
		a = a ^ b;
		b = adv << 1;
	}
	return a;
}

int main(){
	std::cout << "Adding 40 and 13: "<<std::endl;
	std::cout << Add(40, 13) << std::endl;
}
