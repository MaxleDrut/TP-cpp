/*************************************************************************
                           Specifications  -  description
                             -------------------
    début                : 20/01/2021
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

#include "Specifications.h"

const string Specifications::GetSpeci(string nomSpeci) const {
    //Algorithme : renvoie la valeur de l'attribut lié
    unsigned int i=0;
    while(i<nbSpeci && nomSpeci!=tabSpeci[i][0]) { //Localisation de la ligne de la spéci
        i++;
    }
    if(i==nbSpeci) {
        return nullptr;
    } else {
        return tabSpeci[i][1];
    }

}//---------- Fin de GetSpeci


Specifications::Specifications() {
//Constructeur par défaut :
//      Crée le tableau 2D référençant les différentes spécifications et leurs attributs
    #ifdef MAP
        cout << "Appel au constructeur de <Specifications>" << endl;
    #endif
    tabSpeci = new string*[nbSpeci];
    for(unsigned int i=0;i<nbSpeci;i++) {
        tabSpeci[i] = new string[2];
        tabSpeci[i][0] = listeSpeci[i];
        tabSpeci[i][1] = "";
    }
}//---------- Fin du constructeur par défaut

Specifications::~Specifications() {
//Destructeur par défaut :
//      Détruit le tableau des spécifications
    #ifdef MAP
        cout << "Appel au destructeur de <Specifications>" << endl;
    #endif
    for(unsigned int i=0;i<nbSpeci;i++) {
        delete[] tabSpeci[i];
    }
    delete[] tabSpeci;
}//---------- Fin du destructeur par défaut

//-------------------------------------------------------- Méthodes privées

codeAjout Specifications::ajoutSpeci(string nomSpeci, string attribut) {
//Algorithme :
//      Renseigne le champ d'attribut pour une spéficiation renseignée
//      Si elle existe parmi les spéci attendues

    unsigned int i=0;
    while(i<nbSpeci && nomSpeci!=tabSpeci[i][0]) { //Localisation de la ligne de la spéci
        i++;
    }
    if(i==nbSpeci) {
        return PAS_TROUVE;
    } else {
        tabSpeci[i][1] = attribut;
        return AJOUTE;
    }
}//---------- Fin de ajoutSpeci

bool Specifications::estSpeci(string nomSpeci) const {
//Algorithme :
//      Détermine si un nom de spécification fait partie de ceux attendus par l'application
    unsigned int i=0;
    while(i<nbSpeci && nomSpeci!=listeSpeci[i]) {
        i++;
    }
    if(i==nbSpeci) {
        return false; //Pas trouvé
    } else {
        return true;
    }
}//---------- Fin de estSpeci
