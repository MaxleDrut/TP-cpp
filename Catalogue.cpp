/*Catalogue permet de stocker un ensemble de Trajet de manière ordonnée
à l'aide d'une ListeTrajets. Les trajets sont uniques et classés par ordre alphabétique
sur la ville de départ puis sur la ville d'arrivée.
Catalogue contient les algorithmes de recherche simple et recherche avancée
conformément au cahier des charges.*/

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

/*Ajoute un trajet au Catalogue en respectant l'ordre alphabétique de la liste.
(trié sur la ville de départ puis sur la ville d'arrivée)
Si le trajet existe déjà dans le Catalogue, renvoie le code DOUBLON. Sinon,
renvoie le code FAIT*/
codeAjout Catalogue::AjoutCatalogue(Trajet * trajet) {
    if(liste->GetLast() == nullptr) { //Liste initialement vide
        liste->AddLast(trajet);
        return FAIT;
    }

    int i = 0;
    Maillon * actuel = liste->GetPos(0); //Parcours linéaire, complexité O(n)

    //Comparaison des villes de départ
    while(actuel!=nullptr && (strncmp(trajet->GetDepart(),actuel->GetContenu()->GetDepart(),plusPetitString(trajet->GetDepart(),actuel->GetContenu()->GetDepart()))>0) ) {
        actuel = actuel->GetNext();
        i++;
    }

    if(actuel==nullptr) { //Ajout en fin de liste
        liste->AddLast(trajet); //AddLast + rapide que AddPos. Autant l'utiliser !
        return FAIT;
    }

    if(strncmp(trajet->GetDepart(), actuel->GetContenu()->GetDepart(),plusPetitString(trajet->GetDepart(),actuel->GetContenu()->GetDepart())) != 0) {
        //Position trouvée : la ville de départ n'est pas en double dans le catalogue : on peut ajouter directement.
        liste->AddPos(trajet,i);
        return FAIT;
    } else { //Ville de départ identique : on compare sur la ville d'arrivée
        while(actuel != nullptr && (strncmp(trajet->GetArrivee(), actuel->GetContenu()->GetArrivee(),plusPetitString(trajet->GetArrivee(),actuel->GetContenu()->GetArrivee())) > 0) && strncmp(trajet->GetDepart(),actuel->GetContenu()->GetDepart(),plusPetitString(trajet->GetDepart(),actuel->GetContenu()->GetDepart())) == 0){
            actuel=actuel->GetNext();
            i++;
        }
        if(actuel==nullptr) { //Fin de liste
            liste->AddLast(trajet);
            return FAIT;
        }
        if(strncmp(trajet->GetArrivee(), actuel->GetContenu()->GetArrivee(),plusPetitString(trajet->GetArrivee(),actuel->GetContenu()->GetArrivee())) != 0) {
            //Pas la même ville d'arrivée.
            liste->AddPos(trajet,i);
            return FAIT;
        } else { //Même villes de départ et arrivée : on ajoute que si le doublon n'est pas sur deux trajets simples
            if((typeid(*trajet) == typeid(TrajetSimple)) && typeid(*actuel->GetContenu()) == typeid(TrajetSimple)) {
                delete trajet; //Le trajet sera stocké nulle part, il faut donc bien le supprimer avant !!
                return DOUBLON;
            } else {
                liste->AddPos(trajet,i);
                return FAIT;
            }
        }
    }
}

