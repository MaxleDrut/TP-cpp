#include <iostream>
#include "Ensemble.h"

using namespace std;

int main() {
	
	
	int tab1[] = {5,4,3,6,1};
	Ensemble ens1(tab1,5);
	
	int tab2[] = {1,4, 5, 3};
	Ensemble ens2(tab2,5);
	
	cout<<ens1.EstEgal(ens2);
	
	return 0;
}
