/*La classe ListeTrajets est une liste chainée de trajets.
Elle se compose de maillons qui contiennent un trajet chacun.
On la définie avec un maillon de début et un maillon de fin.
La liste peut être utilisée par le catalogue pour stocker des
trajets simples ou composés, ou par les TrajetCompo pour stocker des Trajet.
On peut rajouter un trajet à n'importe quelle position dans la liste entre
le premier maillon et le dernier.
On peut également supprimer le maillon se trouvant en fin de liste.*/

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

/*Ajoute un trajet t en fin de liste en créant un nouveau Maillon associé*/
void ListeTrajets::AddLast(Trajet * t) {
    if(last == nullptr) { //Cas où la liste est vide
        Maillon * nouveau = new Maillon(t);
        first = nouveau;
        last = nouveau;
    } else {
        Maillon * nouveau = new Maillon(t);
        last->SetNext(nouveau);
        last = nouveau; //Màj du last
    }
}

/*Ajoute un trajet t en début de liste en créant un nouveau Maillon associé*/
void ListeTrajets::AddFirst(Trajet * t) {
    if(first==nullptr) { //Liste vide
        Maillon * nouveau = new Maillon(t);
        first = nouveau;
        last = nouveau;
    } else {
        Maillon * nouveau = new Maillon(t,first);
        first = nouveau; //Màj du first
    }
}

/*Ajoute un trajet t à une position pos ciblée en créant un nouveau Maillon associé.
Elle l'ajoute entre le maillon de la liste situé à la position pos et son suivant.*/
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


/*Retirer le DERNIER maillon de la liste et renvoie son pointeur.
Il faut penser à le delete par la suite.*/
Maillon * ListeTrajets::Supprimer(){
    Maillon * toReturn;
    if(first!=nullptr) {
        toReturn = last;
        if(first==last) { //Liste à un élément. La liste deviendra donc vide après le retrait.
            first = last = nullptr;
        } else { //Liste à plusieurs éléments.
            Maillon * actuel = first;
            while(actuel->GetNext()->GetNext()!=nullptr){ //On fait le parcours jusqu'à l'AVANT DERNIER Maillon.
                actuel = actuel->GetNext();
            } //L'avant dernier maillon devient le dernier de la liste.
            actuel->SetNext(nullptr);
            last = actuel;
        }
    } else { //Liste vide.
        toReturn = nullptr;
    }
    return toReturn;
}


/*Renvoie le nombre d'éléments de la liste*/
int ListeTrajets::GetLength() {
    int nbItems=1;
    Maillon * actuel = first;

    while(actuel->GetNext()!=nullptr){
        actuel = actuel->GetNext();
        nbItems++;
    }

    return nbItems;
}

/*Retourne le pointeur sur le dernier maillon de la liste.*/
Maillon * ListeTrajets::GetLast() {
    return last;
}

/*Retourne le pointeur sur le maillon à la position pos.*/
Maillon * ListeTrajets::GetPos(int pos) {

    if(first==nullptr || pos>GetLength()) { //Position en dehors de la taille de la Liste/liste vide
        return nullptr;
    }
    Maillon * actuelle = first; //Sinon algo de parcours classique !
    for(int i=0;i<pos;i++) {
        actuelle = actuelle->GetNext();
    }
    return actuelle;
}


/*Affiche le contenu de chaque maillon de la liste.*/
void ListeTrajets::Afficher() const{
    Maillon * actuel = first;
    while(actuel!=nullptr) {
        actuel->GetContenu()->Afficher();
        cout<<endl;
        actuel = actuel->GetNext();
    }
}

ListeTrajets::~ListeTrajets ()
{
#ifdef MAP
    cout << "Appel au destructeur de <ListeTrajets>" << endl;
#endif
    if(first!=nullptr) { //Liste non vide :
        delete first; //En détruisant first, on détruit tous les maillons.
        //En effet, le destructeur de maillon est conçu pour aussi détruire le maillon pointé suivant.
    }
}
