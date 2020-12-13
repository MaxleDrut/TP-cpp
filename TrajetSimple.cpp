/*************************************************************************
                           TrajetSimple  -  description
                             -------------------
    début                : 13/12/20
    copyright            : (C) 2020 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <cstring>
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "TrajetSimple.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques


void TrajetSimple::Afficher() const
//Algorithme : Aucun
{
    cout<<"De "<<villeDepart<<" a "<<villeArrivee<<" en "<<transport;
}//----- Fin de Afficher


Trajet * TrajetSimple::Dupliquer()
//Algorithme : Aucun
{
    TrajetSimple * nouveau = new TrajetSimple(villeDepart,villeArrivee,transport);
    return nouveau;
}//----- Fin de Duppliquer



char * TrajetSimple::GetDepart() const
//Algorithme: Aucun
{
    return villeDepart;
}//----- Fin de GetDepart


char * TrajetSimple::GetArrivee() const
//Algorithme: Aucun
{
    return villeArrivee;
}//----- Fin de GetArrivee


char * TrajetSimple::GetTransport() const
//Algorithme: Aucun
{
    return transport;
}//----- Fin de GetTransport


//-------------------------------------------- Constructeurs - destructeur

TrajetSimple::TrajetSimple ()
//Algorithme: Aucun
{
#ifdef MAP
    cout << "Appel au constructeur vide de <TrajetSimple>" << endl;
#endif
    villeDepart = new char[1];
    villeArrivee = new char[1];
    transport = new char[1];
    villeDepart[0] = villeArrivee[0] = transport[0] = '\0';
}//----- Fin de TrajetSimple

TrajetSimple::TrajetSimple(const char* depart,const char* arrivee,const char* trans)
//Algorithme:
//      On copie dans nos attribut villeDepart, villeArrivee et transport les const char *
//      passés en paramètre
{
#ifdef MAP
    cout << "Appel au constructeur complet de <TrajetSimple>" << endl;
#endif
    villeDepart = new char[strlen(depart)+1];
    villeDepart[0] = '\0';
    villeArrivee = new char[strlen(arrivee)+1];
    villeArrivee[0] = '\0';
    transport = new char[strlen(trans)+1];
    transport[0] = '\0';
    strcpy(villeDepart,depart);
    strcpy(villeArrivee,arrivee);
    strcpy(transport,trans);
}//----- Fin de TrajetSimple

TrajetSimple::~TrajetSimple ()
//Algorithme: Aucun
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
    delete[] villeDepart;
    delete[] villeArrivee;
    delete[] transport;
}//----- Fin de ~TrajetSimple
