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

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------ Include personnel
#include "Specifications.h"
//------------------------------------------------------------------------
// Rôle de la classe <Trajet>
// Classe permettant d'interpréter les différents paramètres d'une commande
// donnée à l'exécution

//------------------------------------------------------------------------

class Interpreteur
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    Specifications * LireCommande(int argc, char** argv);
    // Mode d'emploi :
    //      A partir de la commande, renvoie la liste des spécifications
    // Contrat :
    //      Aucun

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

//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};
//-------------------------------- Autres définitions dépendantes de <Interpreteur>
#endif // INTERPRETEUR_H
