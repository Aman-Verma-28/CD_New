#include<iostream>
#include<string>

using namespace std;

int main(){
	vector<int> vec = {1,2,3,4,5};
	for(int i=0; i < vec.size() ; i++ ){
		cout<<vec[val]<<endl;
	}

	std::vector<int> v = {6,7,8,9,10};
	vector<int> :: iterator it = v.begin();
	for(it = v.begin(); it!=v.end(); it++ )
		cout<<(*it)<<endl;
	return 0;
}