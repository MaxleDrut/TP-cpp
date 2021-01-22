/*************************************************************************
                           Interpreteur -  description
                             -------------------
    début                : 20/01/21
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Grapheur> (fichier Trajet.h) ----------------
#if ! defined ( GRAPHEUR_H )
#define GRAPHEUR_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------ Include personnel
#include <unordered_map>
#include "Analyseur.h"
#include <string>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef unordered_map<string,int> ClasseurHits;
//------------------------------------------------------------------------
// Rôle de la classe <Grapheur>
// Permet de générer un graphe à partir de l'umap d'Analyseur

//------------------------------------------------------------------------

class Grapheur
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    void GenererGraph(string nomFichier, ClasseurLogs logs);
    // Mode d'emploi :
    //      A partir du recensement des logs, crée un fichier graph
    // Contrat :
    //      Aucun

//-------------------------------------------- Constructeurs - destructeur

    Grapheur();
    // Mode d'emploi :
    //      Constructeur par défaut
    // Contrat :
    //      Aucun
    virtual ~Grapheur();
    // Mode d'emploi :
    //      Destructeur par défaut
    // Contrat :
    //      Aucun


//------------------------------------------------------------------ PRIVE
private :
//----------------------------------------------------- Méthodes protégées
    void genererClasseurHits(ClasseurLogs logs);
    string genererCode();
//----------------------------------------------------- Attributs protégés
    ClasseurHits hits;
};
//-------------------------------- Autres définitions dépendantes de <Grapheur>
#endif // GRAPHEUR_H