/*Parcours la liste et affiche tous les trajets ayant la meme chaîne de caractères que depart et arrivée.
Renvoie TROUVE s'il y a eu au moins une occurence. Renvoie PAS_TROUVE sinon*/
codeRecherche Catalogue::RechercheSimple(const char * depart,const char * arrivee) const {
    cout<<"Recherche simple de "<<depart<<" a "<< arrivee<<" : "<<endl<<endl;

    if(liste->GetLast() == nullptr) { //Liste initialement vide
        cout<<"Erreur 001 (liste vide)"<<endl;
        return PAS_TROUVE;
    }

    int i = 0;
    Maillon * actuel = liste->GetPos(0);
    while(actuel!=nullptr && strncmp(depart,actuel->GetContenu()->GetDepart(), plusPetitString(depart,actuel->GetContenu()->GetDepart()))>=0) {
        /*Vu que c'est trié par ordre alphabétique, on peut arrêter notre parcours
        quand la ville départ sélectionnée dépasse alphabétiquement celle recherchée*/
        if(strncmp(depart,actuel->GetContenu()->GetDepart(), plusPetitString(depart,actuel->GetContenu()->GetDepart()))==0 && strncmp(arrivee,actuel->GetContenu()->GetArrivee(), plusPetitString(arrivee,actuel->GetContenu()->GetArrivee()))==0) {
            i++;
            cout<<i<<". "<<endl;
            actuel->GetContenu()->Afficher();
        }
        actuel = actuel->GetNext();
    }
    if(i>0) {
        cout<<endl<<endl<<"Total : "<<i<<" parcour(s) possible(s)."<<endl;
        return TROUVE;
    } else {
        cout<<"Le trajet n'a pas ete trouve."<<endl;
        return PAS_TROUVE;
    }
}

/*Il s'agit d'une "extension" de la méthode RechercheSimple. On cherche désormais
toutes les combinaisons de trajets permettant de rejoindre une ville depart à une ville arrivee.
On fait appel pour cela à la méthode récursive "recherche"
On affiche toutes les combinaisons trouvées. On renvoie TROUVE s'il y a eu au moins
une occurence. On renvoie PAS_TROUVE sinon*/

codeRecherche Catalogue::RechercheAvancee(const char * depart, const char * arrivee) const {
    cout<<endl<<"Recherche Avancee de "<<depart<<" a "<< arrivee<<" : "<<endl<<endl;
    if(liste->GetLast() == nullptr) { //Liste initialement vide
        cout<<"Erreur 001 (liste vide)"<<endl;
        return PAS_TROUVE;
    }

    Maillon * actuel = liste->GetPos(0);
    while(actuel!=nullptr && strncmp(depart, actuel->GetContenu()->GetDepart(),plusPetitString(depart, actuel->GetContenu()->GetDepart()))!=0){
        actuel=actuel->GetNext();
    }

    ListeTrajets * cherche = new ListeTrajets();
    ListeTrajets * listeAfficher = new ListeTrajets();
    int parcours =0;
    if(actuel!=nullptr){
        //Si on trouve dans le catalogue la ville de départ indiquée on lance une recherche
        parcours = recherche(depart, arrivee, parcours, cherche, listeAfficher);
        if(parcours==0){
            cout<<"Pas de trajets trouves"<<endl;
            delete cherche;
            delete listeAfficher;
            return PAS_TROUVE;
        }
        cout<<endl<<"Total : "<<parcours<<" parcour(s) possible(s)"<<endl;
        delete cherche;
        delete listeAfficher;
        return TROUVE;
    }else if(actuel!=nullptr){
        cout<<"Pas de trajet trouve"<<endl;
        delete cherche;
        delete listeAfficher;
        return PAS_TROUVE;
    }

    delete cherche;
    delete listeAfficher;

    return PAS_TROUVE;
}


/*Affiche tous les trajets contenus dans Catalogue*/
void Catalogue::AfficheCatalogue() const{
    liste->Afficher();
}

/*Il s'agit d'une méthode récursive pour la recherche avancée qui prend en paramètre une ville de départ da
et la ville d'arrivée av attendue par la recherche avancée.
Elle contient la liste listeAfficher qui contient tous les trajets recensés lors des précédents appels à recherche.
La méthode va regarder tous les trajets du Catalogue partant de la ville de départ da :
S'il y a un trajet menant directement à l'arrivée av, elle affiche ce trajet ainsi que toutes les étapes précendentes
Sinon, elle ajoute cette étape à la liste ListeAfficher et refait un appel à la méthode recherche avec la nouvelle ville d'arrivée.

Elle renvoie un int qui compte tous les parcours possibles à partir de da en ajoutant les occurences trouvées précédemment par nbt.*/

