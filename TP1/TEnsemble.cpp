#include <iostream>
#include "Ensemble.h"

using namespace std;

int main() {
	
	
	int tab1[] = {1,2,3,4};
	Ensemble ens1(tab1,4);
	ens1.Ajuster(8);
	
	int tab2[] = {-3,-8,3,4,6,-5};
	Ensemble ens2(tab2,6);
	
	ens1.Afficher();
	cout<<ens1.Retirer(ens1)<<"\n";
	ens1.Afficher();
	
	return 0;
}
