/*************************************************************************
                           Grapheur  -  description
                             -------------------
    début                : 22/01/2021
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

#include "Grapheur.h"

codeGraph Grapheur::GenererGraph(string nomFichier, ClasseurLogs logs) {
//Algorithme :
//      Crée un flux sortant pour le fichier graphe, et y inclue son contenu si
//      l'ouverture a été possible. Renvoie un code d'erreur indiquant l'état du flux.
    ofstream flux(nomFichier);
    if(flux) {
        flux<<genererCode(logs);
        flux.close();
        return OUVERT;
    } else {
        cerr<<errOuvrir<<nomFichier<<endl;
        return PAS_OUVERT;
    }
}//---------- Fin de GenererGraph

Grapheur::Grapheur() {
    #ifdef MAP
        cout<<"Appel au constructeur de <Grapheur>";
    #endif
}//---------- Fin du constructeur

Grapheur::~Grapheur() {
    #ifdef MAP
        cout<<"Appel au destructeur de <Grapheur>";
    #endif
}//---------- Fin du destructeur

string Grapheur::genererCode(ClasseurLogs logs) {
//Algorithme :
//     Parcours le classeur référençant tous les targets et referers pour dresser 2 structures :
//     1 : DicoBulles, un set qui référence tous les referers/targets pour dresser les bulles du graphiques
//     2 : CompteLiens, une map qui a pour First une string qui référence les couples Referers->Target et pour Second la cardinalité du couple
//     Après avoir créé ces deux structures, on peut facilement générer une string contenant le code du fichier .dot !

    string ligne;
    CompteLiens liens;
    /*Pour les liens, on utilise une map (et non pas une umap) car le code de sortie nécessite
    d'avoir des éléments ordonnés pour qu'il puisse être comparé dans nos tests*/
    DicoBulles bulles;
    ClasseurLogs::iterator it;
    for(it = logs.begin(); it!=logs.end();++it) {
        ligne = "\""+it->second +"\" -> \""+ it->first+"\"";
        //Ajout à la liste des bulles
        bulles.insert("\""+it->first+"\"");
        bulles.insert("\""+it->second+"\"");

        //Création ou itération des liens
        if(liens.find(ligne) == liens.end()) {
            liens[ligne] = 1;
        } else {
            //Sinon, incrémentation du nombre du lien
            liens[ligne]++;
        }
    }

    //Génération du code
    string code = "digraph {\n";
    //Ajout du code des bulles :
    for(DicoBulles::iterator itb=bulles.begin(); itb!=bulles.end();++itb) {
        code+="\t"+*itb+";\n";
    }
    //Code des liens :
    for(CompteLiens::iterator itl=liens.begin();itl!=liens.end();++itl) {
        code+="\t"+itl->first+" [label=\""+to_string(itl->second)+"\"];\n";
    }
    code+="}";
    return code;
}//---------- Fin de genererCode 
