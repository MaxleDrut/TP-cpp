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
        Maillon nouveau(t);
        first = &nouveau;
        last = &nouveau;
    } else {
        Maillon nouveau(t);
        last->SetNext(&nouveau);
        last = &nouveau;
    }
}

/*Ajoute le trajet à la position pos par rapport à cette chaîne (pos = 1 signifie ajouter juste après le maillion sélectionné)*/
codeAdd ListeTrajets::AddPos(Trajet * t, int pos) {
    if(pos>GetLength()) {
        return OFB; //Out of Bound
    }
    Maillon * actuelle = first;
    for(int i=1;i<=pos;i++) {
        actuelle = actuelle->GetNext();
    } //On récupère le maillon à la position cible

    if(actuelle->GetNext() == nullptr) { //La position cible est en bout de chaîne : on peut utiliser l'algo addlast
        AddLast(t);
    } else {
        Maillon nouveau(t, actuelle->GetNext()); //Crée le nouveau maillon avec le maillon suivant de celui ciblé
        actuelle->SetNext(&nouveau);
    }

    return DONE;
}

/*Indique le nombre de maillons de chaîne suivants celui-ci*/
int ListeTrajets::GetLength() {
    int nbItems=1;
    Maillon actuelle = *first;

    while(actuelle.GetNext()!=nullptr){
      cout<<actuelle.GetContenu()->ToString();
      actuelle = *actuelle.GetNext();
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

    /*ListeTrajets * actuelle = this;

    for(int i=0;i<tailleChaine;i++){ //Parcours de tous les maillons
        char * texteActuel = actuelle->current->ToString(); //Récup du texte de l'élément du maillon
        strcat(texteGlobal, texteActuel);
        actuelle = actuelle->GetNext();
        delete[] texteActuel;
    }*/

    return texteGlobal;
}

ListeTrajets::~ListeTrajets ()
{
#ifdef MAP
    cout << "Appel au destructeur de <ListeTrajets>" << endl;
#endif
}
