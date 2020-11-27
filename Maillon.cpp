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
}

Maillon::Maillon(const Maillon & unMaillon) {
    this->contenu = unMaillon.GetContenuConst();
    this->next = unMaillon.GetNextConst();
}


Trajet * Maillon::GetContenu()  {
    return contenu;
}
Maillon * Maillon::GetNext() {
    return next;
}

//Pour le constructeur de copie
Trajet * Maillon::GetContenuConst() const {
    return contenu;
}
Maillon * Maillon::GetNextConst() const {
    return next;
}
void Maillon::SetNext(Maillon * m){
    next=m;
}
