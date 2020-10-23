#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Ensemble.h"


Ensemble::Ensemble(unsigned int cardMax) {
	
	tailleMax = cardMax;
	cardActu = 0;
	if(cardMax!=0) { 
		this->tab = new int[cardMax];
	}
	
}

Ensemble::Ensemble(int t[],unsigned int nbElements) {
	tailleMax = nbElements;
	
	tab = new int[nbElements];
	cardActu=0;
	unsigned int j=0;
	while(j<nbElements) {
		if(!dansEnsemble(t[j])) {
			tab[cardActu] = t[j];
			cardActu++;
		}
		j++;
	}
	
	triEnsemble();
}

Ensemble & Ensemble::operator = ( const Ensemble & unEnsemble )
{
	
}


//-------------------------------------------- Constructeurs - destructeur
Ensemble::Ensemble ( const Ensemble & unEnsemble )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Ensemble>" << endl;
#endif
} //----- Fin de Ensemble (constructeur de copie)


Ensemble::Ensemble ()
{
	
#ifdef MAP
    cout << "Appel au constructeur de <Ensemble>" << endl;
#endif
}


Ensemble::~Ensemble ( ) {
#ifdef MAP
    cout << "Appel au destructeur de <Ensemble>" << endl;
    delete[] tab;
#endif
} //----- Fin de ~Ensemble

void Ensemble::Afficher(void) {
	triEnsemble();
	
	cout<<cardActu<<"\r\n";
	cout<<tailleMax<<"\r\n";
	
	cout<<"{";
	for(unsigned int i=0;i<cardActu;i++) {
		if(i>0) {
			cout<<",";
		}
		cout<<tab[i];
	}
	cout<<"}\r\n";
}

bool Ensemble::EstEgal(const Ensemble & unEnsemble) const {
	
	if(unEnsemble.cardActu != cardActu) {
		return false;
	}
	
	unsigned int i = 0;
	while(i<cardActu) {
		if(unEnsemble.tab[i]!=tab[i]) {
			return false;
		}
		i++;
	}
	return true;
}

crduEstInclus Ensemble::EstInclus(const Ensemble & unEnsemble) const {
	if(EstEgal(unEnsemble)){
		return INCLUSION_LARGE;
	}
	unsigned int ppTaille;
	unsigned int i=0;
	if(cardActu>unEnsemble.cardActu) {
		ppTaille=unEnsemble.cardActu;
		while(i<ppTaille) {
			if(!dansEnsemble(unEnsemble.tab[i])) {
				return NON_INCLUSION;
			}
			i++;
		}
		
 	} else {
		ppTaille = cardActu;
		while(i<ppTaille) {
			if(unEnsemble.dansEnsemble(tab[i])==false) {
				return NON_INCLUSION;
			}
			i++;
		}
	}
	
	return INCLUSION_STRICTE;

	
}


bool Ensemble::dansEnsemble(int val) { //Renvoie true si la valeur est déjà dans l'ens
	unsigned int i=0;
	while(i<cardActu && tab[i]!=val) {
		i++;
	}	
	
	if(i==cardActu) {
		return false;
	}
	return true;
}

void Ensemble::triEnsemble() {
	unsigned int posMin;
	int min;
	int temp;
	
	
	for(unsigned int i=0;i<cardActu;i++) {
		min = tab[i];
		posMin = i;
			
		for(unsigned int j=i+1;j<cardActu;j=j+1) {
			if(tab[j]<min) {
				posMin=j;
				min=tab[j];
			}
		}
		
		if(posMin!=i) {
			temp=tab[i];
			tab[i] = min;
			tab[posMin] = temp;
		}
	}
}

