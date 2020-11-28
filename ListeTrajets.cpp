#include <iostream>
#include <cstring>
using namespace std;

#include "ListeTrajets.h"

//La liste est initialisée vide au début
ListeTrajets::ListeTrajets() {
    #ifdef MAP
            cout << "Appel au constructeur de <ListeTrajets>" << endl;
    #endif
    first = nullptr;
    last = nullptr;
}

void ListeTrajets::AddLast(Trajet * t) {
    if(last == nullptr) { //Cas où la liste est vide
        Maillon * nouveau = new Maillon(t);
        first = nouveau;
        last = nouveau;
    } else {
        Maillon * nouveau = new Maillon(t);
        last->SetNext(nouveau);
        last = nouveau;
    }
}

void ListeTrajets::AddFirst(Trajet * t) {
    if(first==nullptr) { //Liste vide
        Maillon * nouveau = new Maillon(t);
        first = nouveau;
        last = nouveau;
    } else {
        Maillon * nouveau = new Maillon(t,first);
        first = nouveau;
    }
}

/*Ajoute le trajet à la position cible*/
codeAdd ListeTrajets::AddPos(Trajet * t, int pos) {
    if(pos>GetLength()) {
        return OFB; //Out of Bound
    }
    if(pos==0) {
        AddFirst(t);
    } else {
        Maillon * actuelle = first;
        for(int i=1;i<pos;i++) { //On récupère le maillon à la position cible
            actuelle = actuelle->GetNext();
        }
        if(actuelle->GetNext() == nullptr) { //La position cible est en bout de chaîne : on peut utiliser l'algo addlast
            AddLast(t);
        } else {
            Maillon * nouveau = new Maillon(t, actuelle->GetNext()); //Crée le nouveau maillon avec le maillon suivant de celui ciblé
            actuelle->SetNext(nouveau);
        }
    }

    return DONE;
}

/*Indique le nombre de maillons de chaîne suivants celui-ci*/
int ListeTrajets::GetLength() {
    int nbItems=1;
    Maillon * actuel = first;

    while(actuel->GetNext()!=nullptr){
        actuel = actuel->GetNext();
        nbItems++;
    }

    return nbItems;
}

Maillon * ListeTrajets::GetLast() {
    return last;
}

Maillon * ListeTrajets::GetPos(int pos) {
    if(pos>GetLength()) {
        return nullptr;
    }
    Maillon * actuelle = first;
    for(int i=0;i<pos;i++) {
        actuelle = actuelle->GetNext();
    }
    return actuelle;
}


//Cette méthode combine les tostring de tous les éléments trajets des maillons à partir de celui d'appel
char * ListeTrajets::ToString() {
    int tailleChaine = GetLength();
    char * texteGlobal = new char[300*tailleChaine+1];
    texteGlobal[0] = '\0';

    Maillon * actuel = first;
    char * texteLocal;
    while(actuel!=nullptr) {
        texteLocal = actuel->GetContenu()->ToString();
        strcat(texteGlobal,texteLocal);
        actuel = actuel->GetNext();
        delete texteLocal;
    }
    return texteGlobal;
}

ListeTrajets::~ListeTrajets ()
{
#ifdef MAP
    cout << "Appel au destructeur de <ListeTrajets>" << endl;
#endif
    delete first; //En détruisant first, on détruit tous les maillons grâce au destructeur des Maillons.
}
