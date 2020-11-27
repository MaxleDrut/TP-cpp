#include <iostream>
#include <cstring>
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
    while(actuelle->GetNext() != nullptr) {
        actuelle = actuelle->GetNext();
    }

    ListeTrajets nouvelle(t);
    actuelle->SetNext(&nouvelle);
}

/*Ajoute le trajet à la position pos par rapport à cette chaîne (pos = 1 signifie ajouter juste après le maillion sélectionné)*/
codeAdd ListeTrajets::AddPos(Trajet * t, int pos) {
    if(pos>GetLength()) {
        return OFB; //Out of Bound
    }
    ListeTrajets * actuelle = this;
    for(int i=1;i<=pos;i++) {
        actuelle = actuelle->GetNext();
    } //On récupère le maillon à la position cible

    if(actuelle->GetNext() == nullptr) { //La position cible est en bout de chaîne : on peut utiliser l'algo addlast
        actuelle->AddLast(t);
    } else {
        ListeTrajets nouvelle(t, actuelle->GetNext()); //Crée le nouveau maillon avec le maillon suivant de celui ciblé
        actuelle->next = &nouvelle;
    }
    return DONE;
}

/*Indique le nombre de maillons de chaîne suivants celui-ci*/
int ListeTrajets::GetLength() {
    int nbItems=1;
    ListeTrajets * actuelle= this;
    while(actuelle->GetNext()!=nullptr){
      actuelle = actuelle->GetNext();
      nbItems++;
    }
    return nbItems;
}

ListeTrajets * ListeTrajets::GetNext(){
    return next;
}

Trajet * ListeTrajets::GetContent(){
    return current;
}

void ListeTrajets::SetNext(ListeTrajets * l){
    next= l;
}

//Cette méthode combine les tostring de tous les éléments trajets des maillons à partir de celui d'appel
char * ListeTrajets::ToString() {
    char * texteGlobal = new char[50*(GetLength()+1)];
    texteGlobal[0] = '\0';
    ListeTrajets * actuelle = this;

    /*char * retourLigne = new char[2];
    retourLigne[0] = '\n';
    retourLigne[1] = '\0';*/

    char * texteActuel = current->ToString(); //Récup du texte de l'élément du maillon
    char * texteSuivant = next->ToString();

    strcat(texteActuel,"\n");
    strcat(texteActuel,texteSuivant);

    delete[] texteSuivant;

    /*while(actuelle->GetNext()!=nullptr){ //Parcours de tous les maillons
        char * texteActuel = actuelle->current->ToString(); //Récup du texte de l'élément du maillon
        strcat(texteGlobal, texteActuel);
        strcat(texteGlobal,retourLigne);

        actuelle=actuelle->GetNext();
        delete[] texteActuel;
    }*/


    //delete[] retourLigne;
    return texteActuel;
}

ListeTrajets::~ListeTrajets ()
{
#ifdef MAP
    cout << "Appel au destructeur de <ListeTrajets>" << endl;
#endif
    delete[] current;
    delete[] next;
}
