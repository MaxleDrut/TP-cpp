/*************************************************************************
                           Main  -  description
                             -------------------
    début                : 13/12/20
    copyright            : (C) 2020 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Main> (fichier Main.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//------------------------------------------------------ Include personnel

#include "Lecteur.h"

//----------------------------------------------------------------- Types

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques


int main(int argc, char * argv[]){

    string nomFichier = argv[0];
    Lecteur * lecteur = new Lecteur();
    lecteur->OuvertureLog(nomFichier);
    string * info = lecteur->NextLine();
    for(int i=0; i<7;i++){
        cout<<info[i]<<endl;
    }





}
