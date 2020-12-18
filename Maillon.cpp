/*************************************************************************
                           Maillon  -  description
                             -------------------
    début                : 13/12/20
    copyright            : (C) 2020 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Maillon> (fichier Maillon.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <cstring>
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Maillon.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques


const Trajet * Maillon::GetContenu() const
//Algorithme: Aucun
{
    return contenu;
}//----- Fin de GetContenu


Maillon * Maillon::GetNext() const
//Algorithme: Aucun
{
    return next;
}//----- Fin de GetNext


void Maillon::SetNext(Maillon * m)
//Algorithme: Aucun
{
    next=m;
}//----- Fin de SetNext


//-------------------------------------------- Constructeurs - destructeur

Maillon::Maillon (const Trajet * t, Maillon * suiv)
//Algorithme: Aucun
{
    #ifdef MAP
        cout << "Appel au constructeur de <Maillon>" << endl;
    #endif
    contenu = t;
    next = suiv;
}//----- Fin de Maillon

Maillon::Maillon ()
//Algorithme: Aucun
{
    #ifdef MAP
        cout << "Appel au constructeur vide de <Maillon>" << endl;
    #endif
    contenu = nullptr;
    next = nullptr;
}//----- Fin de Maillon

Maillon::~Maillon()
//Algorithme: Aucun
{
    #ifdef MAP
        cout << "Appel au destructeur de <Maillon>" << endl;
    #endif
    delete contenu;
    if(next!=nullptr) { //Destruction du maillon suivant
        delete next;
    }
}//----- Fin de ~Maillon
