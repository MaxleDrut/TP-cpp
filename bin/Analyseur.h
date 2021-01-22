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
#include "Specifications.h"

//-------------------------------------------------------- Include système
#include <string>
#include <fstream>
#include <unordered_map>
#include <map>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef unordered_multimap <string,string> ClasseurLogs;
typedef map <string,int> requetes;


//------------------------------------------------------------------------
// Rôle de la classe <Analyseur>
//  Permet de génerer le top 10 des logs.
//------------------------------------------------------------------------


class Analyseur
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    void ChargementLogs (const string nomFichier,  Specifications * speci);
    // Mode d'emploi :
    //      Creation d'une unordered_multimap pour stocker les logs
    // Contrat :
    //      Aucun

    void AfficherTop10(requetes req);
    // Mode d'emploi :
    //      Affiche le top 10 des requête les plus demandées
    // Contrat :
    //      Aucun

    const ClasseurLogs GetLogs() const;
    // Mode d'emploi :
    //      Retourne les logs
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

//----------------------------------------------------- Methodes privées
    bool exclusion(string html);
    // Mode d'emploi :
    //      Renvoie faux si le document est sous les formats images,css ou javascript
    // Contrat :
    //      Aucun

//----------------------------------------------------- Attributs privé
    ClasseurLogs  logs;

};
//-------------------------------- Autres définitions dépendantes de <Lecteur>
#endif // LECTEUR_H
