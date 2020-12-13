/*************************************************************************
                           TrajetCompo  -  description
                             -------------------
    début                : 13/12/20
    copyright            : (C) 2020 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <TrajetCompo> (fichier TrajetCompo.cpp) ----------------
//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <cstring>
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "TrajetCompo.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void TrajetCompo::Afficher() const
//Algorithme:
//      Parcourt la listeTrajet trajets et affiche le contenu de chaque Maillon
{
    Maillon * actuel =trajets->GetPos(0);
    while(actuel->GetNext()!=nullptr) {
        actuel->GetContenu()->Afficher();
        cout<<" - ";
        actuel = actuel->GetNext();
    }

    //Le dernier affichage ne doit pas être suivi de ' - '
    actuel->GetContenu()->Afficher();

}//----- Fin de Afficher



Trajet * TrajetCompo::Dupliquer()
//Algorithme :
//      Crée une nouvelle listeTrajet en y ajoutant le contenu duppliqué
//      de chaque Maillon de l'attribut trajets.
//      Retourne pointeur vers un nouveau TrajetCompo ayant pour attribut la nouvelle liste.
{

    ListeTrajets * nouvListe = new ListeTrajets();
    Maillon * actuel = trajets->GetPos(0);

    while(actuel!=nullptr) {
        nouvListe->AddLast(actuel->GetContenu()->Dupliquer());
        actuel = actuel->GetNext();
    }

    TrajetCompo * nouveau = new TrajetCompo(nouvListe);
    return nouveau;

}//----- Fin de Duppliquer


char* TrajetCompo::GetDepart() const
//Algorithme: Aucun
{
    return villeDepart;
}//----- Fin de GetDepart


char* TrajetCompo::GetArrivee() const
//Algorithme : Aucun
{
    return villeArrivee;
}//----- Fin de GetArrivee


ListeTrajets * TrajetCompo::GetListe()
//Algorithme: Aucun
{
    return trajets;
}//----- Fin de GetListe


//-------------------------------------------- Constructeurs - destructeur

TrajetCompo::TrajetCompo(ListeTrajets * trajets)
//Algorithme:
//      Copie le départ du premier Maillon de la liste passée en paramètre
//      dans villeDepart et l'arrivée du dernier Maillon de la liste passée en paramètre
//      dans villeArrivee. Construit finalement la listeTrajet trajets à partir du
//      paramètre trajets.
{
    #ifdef MAP
        cout << "Appel au constructeur complet de <TrajetCompo>" << endl;
    #endif
    char * temp = trajets->GetPos(0)->GetContenu()->GetDepart();
    villeDepart = new char[strlen(temp)+1];
    villeDepart[0] = '\0';
    strcpy(villeDepart,temp);

    temp = trajets->GetLast()->GetContenu()->GetArrivee();
    villeArrivee = new char[strlen(temp)+1];
    villeArrivee[0] = '\0';
    strcpy(villeArrivee,temp);

    this->trajets = trajets;
}//----- Fin de TrajetCompo

TrajetCompo::TrajetCompo ()
//Algorithme: Aucun
{
    #ifdef MAP
        cout << "Appel au constructeur vide de <TrajetCompo>" << endl;
    #endif
    trajets = nullptr;
    villeDepart = new char[1];
    villeArrivee = new char[1];
    villeDepart[0] = villeArrivee[0] = '\0';
}//----- Fin de TrajetCompo


TrajetCompo::~TrajetCompo()
//Algorithme: Aucun
{
    #ifdef MAP
        cout << "Appel au destructeur de <TrajetCompo>" << endl;
    #endif
    delete trajets;
    delete[] villeDepart;
    delete[] villeArrivee;
}//----- Fin de ~TrajetCompo
