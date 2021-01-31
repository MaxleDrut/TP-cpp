/*************************************************************************
                           Grapheur  -  description
                             -------------------
    début                : 22/01/2021
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

#include "Grapheur.h"

codeGraph Grapheur::GenererGraph(string nomFichier, ClasseurLogs logs) {
    ofstream flux(nomFichier);
    if(flux) {
        flux<<genererCode(logs);
        flux.close();
        return OUVERT;
    } else {
        cerr<<errOuvrir<<nomFichier<<endl;
        return PAS_OUVERT;
    }
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

string Grapheur::genererCode(ClasseurLogs logs) {
    //Création de l'umap qui associe les referers aux targets
    string ligne;
    DicoLiens liens; //Compte les liens referer/target entre les différentes pages
    /*Pour les liens, on utilise une map (et non pas une umap) car le code de sortie nécessite
    d'avoir un ordre précis pour qu'il puisse être comparé dans nos tests*/
    DicoBulles bulles; //Référencie toutes les bulles
    ClasseurLogs::iterator it;
    for(it = logs.begin(); it!=logs.end();++it) {
        ligne = "\""+it->second +"\" -> \""+ it->first+"\"";
        //Ajout à la liste des bulles
        bulles.insert("\""+it->first+"\"");
        bulles.insert("\""+it->second+"\"");

        //Création ou itération des liens
        //Couple non existant :
        if(liens.find(ligne) == liens.end()) {
            liens[ligne] = 1;
        } else {
            liens[ligne]++;
        }
    }

    //Génération du code
    string code = "digraph {\n";
    //Ajout du code des bulles :
    for(DicoBulles::iterator itb=bulles.begin(); itb!=bulles.end();++itb) {
        code+="\t"+*itb+";\n";
    }

    for(DicoLiens::iterator itl=liens.begin();itl!=liens.end();++itl) {
        code+="\t"+itl->first+" [label=\""+to_string(itl->second)+"\"];\n";
    }
    code+="}";
    return code;
}
