/*************************************************************************
                           TrajetSimple  -  description
                             -------------------
    début                : 13/12/20
    copyright            : (C) 2020 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h) ----------------
#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------ Include personnel
#include "Trajet.h"

//------------------------------------------------------------------------
// Rôle de la classe <ListeTrajets>
//  La classe TrajetSimple hérite de la classe Trajet.
//  En plus d'une ville d'arrivée et d'une ville de départ,
//  on ajoute au trajet un moyen de transport entre les deux villes.
//------------------------------------------------------------------------


class TrajetSimple : public Trajet {

//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques

    void Afficher() const;
    // Mode d'emploi :
    //      Affiche le TrajetSimple
    // Contrat :
    //      Aucun

    Trajet * Dupliquer() const;
    // Mode d'emploi :
    //      Crée un nouveau trajet à partir du trajet source en dupliquant
    //      son contenu et retourne le pointeur du nouveau trajet.
    // Contrat :
    //      Aucun

    const char* GetDepart() const;
    // Mode d'emploi :
    //      Retourne la ville de départ.
    // Contrat :
    //      Aucun

    const char* GetArrivee() const;
    // Mode d'emploi :
    //      Retourne la ville d'arrivée.
    // Contrat :
    //      Aucun

    const char* GetTransport() const;
    // Mode d'emploi :
    //      Retourne le moyen de transport.
    // Contrat :
    //      Aucun

//-------------------------------------------- Constructeurs - destructeur

    TrajetSimple(const char * depart, const char * arrivee, const char * transport);
    // Mode d'emploi :
    //      Construit une TrajetSimple à partir de char * représentant la ville de départ, d'arrivée
    //      et le transport
    // Contrat :
    //      Aucun

    TrajetSimple();
    // Mode d'emploi :
    //      Construit un TrajetSimple en denant des valeurs nulles aux attributs
    // Contrat :
    //      Aucun

    virtual ~TrajetSimple();
    // Mode d'emploi :
    //      Detruit les attributs villeDepart, villeArrivee et transport.
    // Contrat :
    //      Aucun

//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Méthodes privées

//----------------------------------------------------- Attributs privées
    char* transport;
};
//-------------------------------- Autres définitions dépendantes de <TrajetSimple>
#endif //TRAJETSIMPLE_H
