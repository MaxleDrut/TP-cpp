/*************************************************************************
                           Specifications -  description
                             -------------------
    début                : 20/01/21
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Specifications> (fichier Specifications.h) ----------------
#if ! defined ( SPECIFICATIONS_H )
#define SPECIFICATIONS_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <iostream>
using namespace std;

//------------------------------------------------------------- Constantes
const unsigned int nbSpeci = 8;
//Nombre de spécifications à stocker pour notre application.
const string listeSpeci[] = {"-g","-e","-t","-ip","-err","-p","-os","log"};
//Liste des attributs actuellement attendus

//------------------------------------------------------------------ Types
enum codeAjout{AJOUTE, PAS_TROUVE};
//------------------------------------------------------ Include personnel

//------------------------------------------------------------------------
// Rôle de la classe <Specifications>
// Permet d'associer les différentes spécifications des commandes à leurs
// attributs. La classe contient notamment les différentes spécifications attendues par
// l'Interpreteur et se veut être flexible.

//------------------------------------------------------------------------

class Specifications
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Friendship
    friend class Interpreteur;
    //La méthode LireCommande de l'Interpreteur pourra faire appel à ajoutSpeci et estSpeci

//----------------------------------------------------- Méthodes publiques
const string GetSpeci(string nomSpeci) const;
// Mode d'emploi :
//      Permet d'obtenir une spécification demandée.
// Contrat :
//      Aucun

//-------------------------------------------- Constructeurs - destructeur

    Specifications();
    // Mode d'emploi :
    //      Constructeur par défaut qui crée le tableau de spéci.
    // Contrat :
    //      Aucun
    virtual ~Specifications();
    // Mode d'emploi :
    //      Detruit les attributs du Trajet
    // Contrat :
    //      Aucun


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
codeAjout ajoutSpeci(string nomSpeci,string attribut);
// Mode d'emploi :
//      Permet d'ajouter une spécifications. Réservé aux amis de Speci.
// Contrat :
//      Aucun

bool estSpeci(string nomSpeci) const;
// Mode d'emploi :
//      Renvoie true si le string est bien une spécification du tableau
// Contrat :
//      Aucun
//----------------------------------------------------- Attributs protégés
string** tabSpeci;

};
//-------------------------------- Autres définitions dépendantes de <Specifications>
#endif // SPECIFICATIONS_H
