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
    villeArrivee = new char[strlen(depart)+1];
    transport = new char[strlen(depart)+1];
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

char * TrajetSimple::ToString() {
    char * texte = new char[300];
    texte[0]='\0'; //Il faut indiquer que le string à une longueur zéro initiale
    strcat(texte,"De ");
    strcat(texte,villeDepart);
    strcat(texte," a ");
    strcat(texte,villeArrivee);
    strcat(texte," en ");
    strcat(texte,transport);
    strcat(texte,"\n");
    return texte;
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
