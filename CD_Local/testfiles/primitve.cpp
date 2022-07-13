#include<iostream>

using namespace std;



int main(){
	int a;
	a=2;
	int b=a++;
	a++;
	for(int i=0; i<5; i++ ) 
		cout<<a;
	
	return 0;
}