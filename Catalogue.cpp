#include <cstring>
#include <iostream>
using namespace std;

#include "Catalogue.h"

Catalogue::Catalogue() {
    #ifdef MAP
        cout << "Appel au constructeur de <Catalogue>" << endl;
    #endif
    liste = new ListeTrajets();
}
Catalogue::~Catalogue() {
    #ifdef MAP
        cout << "Appel au destructeur de <Catalogue>" << endl;
    #endif
    delete liste;
}

codeAjout Catalogue::AjoutCatalogue(Trajet * trajet) {
    if(liste->GetLast() == nullptr) { //Liste initialement vide
        liste->AddLast(trajet);
        return FAIT;
    }

    int i = 0;
    Maillon * actuel = liste->GetPos(0); //Parcours linéaire, complexité O(n)

    while(actuel!=nullptr && (strncmp(trajet->GetDepart(),actuel->GetContenu()->GetDepart(),PlusPetitString(trajet->GetDepart(),actuel->GetContenu()->GetDepart()))>0) ) { //Compare sur la ville de départ
        actuel = actuel->GetNext();
        i++;
    }

    if(actuel==nullptr) {
        liste->AddLast(trajet);
        return FAIT;
    }

    if(strncmp(trajet->GetDepart(), actuel->GetContenu()->GetDepart(),PlusPetitString(trajet->GetDepart(),actuel->GetContenu()->GetDepart())) < 0) { //Pas la même ville de départ
        liste->AddPos(trajet,i);
        return FAIT;
    } else { //Ville de départ identique : on compare la ville d'arrivée
        while(actuel != nullptr && (strncmp(trajet->GetArrivee(), actuel->GetContenu()->GetArrivee(),PlusPetitString(trajet->GetArrivee(),actuel->GetContenu()->GetArrivee())) > 0) && strncmp(trajet->GetDepart(),actuel->GetContenu()->GetDepart(),PlusPetitString(trajet->GetDepart(),actuel->GetContenu()->GetDepart())) == 0){
            actuel=actuel->GetNext();
            i++;
        }
        if(actuel==nullptr) {
            liste->AddLast(trajet);
            return FAIT;
        }
        if(strncmp(trajet->GetArrivee(), actuel->GetContenu()->GetArrivee(),PlusPetitString(trajet->GetArrivee(),actuel->GetContenu()->GetArrivee())) < 0) { //Pas la même ville de départ
            liste->AddPos(trajet,i);
            return FAIT;
        } else { //Même ville d'arrivée : on ajoute que si le doublon n'est pas sur deux trajets simples
            if((typeid(*trajet) == typeid(TrajetSimple)) && typeid(*actuel->GetContenu()) == typeid(TrajetSimple)) {
                return DOUBLON;
            } else {
                liste->AddPos(trajet,i);
                return FAIT;
            }
        }
    }
}


codeRecherche Catalogue::RechercheSimple(const char * depart,const char * arrivee) const {
    cout<<"Recherche simple de "<<depart<<" a "<< arrivee<<" : "<<endl<<endl;

    if(liste->GetLast() == nullptr) { //Liste initialement vide
        cout<<"Erreur 001 (liste vide)"<<endl;
        return PAS_TROUVE;
    }

    int i = 0;
    Maillon * actuel = liste->GetPos(0);
    while(actuel!=nullptr && strncmp(depart,actuel->GetContenu()->GetDepart(), PlusPetitString(depart,actuel->GetContenu()->GetDepart()))>=0) { //Vu que c'est trié par ordre alphabétique, pas besoin de parcourir toute la liste quand on a dépassé le départ
        if(strncmp(depart,actuel->GetContenu()->GetDepart(), PlusPetitString(depart,actuel->GetContenu()->GetDepart()))==0 && strncmp(arrivee,actuel->GetContenu()->GetArrivee(), PlusPetitString(arrivee,actuel->GetContenu()->GetArrivee()))==0) {
            actuel->GetContenu()->Afficher();
            i++;
        }
        actuel = actuel->GetNext();
    }
    if(i>0) {
        cout<<endl<<endl<<"Total : "<<i<<" parcours possible(s)."<<endl;
    } else {
        cout<<"Le trajet n'a pas ete trouve."<<endl;
    }
    return TROUVE;
}
codeRecherche Catalogue::RechercheAvancee(const char * depart, const char * arrivee) const {
    return TROUVE;
}

void Catalogue::AfficheCatalogue() const{
    liste->Afficher();
}

//Renvoie la taille du plus petit string. Utilisé pour strncmp.
int Catalogue::PlusPetitString(const char * a,const char * b) const {
    if(strlen(a)>strlen(b)) {
        return strlen(b);
    } else {
        return strlen(a);
    }
}
