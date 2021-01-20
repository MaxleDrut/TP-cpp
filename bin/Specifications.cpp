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
    tabSpeci[1][1];
    return nullptr;
} //----- Fin de GetSpeci


Specifications::Specifications() {
    //Algorithme : Crée le tableau des spécifications
    //Associe chaque attribut à sa valeur, nullptr par défaut
    #ifdef MAP
        cout << "Appel au constructeur de <Specifications>" << endl;
    #endif
    string tabSpeci[nbSpeci][2];
    for(unsigned int i=0;i<nbSpeci;i++) {
        tabSpeci[i][0] = listeSpeci[i];
        tabSpeci[i][1] = nullptr;
        tabSpeci[i][2] = nullptr;
    }
}
