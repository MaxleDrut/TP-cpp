/*************************************************************************
                           ListeTrajets  -  description
                             -------------------
    début                : 13/12/20
    copyright            : (C) 2020 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <ListeTrajets> (fichier ListeTrajets.h) ----------------
#if ! defined ( LISTETRAJETS_H )
#define LISTETRAJETS_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
enum codeAdd {DONE,OFB};

//------------------------------------------------------ Include personnel
#include "Trajet.h"
#include "Maillon.h"

//------------------------------------------------------------------------
// Rôle de la classe <ListeTrajets>
//  La classe ListeTrajets est une liste chainée de trajets.
//  Elle se compose de maillons qui contiennent un trajet chacun.
//  On la définie avec un maillon de début et un maillon de fin.
//  La liste peut être utilisée par le catalogue pour stocker des
//  trajets simples ou composés, ou par les TrajetCompo pour stocker des Trajet.
//  On peut rajouter un trajet à n'importe quelle position dans la liste entre
//  le premier maillon et le dernier.
//  On peut également supprimer le maillon se trouvant en fin de liste.
//------------------------------------------------------------------------


class ListeTrajets
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    void AddLast(Trajet * t);
    // Mode d'emploi :
    //     Ajoute un trajet t en fin de liste en créant un nouveau Maillon associé
    // Contrat :
    //      Aucun

    void AddFirst(Trajet * t);
    // Mode d'emploi :
    //     Ajoute un trajet t en début de liste en créant un nouveau Maillon associé
    // Contrat :
    //      Aucun

    codeAdd AddPos(Trajet * t, int pos);
    // Mode d'emploi :
    //      Ajoute un trajet t à une position pos ciblée en créant un nouveau Maillon associé.
    //      Elle l'ajoute entre le maillon de la liste situé à la position pos et son suivant.
    // Contrat :
    //      Aucun

    Maillon * Supprimer();
    // Mode d'emploi :
    //      Retire le dernier maillon de la liste et renvoie son pointeur.
    //      Il faut penser à le delete par la suite.
    // Contrat :
    //      Aucun

    int GetLength();
    // Mode d'emploi :
    //      Renvoie le nombre entier d'éléments de la liste.
    // Contrat :
    //      Aucun

    Maillon * GetLast();
    // Mode d'emploi :
    //      Retourne le pointeur sur le dernier Maillon de la liste.
    // Contrat :
    //      Aucun

    Maillon * GetPos(int pos);
    // Mode d'emploi :
    //      Retourne le pointeur sur le Maillon à la position de l'entier pos.
    // Contrat :
    //      Aucun

    void Afficher() const;
    // Mode d'emploi :
    //      Affiche le contenu de chaque Maillon de la liste.
    // Contrat :
    //      Aucun

//-------------------------------------------- Constructeurs - destructeur

    ListeTrajets ();
    // Mode d'emploi :
    //      Construit une ListeTrajets vide
    // Contrat :
    //      Aucun

    virtual ~ListeTrajets();
    // Mode d'emploi :
    //      Detruit le premier Maillon de la liste
    // Contrat :
    //      Aucun

//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Méthodes privées

//----------------------------------------------------- Attributs privées
    Maillon * first;
    Maillon * last;
};
//-------------------------------- Autres définitions dépendantes de <ListeTrajets>
#endif //LISTETRAJETS_H
