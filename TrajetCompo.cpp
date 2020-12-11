/*La classe TrajetCompo hérite de la classe Trajet.
La classe stocke une liste de trajets (ici uniquement des trajets simples)
qui représente les différentes étapes d'un trajet composé.
On retient en + la ville de départ de la première étape et la ville d'arrivée
de la dernière étape ! */

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


/*Cette méthode affiche les trajets simples contenus dans chaque
maillon de la liste du trajet composé.*/
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


/*Cette méthode crée un nouveau trajet à partir du trajet source en dupliquant
son contenu et retourne le pointeur du nouveau trajet.*/
Trajet * TrajetCompo::Dupliquer() {
    //Duplication de la listeTrajet :
    ListeTrajets * nouvListe = new ListeTrajets();
    Maillon * actuel = trajets->GetPos(0);

    while(actuel!=nullptr) {
        nouvListe->AddLast(actuel->GetContenu()->Dupliquer());
        actuel = actuel->GetNext();
    }

    TrajetCompo * nouveau = new TrajetCompo(nouvListe);
    return nouveau;
}

/*Retourne la ville de départ*/
char* TrajetCompo::GetDepart() const{
    return villeDepart;
}

/*Retourne la ville de d'arrivée*/
char* TrajetCompo::GetArrivee() const{
    return villeArrivee;
}

/*Retourne le pointeur vers la liste de trajets simples composant
le trajet composé*/
ListeTrajets * TrajetCompo::GetListe(){
    return trajets;
}
