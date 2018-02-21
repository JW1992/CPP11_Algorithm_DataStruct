#include <iostream>
#include <functional> //for std::hash
#include <string>
#include <list>

class MyHashSet_Str{
public:
	MyHashSet_Str(){
		BUCKET = 1E4;
    	table = new std::list<std::string>[BUCKET];
	}
	MyHashSet_Str(int nums){
		BUCKET = nums;
    	table = new std::list<std::string>[BUCKET];
	}
	void insert(std::string s){
		int index = hasher(s)%BUCKET;
		table[index].push_back(s);
	}
	bool erase(std::string s){
		int index = hasher(s)%BUCKET;
		
		std::list<std::string>::iterator i;
		for(i=table[index].begin(); i!= table[index].end(); i++){
			if(*i == s) break;
		}
		if(i == table[index].end()) return false;
		table[index].erase(i);
		return true;
	}
	bool find(){
		return true;
	}
private:
	int BUCKET;
	std::list<std::string> *table;
    std::hash<std::string> hasher;
};

int main(){
	std::string str = "Hello World";
    std::hash<std::string> hasher;
    auto hashed = hasher(str); //returns std::size_t
    std::cout << hashed << '\n';
    
    
	MyHashSet_Str set(1E3);
	for(int i=0; i<20; ++i)
		set.insert("Foo"+i);
	for(int i=0; i<20; ++i)
		set.erase("Foo"+i);
	return 0;
}
