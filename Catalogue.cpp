/*La classe Catalogue permet de stocker et de lire des trajets.
Elle se compose enfait d'une liste chaînée de trajets simples ou composés.
On peut y ajouter n'importe quel trajet si ce dernier n'est pas déja stocké,
et le catalogue les classe par ordre alphabétique pour une
lecture plus agréable. S'il on veut chercher un moyen d'aller
d'une ville de départ à une ville d'arrivée, on peut effectuer une
recherche simple ou une recherche avancée qui nous fournira tous les
trajets possibles.*/




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


/*Cette méthode recoit un pointeur vers trajet simple ou composé en paramètre
pour pouvoir l'ajouter dans la liste du catalogue. A chaque ajout on
fait en sorte de le classer par ordre alphabétique, d'abord sur la ville de départ
puis sur la ville d'arrivée. Si deux trajets simples ont la même ville de départ
et la même ville d'arrivée alors on considère que c'est un DOUBLON,
on ne l'ajoute pas au catalogue et la méthode retourne le codeAdd: DOUBLON.
Si le trajet est bien ajouté on retourne FAIT.*/
codeAjout Catalogue::AjoutCatalogue(Trajet * trajet) {
    if(liste->GetLast() == nullptr) { //Liste initialement vide
        liste->AddLast(trajet);
        return FAIT;
    }

    int i = 0;
    Maillon * actuel = liste->GetPos(0); //Parcours linéaire, complexité O(n)

    while(actuel!=nullptr && (strncmp(trajet->GetDepart(),actuel->GetContenu()->GetDepart(),plusPetitString(trajet->GetDepart(),actuel->GetContenu()->GetDepart()))>0) ) { //Compare sur la ville de départ
        actuel = actuel->GetNext();
        i++;
    }

    if(actuel==nullptr) {
        liste->AddLast(trajet);
        return FAIT;
    }

    if(strncmp(trajet->GetDepart(), actuel->GetContenu()->GetDepart(),plusPetitString(trajet->GetDepart(),actuel->GetContenu()->GetDepart())) != 0) { //Pas la même ville de départ
        liste->AddPos(trajet,i);
        return FAIT;
    } else { //Ville de départ identique : on compare la ville d'arrivée
        while(actuel != nullptr && (strncmp(trajet->GetArrivee(), actuel->GetContenu()->GetArrivee(),plusPetitString(trajet->GetArrivee(),actuel->GetContenu()->GetArrivee())) > 0) && strncmp(trajet->GetDepart(),actuel->GetContenu()->GetDepart(),plusPetitString(trajet->GetDepart(),actuel->GetContenu()->GetDepart())) == 0){
            actuel=actuel->GetNext();
            i++;
        }
        if(actuel==nullptr) {
            liste->AddLast(trajet);
            return FAIT;
        }
        if(strncmp(trajet->GetArrivee(), actuel->GetContenu()->GetArrivee(),plusPetitString(trajet->GetArrivee(),actuel->GetContenu()->GetArrivee())) != 0) { //Pas la même ville d'arrivée
            liste->AddPos(trajet,i);
            return FAIT;
        } else { //Même ville d'arrivée : on ajoute que si le doublon n'est pas sur deux trajets simples
            if((typeid(*trajet) == typeid(TrajetSimple)) && typeid(*actuel->GetContenu()) == typeid(TrajetSimple)) {
                delete trajet; //Le trajet sera stocké nulle part, il faut bien le supprimer avant !!
                return DOUBLON;
            } else {
                liste->AddPos(trajet,i);
                return FAIT;
            }
        }
    }
}



