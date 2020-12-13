/*************************************************************************
                           Trajet -  description
                             -------------------
    début                : 13/12/20
    copyright            : (C) 2020 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( TRAJET_H )
#define TRAJET_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------ Include personnel

//------------------------------------------------------------------------
// Rôle de la classe <Trajet>
//  Classe abstraite ayant comme enfant TrajetSimple et TrajetCompo
//  Les attributs "génériques" des deux enfants sont les villes de départ et d'arrivée
//------------------------------------------------------------------------


class Trajet
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    virtual void Afficher() const = 0;
    // Mode d'emploi :
    //      Affiche le TrajetSimple
    // Contrat :
    //      Aucun

    virtual char* GetDepart() const = 0;
    // Mode d'emploi :
    //      Retourne la ville de départ
    // Contrat :
    //      Aucun

    virtual char* GetArrivee() const = 0;
    // Mode d'emploi :
    //      Retourne la ville d'arrivée
    // Contrat :
    //      Aucun

    virtual Trajet * Dupliquer() = 0;
    // Mode d'emploi :
    //      Cette méthode crée un nouveau trajet à partir du trajet source en dupliquant
    //      son contenu et retourne le pointeur du nouveau trajet.
    // Contrat :
    //      Aucun


//-------------------------------------------- Constructeurs - destructeur
    virtual ~Trajet(){};
    // Mode d'emploi :
    //      Detruit les attributs du Trajet
    // Contrat :
    //      Aucun


//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    char * villeDepart;
    char * villeArrivee;
};
//-------------------------------- Autres définitions dépendantes de <Trajet>
#endif // TRAJET_H
