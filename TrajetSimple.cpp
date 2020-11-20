#include <cstring>
#include <iostream>
using namespace std;

#include "TrajetSimple.h"

TrajetSimple :: TrajetSimple ( )
{
#ifdef MAP
    cout << "Appel au constructeur vide de <TrajetSimple>" << endl;
#endif
    /*villeDepart = "";
    villeArrivee = "";
    transport = "";*/
}

TrajetSimple::TrajetSimple(const char* depart, const char* arrivee, const char* trans)
{
#ifdef MAP
    cout << "Appel au constructeur complet de <TrajetSimple>" << endl;
#endif
    /*villeDepart = depart;
    villeArrivee = arrivee;
    transport = trans;*/
}

TrajetSimple::~TrajetSimple ()
{
#ifdef MAP
    cout << "Appel au destructeur de <Ensemble>" << endl;
#endif
    /*delete[] villeDepart;
    delete[] villeArrivee;
    delete[] transport;*/
}

char * TrajetSimple :: toString() const{
    /*char * texte[100];
    strcat(texte,"De ");
    strcat(texte,villeDepart);
    strcat(texte," à ");
    strcat(texte,villeArrivee);
    strcat(texte," en ");
    strcat(texte,transport);*/
    return NULL;
}

char * TrajetSimple::getDepart() const {
    return villeDepart;
}

char * TrajetSimple::getArrivee() const{
    return villeArrivee;
}

char * TrajetSimple::getTransport() const{
    return transport;
}
