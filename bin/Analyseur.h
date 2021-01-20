/*************************************************************************
                           Analyseur -  description
                             -------------------
    début                : 20/01/21
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Analyseur> (fichier Analyseur.h) ----------------
#if ! defined ( ANALYSEUR_H )
#define ANALYSEUR_H

//--------------------------------------------------- Interfaces utilisées

//-------------------------------------------------------- Include système
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef unordered_multimap <string,string> ClasseurLogs;
enum codeChargement{SUCCESS,ERROR};



//------------------------------------------------------------------------
// Rôle de la classe <Analyseur>
//  Permet de génerer le top 10 des logs.
//------------------------------------------------------------------------


class Analyseur
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    codeChargement ChargementLogs(const string nomFichier);
    // Mode d'emploi :
    //      Creation d'une unordered_multimap pour stocker les logs
    // Contrat :
    //      Aucun



//-------------------------------------------- Constructeurs - destructeur
    Analyseur ();
    // Mode d'emploi :
    //      Constructeur vide
    // Contrat :
    //      Aucun

    virtual ~Analyseur ();
    // Mode d'emploi :
    //      Destructeur vide
    // Contrat :
    //      Aucun

//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Attributs privé
    ClasseurLogs  logs;

};
//-------------------------------- Autres définitions dépendantes de <Lecteur>
#endif // LECTEUR_H
