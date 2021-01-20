/*************************************************************************
                           Specifications  -  description
                             -------------------
    début                : 20/01/2021
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Specifications> ----------------
#include "Specifications.h"

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
//------------------------------------------------------ Include personnel
//------------------------------------------------------------- Constantes
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

string Specifications::GetSpeci(string nomSpeci) {
    //Algorithme : donne la valeur de l'attribut lié
    unsigned int i=0;
    while(i<nbSpeci && nomSpeci!=tabSpeci[i][0]) { //Localisation de la ligne de la spéci
        i++;
    }
    if(i==nbSpeci) {
        return nullptr;
    } else {
        return tabSpeci[i][1];
    }

} //----- Fin de GetSpeci


Specifications::Specifications() {
    //Algorithme : Crée le tableau des spécifications
    //Associe chaque attribut à sa valeur, nullptr par défaut
    #ifdef MAP
        cout << "Appel au constructeur de <Specifications>" << endl;
    #endif
    tabSpeci = new string*[nbSpeci];
    for(unsigned int i=0;i<nbSpeci;i++) {
        tabSpeci[i] = new string[2];

        tabSpeci[i][0] = listeSpeci[i];
        tabSpeci[i][1] = "\0";
    }

    cout<<tabSpeci[0][0];
    cout<<tabSpeci<<endl;
}

Specifications::~Specifications() {
    #ifdef MAP
        cout << "Appel au destructeur de <Specifications>" << endl;
    #endif
    delete[] tabSpeci;
}

//-------------------------------------------------------- Méthodes privées

codeAjout Specifications::ajoutSpeci(string nomSpeci, string attribut) {
    unsigned int i=0;

    cout<<tabSpeci[0][0];
    /*while(i<nbSpeci && nomSpeci!=tabSpeci[i][0]) { //Localisation de la ligne de la spéci
        i++;
    }

    if(i==nbSpeci) {
        return PAS_TROUVE;
    } else {
        tabSpeci[i][1] = attribut;
        return AJOUTE;
    }*/

}

bool Specifications::estSpeci(string nomSpeci) const {
    unsigned int i=0;
    while(i<nbSpeci && nomSpeci!=listeSpeci[i]) {
        i++;
    }
    if(i==nbSpeci) {
        return false; //Pas trouvé
    } else {
        return true;
    }

}
