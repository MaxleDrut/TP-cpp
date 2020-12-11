/*La classe Maillon est un composant de notre listeTrajet : elle contient un trajet
ainsi que le maillon qui le succède.*/

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

/*Met à jour le pointeur vers le maillon suivant*/
void Maillon::SetNext(Maillon * m){
    next=m;
}
