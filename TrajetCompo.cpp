#include <cstring>
#include <iostream>
using namespace std;

#include "TrajetCompo.h"

TrajetCompo::TrajetCompo(ListeTrajets * trajets){
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
}

TrajetCompo::TrajetCompo () {
    trajets = nullptr;
    #ifdef MAP
        cout << "Appel au constructeur vide de <TrajetCompo>" << endl;
    #endif
    villeDepart = new char[1];
    villeArrivee = new char[1];
    villeDepart[0] = villeArrivee[0] = '\0';
}

TrajetCompo::~TrajetCompo(){
    #ifdef MAP
        cout << "Appel au destructeur de <TrajetCompo>" << endl;
    #endif
    delete trajets;
    delete[] villeDepart;
    delete[] villeArrivee;
}

void TrajetCompo::Afficher() const{
    Maillon * actuel =trajets->GetPos(0);
    while(actuel->GetNext()!=nullptr) {
        actuel->GetContenu()->Afficher();
        cout<<" - ";
        actuel = actuel->GetNext();
    }
    //Le dernier affichage ne doit pas être suivi de ' - '
    actuel->GetContenu()->Afficher();

}

char* TrajetCompo::GetDepart() const{
    return villeDepart;
}
char* TrajetCompo::GetArrivee() const{
    return villeArrivee;
}
ListeTrajets * TrajetCompo::GetListe(){
    return trajets;
}
