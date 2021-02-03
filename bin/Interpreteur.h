/*************************************************************************
                           Interpreteur -  description
                             -------------------
    début                : 20/01/21
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( INTERPRETEUR_H )
#define INTERPRETEUR_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
using namespace std;
//------------------------------------------------------ Include personnel
#include "Specifications.h"

//------------------------------------------------------------- Constantes

//Référencie les différents codes d'erreurs pour la lecture :

const string errLog = "Erreur 001 : Veuillez renseigner un fichier .log";
const string errSpeci= "Erreur 002 : l'option suivante n'a pas ete reconnue : ";
const string errGraph= "Erreur 003 : Le fichier graphique doit être au format .dot";
const string errTemps= "Erreur 004 : -t doit renseigner un nombre entre 0 et 23";
const string errPoids= "Erreur 005 : -p doit renseigner un nombre >0";
//------------------------------------------------------------------ Types
enum codeInter{OK,ERR};

//------------------------------------------------------------------------
// Rôle de la classe <Interpreteur>
// Classe permettant d'interpréter les différents paramètres d'une commande
// donnée à l'exécution et de dresser la structure Specifications

//------------------------------------------------------------------------

class Interpreteur
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    codeInter LireCommande(int argc, char** argv);
    // Mode d'emploi :
    //      A partir de la commande, renvoie la liste des spécifications
    // Contrat :
    //      Aucun

    Specifications * GetObjSpeci() const;
//-------------------------------------------- Constructeurs - destructeur

    Interpreteur();
    // Mode d'emploi :
    //      Constructeur par défaut
    // Contrat :
    //      Aucun
    virtual ~Interpreteur();
    // Mode d'emploi :
    //      Detruit les attributs du Trajet
    // Contrat :
    //      Aucun


//------------------------------------------------------------------ PRIVE
private :
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    Specifications * spe;

};
//-------------------------------- Autres définitions dépendantes de <Interpreteur>
#endif // INTERPRETEUR_H
