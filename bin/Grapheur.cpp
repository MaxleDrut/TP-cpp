/*************************************************************************
                           Grapheur  -  description
                             -------------------
    début                : 22/01/2021
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

#include "Grapheur.h"

void Grapheur::GenererGraph(string nomFichier, ClasseurLogs logs) {
    genererClasseurHits(logs);
}

Grapheur::Grapheur() {
    #ifdef MAP
        cout<<"Appel au constructeur de <Grapheur>";
    #endif
}

Grapheur::~Grapheur() {
    #ifdef MAP
        cout<<"Appel au destructeur de <Grapheur>";
    #endif
}

void Grapheur::genererClasseurHits(ClasseurLogs logs) {
    string ligne;

    ClasseurLogs::iterator it;
    for(it = logs.begin(); it!=logs.end();++it) {
        cout<<it->first<<" "<<it->second;
        //Couple non existant :
        if(hits.find(ligne) == hits.end()) {
            hits[ligne] = 1;
        } else {
            hits[ligne]++;
        }
    }

}
