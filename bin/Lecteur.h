/*************************************************************************
                           Lecteur -  description
                             -------------------
    début                : 20/01/21
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Lecteur> (fichier Lecteur.h) ----------------
#if ! defined ( LECTEUR_H )
#define LECTEUR_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
enum codeLecteur{SUCCESS,ERROR};

//-------------------------------------------------------- Include système
#include <string>
#include <fstream>
using namespace std;

//------------------------------------------------------------------------
// Rôle de la classe <Lecteur>
//  Permet d'ouvrir un fichier log en lecture et de le lire
//  ligne par ligne.
//------------------------------------------------------------------------


class Lecteur
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    codeLecteur OuvertureLog(const string nomFichier);
    // Mode d'emploi :
    //      Ouverture du flux pour nomFichier
    // Contrat :
    //      Aucun

    string * NextLine();
    // Mode d'emploi :
    //      Retourne les informations concernant une ligne de log dans un tableau de string
    // Contrat :
    //      Aucun


//-------------------------------------------- Constructeurs - destructeur
    Lecteur ();
    // Mode d'emploi :
    //      Constructeur vide
    // Contrat :
    //      Aucun

    virtual ~Lecteur ();
    // Mode d'emploi :
    //      Destructeur vide
    // Contrat :
    //      Aucun

//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Attributs privé
    ifstream flux;

};
//-------------------------------- Autres définitions dépendantes de <Lecteur>
#endif // LECTEUR_H
