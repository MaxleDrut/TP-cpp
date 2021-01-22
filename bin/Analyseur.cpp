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
#include <bits/stdc++.h>

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Analyseur :: ChargementLogs(Specifications * speci)
//Algorithme:
//      Pour chaque logs retourné par le Lecteur, on vérifie que les informations correspondent
//      aux les options précisées dans la commande. SI c'est le cas on
//      insert dans l'unordered_multimap logs, la requête en clé et le referer en Attribut.
{
    Lecteur * lecteur = new Lecteur();
    codeLecteur code = lecteur->OuvertureLog(speci->GetSpeci("log"));
    if(code==SUCCESS){
        string * info = lecteur->NextLine();
        bool verifSpeci=true;

        while(info[0]!="Fin"){
            for(int i=0; i<7;i++){
                if(speci->GetSpeci("-ip")!="\0" && speci->GetSpeci("-ip")!=info[0]){
                    verifSpeci=false;
                }
                if(speci->GetSpeci("-t")!="\0" &&speci->GetSpeci("-t")!=info[1]){
                    verifSpeci=false;
                }
                if(speci->GetSpeci("-e")!="\0"){
                    verifSpeci=exclusion(info[2]);
                }
                if(speci->GetSpeci("-err")!="\0" && stoi(info[3])==200){
                    verifSpeci=false;
                }

                if(speci->GetSpeci("-p")!="\0" && stoi(info[4])<stoi(speci->GetSpeci("-p")) ){
                    verifSpeci=false;
                }

                if(speci->GetSpeci("-os")!="\0" && (info[6]!=speci->GetSpeci("-os"))){
                    verifSpeci=false;
                }
            }
            if(verifSpeci){
                logs.insert(make_pair<string,string>(move(info[2]),move(info[5])));
            }
            info = lecteur->NextLine();
        }

    }
    if(speci->GetSpeci("-g")!="\0"){
        Grapheur * graph = new Grapheur();
        graph->GenererGraph(speci->GetSpeci("-g"),logs);
        delete graph;
    }
    delete lecteur;

}//------ Fin de ChargementLogs

Requetes Analyseur::GenererTop10()
//Algorithme : Aucun
{
    map <string,int> mymap;
    for(auto & x : logs) {
        if(mymap.empty() || mymap.find(x.first)==mymap.end()){
            mymap.emplace(x.first,1);
        }else if(!mymap.empty() && mymap.find(x.first)!=mymap.end()){
            mymap[x.first]++;
        }
    }
    Requetes top10;
    for(auto & x : mymap)
    {
        top10.emplace(x.second,x.first);
    }
    return top10;
}//----- Fin de GenererTop10

void Analyseur::AfficherTop10()
//Algorithme : Aucun
{
    Requetes top10 = GenererTop10();
    string * tab = ordreAlphabet(top10);
    for(int i=0; i<10;i++) {
        cout<<tab[i]<<endl;
    }

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

string * Analyseur::ordreAlphabet(Requetes top10)
//Algorithme :
//      Parcours le top 10 jusqu'à 10 iterations. Lorsqu'il y a plusieur
//      fois des requetes avec le même nombre de hits, on sort (méthode de la stl)
//      le tableau tab qui contient les requêtes. Puis on ajoute chaque requetes
//      dans affiche.
{
    Requetes :: reverse_iterator it;
    int pos1=0;
    string * affiche = new string[10];
    it=top10.rbegin();
    while(pos1<10 && it!=top10.rend()) {
        long long unsigned int pos=0;
        string * tab = new string[top10.count(it->first)];
        long long unsigned int nb = top10.count(it->first);
        int val=it->first;
        while(pos<nb){
            tab[pos]=it->second;
            pos++;
            ++it;
        }
        sort(tab,tab+nb);
        pos=0;
        while(pos1<10 && pos<nb){
            affiche[pos1]=tab[pos] + " ("+ to_string(val)+" hits)";
            pos++;
            pos1++;
        }

    }
    return affiche;
}
