/*************************************************************************
                           TrajetCompo  -  description
                             -------------------
    début                : 13/12/20
    copyright            : (C) 2020 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <TrajetCompo> (fichier TrajetCompo.h) ----------------
#if ! defined ( TRAJETCOMPO_H )
#define TRAJETCOMPO_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------ Include personnel
#include "Trajet.h"
#include "ListeTrajets.h"
#include "Maillon.h"

//------------------------------------------------------------------------
// Rôle de la classe <TrajetCompo>
/*La classe TrajetCompo hérite de la classe Trajet.
La classe stocke une liste de trajets (ici uniquement des trajets simples)
qui représente les différentes étapes d'un trajet composé.
On retient en + la ville de départ de la première étape et la ville d'arrivée
de la dernière étape ! */
//------------------------------------------------------------------------

class TrajetCompo : public Trajet {

//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques

    void Afficher() const;
    // Mode d'emploi :
    //      Affiche les trajetSimples contenus dans chaque
    //      Maillon de la liste du trajetComposé.
    // Contrat :
    //      Aucun

    Trajet * Dupliquer();
    // Mode d'emploi :
    //      Cette méthode crée un nouveau trajet à partir du trajet source en dupliquant
    //      son contenu et retourne le pointeur du nouveau trajet.
    // Contrat :
    //      Aucun

    char* GetDepart() const;
    // Mode d'emploi :
    //      Retourne la ville de départ
    // Contrat :
    //      Aucun

    char* GetArrivee() const;
    // Mode d'emploi :
    //      Retourne la ville d'arrivée
    // Contrat :
    //      Aucun

    ListeTrajets * GetListe();
    // Mode d'emploi :
    //      Retourne le pointeur vers la liste de trajetSimples composant
    //le trajetComposé
    // Contrat :
    //      Aucun

//-------------------------------------------- Constructeurs - destructeur

    TrajetCompo(ListeTrajets * trajets);
    // Mode d'emploi :
    //      Construit un TrajetCompo à partir d'une ListeTrajets de TrajetSimple
    // Contrat :
    //      Aucun

    TrajetCompo();
    // Mode d'emploi :
    //      Construit un TrajetCompo en denant des valeurs nulles aux attributs
    // Contrat :
    //      Aucun


    virtual ~TrajetCompo();
    // Mode d'emploi :
    //      Detruit la ListeTrajets trajets ainsi que les attributs villeDepart et villeArrivee
    // Contrat :
    //      Aucun

//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Méthodes privées

//----------------------------------------------------- Attributs privées
    ListeTrajets * trajets;
};
//-------------------------------- Autres définitions dépendantes de <TrajetCompo>
#endif //TRAJETCOMPO_H
