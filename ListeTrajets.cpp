/*La classe ListeTrajets représentent une liste chainée de trajets.
Elle se compose de maillons qui contiennent un trajet chacun.
On la définie avec un maillon de début et un maillon de fin.
La liste peut être utilisée par le catalogue pour stocker des
trajets simples ou composés, ou par les trajets composés pour stocker
des trajets simples.
On peut rajouter un maillon et donc un trajet à n'importe quelle
position dans la liste entre le premier maillon et le dernier.
On peut également supprimer le maillon se trouvant en fin de liste
*/


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


/*Renvoie le pointeur du maillon qui a été retiré de la liste. Il faut le delete en dehors.
A la base, nous souhaitions le supprimer dans cette méthode, mais vu que deux mêmes listes peuvent
utiliser la même adresse il faut s'assurer que le maillon a retiré partout*/
Maillon * ListeTrajets::Supprimer(){
    Maillon * toReturn;
    if(first!=nullptr) {
        toReturn = last;
        if(first==last) {
            first = last = nullptr;
        } else {
            Maillon * actuel = first;
            while(actuel->GetNext()->GetNext()!=nullptr){
                actuel = actuel->GetNext();
            }
            actuel->SetNext(nullptr);
            last = actuel;
        }
    } else {
        toReturn = nullptr;
    }
    return toReturn;
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

    if(first==nullptr || pos>GetLength()) {
        return nullptr;
    }
    Maillon * actuelle = first;
    for(int i=0;i<pos;i++) {
        actuelle = actuelle->GetNext();
    }
    return actuelle;
}


//Cette méthode combine les tostring de tous les éléments trajets.
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
    if(first!=nullptr) {
        delete first; //En détruisant first, on détruit tous les maillons grâce au destructeur des Maillons.
    }
}
