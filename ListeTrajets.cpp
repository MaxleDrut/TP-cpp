/*************************************************************************
                           ListeTrajets  -  description
                             -------------------
    début                : 13/12/20
    copyright            : (C) 2020 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <ListeTrajets> (fichier ListeTrajets.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <cstring>
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "ListeTrajets.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques


void ListeTrajets::AddLast(Trajet * t)
//Algorithme:
        //  Si la liste n'est pas vide on met à jour le dernier Maillon de la liste et son suivant
{
    if(last == nullptr) { //Cas où la liste est vide
        Maillon * nouveau = new Maillon(t);
        first = nouveau;
        last = nouveau;
    } else {
        Maillon * nouveau = new Maillon(t);
        last->SetNext(nouveau);
        last = nouveau; //Màj du last
    }
}//----- Fin de AddLast


void ListeTrajets::AddFirst(Trajet * t)
//Algorithme:
//      Si la liste n'est pas vide on met à jour le premier Maillon de la liste et son suivant
{
    if(first==nullptr) { //Liste vide
        Maillon * nouveau = new Maillon(t);
        first = nouveau;
        last = nouveau;
    } else {
        Maillon * nouveau = new Maillon(t,first);
        first = nouveau; //Màj du first
    }
}//----- Fin de AddFirst


codeAdd ListeTrajets::AddPos(Trajet * t, int pos)
//Algorithme:
//      Si la position passée en paramètre est supérieur à la taille de la liste on renvoie le code OFB
//      Si elle est égale à 0, on ajoute le Trajet passé en paramètre avec AddFirst
//      Sinon on parcourt la listeTrajets jusqu'à la position pos, si on arrive à la fin
//      de la liste on appelle AddLast sinon on ajoute le nouveau Trajet entre le Maillon à la
//      position pos et son suivant.
{
    if(pos>GetLength()) {
        return OFB; //Out of Bound
    }
    if(pos==0) {
        AddFirst(t);
    } else {
        Maillon * actuelle = first;
        for(int i=1;i<pos;i++) { //On récupère le maillon à la position cible
            actuelle = actuelle->GetNext();
        }
        if(actuelle->GetNext() == nullptr) { //La position cible est en bout de chaîne : on peut utiliser l'algo addlast
            AddLast(t);
        } else {
            Maillon * nouveau = new Maillon(t, actuelle->GetNext()); //Crée le nouveau maillon avec le maillon suivant de celui ciblé
            actuelle->SetNext(nouveau);
        }
    }

    return DONE;
}//----- Fin de AddPos


Maillon * ListeTrajets::Supprimer()
//Algorithme:
//      Si la liste est vide on renvoie le dernier, si la listeTrajets
//      ne contient qu'un élément on le met à null pour rendre la listeTrajets vide.
//      Sinon on parcours la liste pour supprimer le dernier Maillon de sorte à ce
//      que l'avant dernier Maillon devienne le last.
{
    Maillon * toReturn;
    if(first!=nullptr) {
        toReturn = last;
        if(first==last) { //Liste à un élément. La liste deviendra donc vide après le retrait.
            first = last = nullptr;
        } else { //Liste à plusieurs éléments.
            Maillon * actuel = first;
            while(actuel->GetNext()->GetNext()!=nullptr){ //On fait le parcours jusqu'à l'AVANT DERNIER Maillon.
                actuel = actuel->GetNext();
            } //L'avant dernier maillon devient le dernier de la liste.
            actuel->SetNext(nullptr);
            last = actuel;
        }
    } else { //Liste vide.
        toReturn = nullptr;
    }
    return toReturn;
}//------ Fin de supprimer



int ListeTrajets::GetLength()
//Algorithme:
//      Parcourt la ListeTrajets pour conter son nombre d'éléments
{
    int nbItems=1;
    Maillon * actuel = first;

    while(actuel->GetNext()!=nullptr){
        actuel = actuel->GetNext();
        nbItems++;
    }

    return nbItems;
}//----- Fin de GetLength


Maillon * ListeTrajets::GetLast()
//Algorithme: Aucun
{
    return last;
}//----- Fin de GetLast


Maillon * ListeTrajets::GetPos(int pos)
//Algorithme:
//      Parcourt la liste jusqu'à la position passée en paramètre,
//      si la liste est vide ou si la position demandée n'est pas
//      dans la liste la méthode retourne nullptr
{

    if(first==nullptr || pos>GetLength()) { //Position en dehors de la taille de la Liste/liste vide
        return nullptr;
    }
    Maillon * actuelle = first; //Sinon algo de parcours classique !
    for(int i=0;i<pos;i++) {
        actuelle = actuelle->GetNext();
    }
    return actuelle;
}//----- Fin de GetPos


void ListeTrajets::Afficher() const
//Algorithme:
//      Parcourt la liste affiche le contenu de chaque Maillon
{
    Maillon * actuel = first;
    while(actuel!=nullptr) {
        actuel->GetContenu()->Afficher();
        cout<<endl;
        actuel = actuel->GetNext();
    }
}//----- Fin de Afficher



//-------------------------------------------- Constructeurs - destructeur

ListeTrajets::ListeTrajets()
//Algorithme: Aucun
{
    #ifdef MAP
            cout << "Appel au constructeur de <ListeTrajets>" << endl;
    #endif
    first = nullptr;
    last = nullptr;
}//----- Fin de ListeTrajets



ListeTrajets::~ListeTrajets ()
//Algorithme:
//      Si la liste n'est pas vide on détruit le premier Maillon de la listeTrajets
//      En détruisant first, on détruit tous les maillons.
//      En effet, le destructeur de maillon est conçu pour aussi détruire le maillon pointé suivant.
{
#ifdef MAP
    cout << "Appel au destructeur de <ListeTrajets>" << endl;
#endif
    if(first!=nullptr) {
        delete first;
    }
}//----- Fin de ~ListeTrajets 
