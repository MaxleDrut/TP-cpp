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

#include "Analyseur.h"

//----------------------------------------------------------------- Types

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques


int main(int argc, char ** argv){
    cout<<argv[1]<<endl;
    string nomFichier = argv[1];
    Specifications * speci = new Specifications();
    speci->ajoutSpeci("-e","lala");
    Analyseur * analyseur = new Analyseur();
    analyseur->ChargementLogs(nomFichier,speci);
    for(auto & x : analyseur->GetLogs()) {
        cout<<x.first<<";"<<x.second<<endl;
    }
    cout<<"top 10"<<endl;
    analyseur->AfficherTop10();





}
