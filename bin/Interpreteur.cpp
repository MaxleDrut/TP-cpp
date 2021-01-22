/*************************************************************************
                           Interpreteur  -  description
                             -------------------
    début                : 22/01/2021
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Interpreteur> ----------------
#include "Interpreteur.h"
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
//------------------------------------------------------ Include personnel
//------------------------------------------------------------- Constantes
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

Specifications * Interpreteur::LireCommande(int argc, char ** argv) {
    //Algorithme : donne la valeur de l'attribut lié
    Specifications * spe = new Specifications();
    

} //----- Fin de GetSpeci


Interpreteur::Interpreteur() {
    //Constructeur vide
    #ifdef MAP
        cout << "Appel au constructeur de <Interpreteur>" << endl;
    #endif
}

Interpreteur::~Interpreteur() {
    #ifdef MAP
        cout << "Appel au destructeur de <Interpreteur>" << endl;
    #endif
}
