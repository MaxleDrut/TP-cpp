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
		if(dansEnsemble(t[j])==-1) {
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
	if(EstEgal(unEnsemble)==true){
		return INCLUSION_LARGE;
	}
	unsigned int ppTaille;
	unsigned int i=0;
	if(cardActu>unEnsemble.cardActu) {
		ppTaille=unEnsemble.cardActu;
		while(i<ppTaille) {
			if(dansEnsemble(unEnsemble.tab[i])==-1) {
				return NON_INCLUSION;
			}
			i++;
		}
		
 	} else {
		ppTaille = cardActu;
		while(i<ppTaille) {
			if(unEnsemble.dansEnsemble(tab[i])==-1) {
				return NON_INCLUSION;
			}
			i++;
		}
	}
	
	return INCLUSION_STRICTE;

	
}

crduAjouter Ensemble::Ajouter(int aAjouter) {
	//Déjà présent l'emporte sur plein !
	if(dansEnsemble(aAjouter)!=-1) {
		return DEJA_PRESENT;
	}
	if(tailleMax==cardActu) {
		return PLEIN;
	}
	tab[cardActu]=aAjouter;
	cardActu++;
	triEnsemble();
	return AJOUTE;
	
}

unsigned int Ensemble::Ajuster(int delta) {
	if(delta>0) {
		int *tabTemp = tab;
		tailleMax+=delta;
		tab = new int[tailleMax];
		
		for(unsigned int i=0;i<tailleMax-delta;i++) {
			tab[i] = tabTemp[i];
		}
		delete[] tabTemp;
	}
	
	if(delta<0) {
		int *tabTemp = tab;
		int dimEffect = delta;
		if(delta<cardActu-tailleMax) {//Cas où l'on veut retirer + que possible
			dimEffect=cardActu-tailleMax;
		} else {
			dimEffect=delta;
		}
		
		tailleMax+=dimEffect;

		tab = new int[tailleMax];
		for(unsigned int i=0;i<tailleMax;i++) {
			tab[i] = tabTemp[i];
		}
		
		delete[] tabTemp;
	}
	
	return tailleMax;
}

bool Ensemble::Retirer(int element) {
	int pos = dansEnsemble(element);
	if(pos==-1) { //Pas dans l'ensemble
		Ajuster(cardActu-tailleMax);
		return false;
	}
	//On décale les valeurs d'un indice à partir de celui retiré
	for(unsigned int i=pos;i<cardActu-1;i++) {
		tab[i] = tab[i+1];
	}
	cardActu--;
	Ajuster(cardActu-tailleMax); //On fait appel à ajuster pour que la taille max devienne la cardu actu
	return true;
}

/*unsigned int Ensemble::Retirer(const Ensemble & unEnsemble) {
	unsigned int compte=0;
	if(&unEnsemble!=this) {
		for(unsigned int i=0;i<unEnsemble.cardActu;i++) {
			int pos = dansEnsemble(unEnsemble.tab[i]);
			if(pos!=-1) { //Element trouvé
				for(unsigned int j=pos; j<cardActu-1;j++) {//Décalage des valeurs d'un indice à partir de la val retirée
					tab[j]=tab[j+1];
				}
				cardActu--;
				compte++; //Incrémentaiton du compteur
			}
		}
	} else {//Cas particulier où l'on veut retirer l'ensemble à lui même.
		cardActu=0;
	}

	triEnsemble();
	return compte;
}*/

//Version 2 de la méthode :
unsigned int Ensemble::Retirer(const Ensemble & unEnsemble) {
	unsigned int compte=0;
	unsigned int tailleInitiale = tailleMax;
	for(unsigned int i=0;i<unEnsemble.cardActu;i++) {
		if(Retirer(unEnsemble.tab[i])==true) {
			compte++;
			i--;
		}
	}
	Ajuster(tailleInitiale-tailleMax); //Réallocation à la taille initiale
	return compte;
}


int Ensemble::Reunir(const Ensemble & unEnsemble) {
	int reajust=1; //Devient -1 si on réajuste la taille de this.
	int compte=0; //Compte le nombre de valeurs ajoutées
	for(unsigned int i=0;i<unEnsemble.cardActu;i++) {
		switch(Ajouter(unEnsemble.tab[i])) {
			case AJOUTE:
			compte++;
			break;
			case PLEIN:
			Ajuster(1);
			Ajouter(unEnsemble.tab[i]);
			reajust=-1;
			compte++;
			break;
			default:;
		}
	}
	
	compte = compte*reajust; //S'il y a eu un réajustement, compte devient négatif.
	return compte;
}

unsigned int Ensemble::Intersection(const Ensemble & unEnsemble) {
	int compte=0;
	for(unsigned int i=0;i<cardActu;i++) {
		if(unEnsemble.dansEnsemble(tab[i])==-1) {
			Retirer(tab[i]);
			i--;//Retirer décalle les valeurs d'un cran. Il faut donc aussi décaller notre i d'un cran plus bas
			compte++;
		}
	}
	//Il faut quand même faire un réajuster même si Retirer le fait déjà
	//En effet, si on ne retire aucune valeur alors this ne sera pas réajusté.
	Ajuster(cardActu-tailleMax);
	
	return compte;
}

//Renvoie -1 si l'élément n'est pas dans l'ensemble. Renvoie sa position sinon
int Ensemble::dansEnsemble(int val) const { 
	unsigned int i=0;
	while(i<cardActu && tab[i]!=val) {
		i++;
	}	
	if(i==cardActu) {
		return -1;
	}
	return i;
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