/*Cette méthode effectue une recherche de trajets selon le nom de la ville de départ et
le nom de la ville d'arrivée fournis en paramètre. La recherche simple affichera
seulement les parcours constitués de trajets simple ou composés sans composition
avec d'autres trajets stockés dans le catalogue. Pour ce faire, on parcours la liste
du catalogue et à chaque fois qu'on rencontre le trajet voulu on l'affiche.La méthode
retourne le codeRecherche TROUVE si au moins un parcours est trouvé et PAS_TROUVE si
il n'y a aucun Parcours correspondant aux paramètres de la recherche.*/
codeRecherche Catalogue::RechercheSimple(const char * depart,const char * arrivee) const {
    cout<<"Recherche simple de "<<depart<<" a "<< arrivee<<" : "<<endl<<endl;

    if(liste->GetLast() == nullptr) { //Liste initialement vide
        cout<<"Erreur 001 (liste vide)"<<endl;
        return PAS_TROUVE;
    }

    int i = 0;
    Maillon * actuel = liste->GetPos(0);
    while(actuel!=nullptr && strncmp(depart,actuel->GetContenu()->GetDepart(), plusPetitString(depart,actuel->GetContenu()->GetDepart()))>=0) { //Vu que c'est trié par ordre alphabétique, pas besoin de parcourir toute la liste quand on a dépassé le départ
        if(strncmp(depart,actuel->GetContenu()->GetDepart(), plusPetitString(depart,actuel->GetContenu()->GetDepart()))==0 && strncmp(arrivee,actuel->GetContenu()->GetArrivee(), plusPetitString(arrivee,actuel->GetContenu()->GetArrivee()))==0) {
            i++;
            cout<<i<<". "<<endl;
            actuel->GetContenu()->Afficher();
        }
        actuel = actuel->GetNext();
    }
    if(i>0) {
        cout<<endl<<endl<<"Total : "<<i<<" parcour(s) possible(s)."<<endl;
    } else {
        cout<<"Le trajet n'a pas ete trouve."<<endl;
    }
    return TROUVE;
}


/*Cette méthode effectue une recherche de trajets selon le nom de la ville de départ et
le nom de la ville d'arrivée fournis en paramètre. La recherche avancée affichera
les parcours constitués de trajets simple ou composés sans et avec composition
de trajets stockés dans le catalogue. Pour ce faire, on créer une liste de trajets
à afficher et de trajets en cours de recherche et on appelle une autre methode recherche
plus pousée que la recherche simple.
La méthode retourne le codeRecherche TROUVE si au moins un parcours est trouvé et PAS_TROUVE si
il n'y a aucun Parcours correspondant aux paramètres de la recherche.*/
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


/*Cette méthode affiche les trajets composants le catalogue, elle utilise la méthode
Afficher de la liste de trajets qui constitue le catalogue.*/
void Catalogue::AfficheCatalogue() const{
    liste->Afficher();
}

/*La méthode recherce est utilisée seulement par la méthode RechercheAvancee. Elle prend en
paramètres le nom de la ville de départ de chaque étapes (da), le nom de la ville d'arrivée
attendue par la RechercheAvancee (av), le nombre de parcours possibles à chaque fois trouvés (nbT),
la liste de Trajets en cours de recherche (trajetRech) et la liste de trajets à afficher
qui répond aux paramètres de la RechercheAvancee.
La méthode retourne le nombre de parcours trouvés et affiche ces parcours.
Pour effectuer cela, elle parcours la liste du catalogue. Si on trouve un Parcours
possible on l'affiche, sinon si la ville de départ correspond à celle attendue mais
pas la ville d'arrivée voulue, on rappelle la fonction recherche mais en prenant la
ville d'arrivée comme ville de départ. La méthode se base donc sur la récursivité
jusqu'à qu'on obtienne plus aucun parcours possibles. A chaque étape on vérifie
également que le trajet n'a pas déja été cherché en utilisant la méthode vérif*/

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

//Renvoie la taille du plus petit string. Utilisé par strncmp.
int Catalogue::plusPetitString(const char * a,const char * b) const {
    if(strlen(a)>strlen(b)) {
        return strlen(b);
    } else {
        return strlen(a);
    }
}
