/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : 13/12/20
    copyright            : (C) 2020 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
enum codeAjout{FAIT,DOUBLON};
enum codeRecherche{TROUVE,PAS_TROUVE};

//------------------------------------------------------ Include personnel
#include "ListeTrajets.h"
#include "Trajet.h"
#include "Maillon.h"
#include "TrajetSimple.h" //Nécessaire pour tester le type dans Ajout
#include "TrajetCompo.h" //Idem que pour TrajetSimple.h

//------------------------------------------------------------------------
// Rôle de la classe <ListeTrajets>
//  Catalogue permet de stocker un ensemble de Trajet de manière ordonnée
//  à l'aide d'une ListeTrajets. Les trajets sont uniques et classés par ordre alphabétique
//  sur la ville de départ puis sur la ville d'arrivée.
//  Catalogue contient les algorithmes de recherche simple et recherche avancée
//  conformément au cahier des charges.
//------------------------------------------------------------------------

class Catalogue{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques

    codeAjout AjoutCatalogue(Trajet * trajet);
    // Mode d'emploi :
    //     Ajoute un Trajet au Catalogue en respectant l'ordre alphabétique de la liste.
    //     (trié sur la ville de départ puis sur la ville d'arrivée)
    //     Si le trajet existe déjà dans le Catalogue, renvoie le code DOUBLON. Sinon,
    //     renvoie le code FAIT.
    // Contrat :
    //      Aucun

    codeRecherche RechercheSimple(const char * depart, const char * arrivee) const;
    // Mode d'emploi :
    //     Parcours la liste et affiche tous les trajets ayant la meme chaîne de caractères que depart et arrivee.
    //     Renvoie TROUVE s'il y a eu au moins une occurence. Renvoie PAS_TROUVE sinon
    // Contrat :
    //      Aucun

    codeRecherche RechercheAvancee(const char * depart, const char * arrivee) const;
    // Mode d'emploi :
    //      Il s'agit d'une "extension" de la méthode RechercheSimple. On cherche désormais
    //      toutes les combinaisons de trajets permettant de rejoindre une ville depart à une ville arrivee.
    //      On fait appel pour cela à la méthode récursive "recherche"
    //      On affiche toutes les combinaisons trouvées. On renvoie TROUVE s'il y a eu au moins
    //      une occurence. On renvoie PAS_TROUVE sinon
    // Contrat :
    //      Aucun

    void AfficheCatalogue() const;
    // Mode d'emploi :
    //      Affiche tous les Trajets contenus dans la liste du Catalogue
    // Contrat :
    //      Aucun

//-------------------------------------------- Constructeurs - destructeur

    Catalogue();
    // Mode d'emploi :
    //      Construit une Catalogue vide
    // Contrat :
    //      Aucun

    virtual ~Catalogue();
    // Mode d'emploi :
    //      Détruit la liste du Catalogue
    // Contrat :
    //      Aucun

//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Méthodes privées

    int recherche(const char * da,const  char * av, int nbT, ListeTrajets * trajetRech, ListeTrajets * listeAfficher) const;
    // Mode d'emploi :
    //      Il s'agit d'une méthode récursive pour la recherche avancée qui prend en paramètre une ville de départ da
    //      et la ville d'arrivée av attendue par la recherche avancée.
    //      Elle contient la liste listeAfficher qui prend tous les trajets recensés lors des précédents appels à recherche.
    //      La méthode va regarder tous les trajets du Catalogue partant de la ville de départ da :
    //      S'il y a un trajet menant directement à l'arrivée av, elle affiche ce trajet ainsi que toutes les étapes précendentes
    //      Sinon, elle ajoute cette étape à la liste ListeAfficher et refait un appel à la méthode recherche avec la nouvelle ville d'arrivée.
    //      Elle renvoie un int qui compte tous les parcours possibles à partir de da en ajoutant les occurences trouvées précédemment par nbt.
    // Contrat :
    //      Aucun

    bool verif(const char * da,const  char * av, ListeTrajets * liste )const ;
    // Mode d'emploi :
    //      Verif est utilisée par la méthode recherche. Elle prend en paramètres
    //      une ville de départ (da) et une ville d'arrivée (av) ainsi que la liste des trajets
    //      déja recherchés. On parcourt cette liste pour voir si notre ville de départ et notre
    //      ville d'arrivée forment un trajet déja présent dans listeRech. Si c'est le cas
    //      la méthode retourne faux pour ne pas refaire une recherche sur ce trajet (et donc
    //      éviter une boucle infinie) sinon elle retourne vrai.
    // Contrat :
    //      Aucun


    int plusPetitString(const char * a,const char * b) const;
    // Mode d'emploi :
    //      Renvoie la taille du plus petit string entre a et b.
    //      Utilisé pour nos appels à la méthode strncmp.
    // Contrat :
    //      Aucun

//----------------------------------------------------- Attributs privées
    ListeTrajets * liste;

};
//-------------------------------- Autres définitions dépendantes de <Catalogue>
#endif //CATALOGUE_H
