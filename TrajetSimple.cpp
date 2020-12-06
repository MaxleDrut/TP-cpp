/*La classe TrajetSimple hérite de la classe Trajet.
En plus d'une ville d'arrivée et d'une ville de départ,
on ajoute au trajet un moyen de transport entre les deux villes.*/


#include <cstring>
#include <iostream>
using namespace std;

#include "TrajetSimple.h"

TrajetSimple::TrajetSimple ()
{
#ifdef MAP
    cout << "Appel au constructeur vide de <TrajetSimple>" << endl;
#endif
    villeDepart = new char[1];
    villeArrivee = new char[1];
    transport = new char[1];
    villeDepart[0] = villeArrivee[0] = transport[0] = '\0';
}

TrajetSimple::TrajetSimple(const char* depart,const char* arrivee,const char* trans)
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
}

TrajetSimple::~TrajetSimple ()
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
    delete[] villeDepart;
    delete[] villeArrivee;
    delete[] transport;
}

/*Affiche le trajet simple*/
void TrajetSimple::Afficher() const{
    cout<<"De "<<villeDepart<<" a "<<villeArrivee<<" en "<<transport;
}

/*Cette méthode retourne un pointeur vers un trajet ayant
le même contenu que le trajet à duppliquer.*/
Trajet * TrajetSimple::Dupliquer() {
    TrajetSimple * nouveau = new TrajetSimple(villeDepart,villeArrivee,transport);
    return nouveau;
}

/*Retourne la ville de départ*/
char * TrajetSimple::GetDepart() const {
    return villeDepart;
}

/*Retourne la ville de d'arrivée*/
char * TrajetSimple::GetArrivee() const{
    return villeArrivee;
}

/*Retourne le moyen de transport*/
char * TrajetSimple::GetTransport() const{
    return transport;
}