int Catalogue::recherche(const char * da,const  char * av, int nbT, ListeTrajets * trajetRech, ListeTrajets * listeAfficher) const {
    Maillon * actuel = liste->GetPos(0);
    int nbCharDepart = plusPetitString(da,actuel->GetContenu()->GetDepart());
    int nbCharArrivee= plusPetitString(av,actuel->GetContenu()->GetArrivee());
    while(actuel!=nullptr && strncmp(da,actuel->GetContenu()->GetDepart(), nbCharDepart)>=0) {
           if(strncmp(da,actuel->GetContenu()->GetDepart(),nbCharDepart)==0 && strncmp(av,actuel->GetContenu()->GetArrivee(),nbCharArrivee)==0 && verif(da,av,trajetRech)){ //Si on trouve un trajet arrivant à la ville d'arrivée voulue, on affiche tout le parcour (listeAfficher)
                nbT++;
                listeAfficher->AddLast(actuel->GetContenu()->Dupliquer());
                cout<<nbT<<" . "<<endl;
                listeAfficher->Afficher();
                delete listeAfficher->Supprimer(); //On supprime le dernier trajet ajouté pour continuer la recherche avec le trajet du catalogue suivant
            }else if(strncmp(da,actuel->GetContenu()->GetDepart(),nbCharDepart)==0 && strncmp(av,actuel->GetContenu()->GetArrivee(),nbCharArrivee)!=0 && verif(da,actuel->GetContenu()->GetArrivee(),trajetRech)){ //Si la ville d'arrivée ne correspond pas, on relance une recherche sur celle ci
                trajetRech->AddLast(actuel->GetContenu()->Dupliquer());
                listeAfficher->AddLast(actuel->GetContenu()->Dupliquer());
                nbT=recherche(actuel->GetContenu()->GetArrivee(), av, nbT, trajetRech,listeAfficher);

                //On supprime le dernier trajet ajouté pour continuer la recherche avec le trajet du catalogue suivant
                delete trajetRech->Supprimer();
                delete listeAfficher->Supprimer();
            }
            actuel = actuel->GetNext();
    }
    return nbT;

}

/*La méthode verif est utilisée par la méthode recherche. Elle prend en paramètres
une ville de départ (da) et une ville d'arrivée (av) ainsi que la liste des trajets
déja recherchés. On parcourt cette liste pour voir si notre ville de départ et notre
ville d'arrivée forment un trajet déja présent dans listeRech. Si c'est le cas
la méthode retourne faux pour ne pas refaire une recherche sur ce trajet (et donc
éviter une boucle infinie) sinon elle retourne vrai.*/
bool Catalogue::verif(const char * da, const char * av, ListeTrajets * listeRech) const {
    if(listeRech->GetPos(0)==nullptr){ //liste initialement vide
        return true;
    }

    Maillon * actuel = listeRech->GetPos(0);
    bool arret = false;

    while(arret!=true && actuel!=nullptr){

        if(strncmp(da,actuel->GetContenu()->GetDepart(),plusPetitString(da,actuel->GetContenu()->GetDepart()))==0 && strncmp(av,actuel->GetContenu()->GetArrivee(),plusPetitString(av,actuel->GetContenu()->GetArrivee()))==0){
            arret=true;
        }else if(strncmp(av,actuel->GetContenu()->GetDepart(),plusPetitString(av,actuel->GetContenu()->GetDepart()))==0 && strncmp(da,actuel->GetContenu()->GetArrivee(),plusPetitString(da,actuel->GetContenu()->GetArrivee()))==0){
            arret=true;
        }
        actuel=actuel->GetNext();
    }
    if(arret==true){
        return false;
    }else{
        return true;
    }
}

/*Renvoie la taille du plus petit string entre a et b.
Utilisé pour nos appels à la méthode strncmp*/
int Catalogue::plusPetitString(const char * a,const char * b) const {
    if(strlen(a)>strlen(b)) {
        return strlen(b);
    } else {
        return strlen(a);
    }
}
