/*La classe Maillon représente un noeud contenant un trajet simple ou composé.
Comme il va composer une chaine avec d'autres maillons, il pointe sur
le prochain maillon.*/


#include <iostream>
#include <cstring>
using namespace std;

#include "Maillon.h"


Maillon::Maillon (Trajet * t, Maillon * suiv){
    #ifdef MAP
        cout << "Appel au constructeur de <Maillon>" << endl;
    #endif
    contenu = t;
    next = suiv;
}

Maillon::Maillon () {
    #ifdef MAP
        cout << "Appel au constructeur vide de <Maillon>" << endl;
    #endif
    contenu = nullptr;
    next = nullptr;
}

Maillon::~Maillon() {
    #ifdef MAP
        cout << "Appel au destructeur de <Maillon>" << endl;
    #endif
    delete contenu;
    if(next!=nullptr) { //Destruction du maillon suivant
        delete next;
    }
}


/*Retourne un pointeur vers le trajet contenu dans le maillon.*/
Trajet * Maillon::GetContenu()  {
    return contenu;
}

/*Retourne un pointeur vers le maillon suivant du maillon actuel*/
Maillon * Maillon::GetNext() {
    return next;
}


/*Recois en paramètre un poiteur vers un maillon et permet de modifier
son suivant.*/
void Maillon::SetNext(Maillon * m){
    next=m;
}
