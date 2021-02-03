/*************************************************************************
                           Lecteur -  description
                             -------------------
    début                : 20/01/21
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Lecteur> (fichier Lecteur.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//------------------------------------------------------ Include personnel

#include "Lecteur.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

codeLecteur Lecteur::OuvertureLog(const string nomFichier)
//Algorithme: Aucun
{
    flux.open(nomFichier);
    if(flux){
        return SUCCESS;
    }
    cerr<<errOuverture<<nomFichier<<endl;
    return ERROR;
}//----- Fin de OuvertureLog


string * Lecteur::NextLine()
//Algorithme:
//      A chaque fois que l'on rencontre un charactère spécial annocant l'information
//      cherchée, on copie charactère par charactère dans la string correspondante à l'information.
{

    string ligne;
    getline(flux,ligne);
    if(ligne!="\0"){
        string * tabInfo = new string[7];
        int pos=0;
        while(ligne[pos]!=' '){
            tabInfo[0]+=ligne[pos];
            pos++;
        }
        while(ligne[pos]!='['){
            pos++;
        }
        pos++;
        while(ligne[pos]!=' '){
            tabInfo[1]+=ligne[pos];
            pos++;
        }
        while(ligne[pos]!='\"'){
            pos++;
        }
        pos++;
         while(ligne[pos]!='\"'){
            tabInfo[2]+=ligne[pos];
            pos++;
        }
        pos+=2;
        while(ligne[pos]!=' '){
            tabInfo[3]+=ligne[pos];
            pos++;
        }
        pos++;
        while(ligne[pos]!=' '){
            tabInfo[4]+=ligne[pos];
            pos++;
        }
        pos+=2;
        while(ligne[pos]!='\"'){
            tabInfo[5]+=ligne[pos];
            pos++;
        }
        tabInfo[5]+=ligne[pos];
        pos++;
        while(ligne[pos]!='('&& ligne[pos]!='-' && ligne[pos]!='\0'){
            pos++;
        }
        if(ligne[pos]=='-' || ligne[pos]=='\0'){
            tabInfo[6]+=ligne[pos];
        }else{
            pos++;
            while(ligne[pos]!=' ' && ligne[pos]!=';' && ligne[pos]!=')' ){
                tabInfo[6]+=ligne[pos];
                pos++;
            }
        }
        return tabInfo;
    }else{
        string * tabInfo = new string[1];
        tabInfo[0]="Fin";
        return tabInfo;
    }

}//----- Fin de NextLine

//-------------------------------------------- Constructeurs - destructeur

Lecteur::Lecteur()
//Algorithme: Aucun
{
    #ifdef MAP
        cout << "Appel au constructeur vide de <Lecteur>" << endl;
    #endif
}//----- Fin de Lecteur

Lecteur::~Lecteur()
//Algorithme: Aucun
{
    #ifdef MAP
        cout << "Appel au destructeurde <Lecteur>" << endl;
    #endif
    flux.close();
}
