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

TrajetSimple::TrajetSimple(const TrajetSimple & unTrajet) {
    villeDepart = unTrajet.GetDepart();
    villeArrivee = unTrajet.GetArrivee();
    transport = unTrajet.GetTransport();
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
void TrajetSimple::Afficher() const{
    cout<<"De "<<villeDepart<<" a "<<villeArrivee<<" en "<<transport;
}

char * TrajetSimple::GetDepart() const {
    return villeDepart;
}

char * TrajetSimple::GetArrivee() const{
    return villeArrivee;
}

char * TrajetSimple::GetTransport() const{
    return transport;
}
