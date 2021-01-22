/*************************************************************************
                           Analyseur -  description
                             -------------------
    début                : 22/01/21
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Analyseur> (fichier Analyseur.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système


//------------------------------------------------------ Include personnel

#include "Analyseur.h"
#include "Lecteur.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Analyseur :: ChargementLogs(const string nomFichier, Specifications * speci)
//Algorithme:
//      Pour chaque logs retourné par le Lecteur, on vérifie que les informations correspondent
//      aux les options précisées dans la commande. SI c'est le cas on
//      insert dans l'unordered_multimap logs, la requête en clé et le referer en Attribut.
{
    Lecteur * lecteur = new Lecteur();
    codeLecteur code = lecteur->OuvertureLog(nomFichier);
    if(code==SUCCESS){
        string * info = lecteur->NextLine();
        bool verifSpeci=false;

        while(info[0]!="Fin"){
            for(int i=0; i<7;i++){
                if(speci->GetSpeci("-ip")==info[0]){
                    verifSpeci=true;
                }
                if(speci->GetSpeci("-t")==info[1]){
                    verifSpeci=true;
                }
                if(speci->GetSpeci("-e")!="\0"){

                    verifSpeci=exclusion(info[2]);
                }
                if(speci->GetSpeci("-err")!="\0" && stoi(info[3])!=200){
                    verifSpeci=true;
                }

                if(speci->GetSpeci("-p")!="\0" && stoi(info[4])>=stoi(speci->GetSpeci("-p")) ){
                    verifSpeci=true;
                }

                if(info[6]==speci->GetSpeci("-os")){
                    verifSpeci=true;
                }
            }
            if(verifSpeci){
                logs.insert(make_pair<string,string>(move(info[2]),move(info[5])));
            }

            info = lecteur->NextLine();
        }

    }

}//------ Fin de ChargementLogs

void Analyseur::AfficherTop10(requetes req)
//Algorithme : Aucun
{


}//----- Fin de AfficherTop10


const ClasseurLogs Analyseur::GetLogs() const
//Algorithme:Aucun
{
    return logs;
}//----- Fin de GetLogs

//-------------------------------------------- Constructeurs - destructeur

Analyseur::Analyseur()
//Algorithme: Aucun
{
    #ifdef MAP
        cout << "Appel au constructeur vide de <Analyseur>" << endl;
    #endif
}//----- Fin de Analyseur

Analyseur::~Analyseur()
//Algorithme: Aucun
{
    #ifdef MAP
        cout << "Appel au destructeurde <Analyseur>" << endl;
    #endif
}//----- Fin de ~Analyseur

//----------------------------------------------------- Méthodes privées
bool Analyseur :: exclusion(string doc)
//Algorithme :
//      Parcours la string doc jusqu'à arriver au format du document. Puis on vérifie
//      si le format est un format image, css ou javascript. Dans ce cas
//      il faut exclure le document et donc la méthode renvoie faux.
{
    int pos=0;
    string format;
    const string tabFormat[] = {".png",".jpg",".gif",".css",".json",".ico"};
    int sizeTabFormat=6;
    while(doc[pos]!='.'){
        pos++;
    }

    while(doc[pos]!='\0'){
        format+=doc[pos];
        pos++;
    }
    for(int i=0; i<sizeTabFormat; i++){
        if(format==tabFormat[i]){
            return false;
        }
    }
    return true;

}//----- fin d'exclusion
