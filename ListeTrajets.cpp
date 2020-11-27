#include <iostream>
using namespace std;

#include "ListeTrajets.h"

ListeTrajets::ListeTrajets(Trajet * t, ListeTrajets * next) {
    #ifdef MAP
        cout << "Appel au constructeur de <ListeTrajets>" << endl;
    #endif
    current = t;
    this->next = next;
}

ListeTrajets::ListeTrajets() {
    #ifdef MAP
        cout << "Appel au constructeur vide de <ListeTrajets>" << endl;
    #endif
    current = nullptr;
    next = nullptr;
}

void ListeTrajets::AddLast(Trajet * t) {
    ListeTrajets * actuelle = this;
    while(this.GetNext() != nullptr) {
        actuelle = actuelle.GetNext();
    }

    ListeTrajets * nouvelle(t);
    actuelle.SetNext(nouvelle);
}

/*Ajoute le trajet à la position pos */
codeAdd ListeTrajets::AddPos(Trajet * t, int pos) {


}

/*Indique le nombre de maillons de chaîne suivants celui-ci*/
int ListeTrajets::GetLength() const{
    int nbItems=1;
    ListeTrajets * actuel= this;
    while(this.GetNext()!=nullptr){
      actuel = actuel.getNext();
      nbItems++;
    }
    return nbItems;
}

ListeTrajets * GetNext(){
    return next;
}

Trajet * GetContent(){
    return current;
};

void SetNext(ListeTrajets *){

};

char * ToString() const;
