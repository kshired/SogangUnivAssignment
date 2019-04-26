#include <iostream>
#include "GrowableArray.h"
using namespace std;
int main(){
	cout<<"GrowableArray<int> Test"<<endl;
	GrowableArray<int> g(10);
	int i;
	for(i = 0; i < g.length(); i++) g[i] = 2 * i + 3;
	cout<<"g(10)"; g.print();
	g[13] = 13;
	cout<<"g(26)"; g.print();
	
	cout<<"GrowableArray<double> Test"<<endl;
	GrowableArray<double> h(5);
	for(i = 0; i < h.length(); i++) h[i] = 2.231 * i + 3.12;
	cout<<"h(10)"; h.print();
	h[13] = 13.1;
	cout<<"h(26)"; h.print();


	return 0;
}
