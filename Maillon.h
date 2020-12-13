/*************************************************************************
                           Maillon  -  description
                             -------------------
    début                : 13/12/20
    copyright            : (C) 2020 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Maillon> (fichier Maillon.h) ----------------
#if ! defined ( MAILLON_H )
#define MAILLON_H
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------ Include personnel
#include "Trajet.h"

//------------------------------------------------------------------------
// Rôle de la classe <Maillon>
//  La classe Maillon est un composant de notre ListeTrajets : elle contient un Trajet
//  ainsi que le Maillon qui le succède.
//------------------------------------------------------------------------



class Maillon
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques

    Trajet * GetContenu();
    // Mode d'emploi :
    //      Retourne un pointeur vers le Trajet contenu dans le Maillon
    // Contrat :
    //      Aucun

    Maillon * GetNext();
    // Mode d'emploi :
    //      Retourne un pointeur vers le Maillon suivant du Maillon actuel
    // Contrat :
    //      Aucun

    void SetNext(Maillon * m);
    // Mode d'emploi :
    //     Met à jour le pointeur vers le Maillon suivant
    // Contrat :
    //      Aucun

//-------------------------------------------- Constructeurs - destructeur

    Maillon (Trajet * t, Maillon * suiv = nullptr);
    // Mode d'emploi :
    //      Construit un Maillon à partir d'un pointeur vers un Trajet
    //      et d'un pointeur vers un Maillon
    // Contrat :
    //      Aucun

    Maillon ();
    // Mode d'emploi :
    //      Construit un Maillon en denant des valeurs nulles aux attributs
    // Contrat :
    //      Aucun

    virtual ~Maillon();
    // Mode d'emploi :
    //      Detruit le contenu du Maillon et le Maillon suivant
    // Contrat :
    //      Aucun

//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Méthodes privées

//----------------------------------------------------- Attributs privées
    Trajet * contenu;
    Maillon * next;
};
//-------------------------------- Autres définitions dépendantes de <Maillon>
#endif //MAILLON_H
