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
#include <map>
#include <set>
#include <unordered_map>
#include "Analyseur.h"
#include <string>
using namespace std;

//------------------------------------------------------------- Constantes
const string errOuvrir = "Erreur 006 : Impossible de creer le fichier : ";
//------------------------------------------------------------------ Types
typedef map<string,int> DicoLiens;
typedef set<string> DicoBulles;
typedef unordered_multimap <string,string> ClasseurLogs;
enum codeGraph{OUVERT,PAS_OUVERT};
//------------------------------------------------------------------------
// Rôle de la classe <Grapheur>
// Permet de générer un graphe à partir de l'umap d'Analyseur

//------------------------------------------------------------------------

class Grapheur
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    codeGraph GenererGraph(string nomFichier, ClasseurLogs logs);
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
    string genererCode(ClasseurLogs logs);
//----------------------------------------------------- Attributs protégés
};
//-------------------------------- Autres définitions dépendantes de <Grapheur>
#endif // GRAPHEUR_H
