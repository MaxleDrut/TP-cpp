/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : 13/12/20
    copyright            : (C) 2020 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//------------------------------------------------------ Include personnel

#include "Catalogue.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques



codeAjout Catalogue::AjoutCatalogue(Trajet * trajet)
//Algorithme:
//      Si la liste n'est pas vide, la méthode parcourt la ListeTrajets
//      jusqu'à que la ville de départ soit plassée dans le bon ordre
//      alphabétique. On fait de même avec la ville d'arrivée si la
//      liste contient plusieurs trajets avec la même ville de départ.
//      Si le trajet est déja dans le catalogue on ne l'ajoute pas
{
    if(liste->GetLast() == nullptr) { //Liste initialement vide
        liste->AddLast(trajet);
        return FAIT;
    }

    int i = 0;
    const Maillon * actuel = liste->GetPos(0); //Parcours linéaire, complexité O(n)

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

        if(strncmp(trajet->GetDepart(), actuel->GetContenu()->GetDepart(),plusPetitString(trajet->GetDepart(),actuel->GetContenu()->GetDepart()))!= 0 || strncmp(trajet->GetArrivee(), actuel->GetContenu()->GetArrivee(),plusPetitString(trajet->GetArrivee(),actuel->GetContenu()->GetArrivee()))!= 0) {
            //Pas la même ville d'arrivée.
            liste->AddPos(trajet,i);
            return FAIT;
        } else { //Même villes de départ et arrivée !! Vérifions s'il s'agit d'un doublon
            /*Si on a un TrajetCompo et un TrajetSimple ayant la meme villeDepart et villeArrivee dans le Catalogue que le trajet
            alors il vaut vérifier que les deux ne soient pas des doublons*/ 
            while(actuel != nullptr && (strncmp(trajet->GetArrivee(), actuel->GetContenu()->GetArrivee(),plusPetitString(trajet->GetArrivee(),actuel->GetContenu()->GetArrivee())) == 0) && strncmp(trajet->GetDepart(),actuel->GetContenu()->GetDepart(),plusPetitString(trajet->GetDepart(),actuel->GetContenu()->GetDepart())) == 0){
                cout<<typeid(*trajet).name()<<endl;
                cout<<typeid(*actuel->GetContenu()).name()<<endl;

                if( typeid(*trajet)== typeid(TrajetSimple) && typeid(*actuel->GetContenu()) ==typeid(TrajetSimple)) {
                    //Les deux trajet sont des trajets simples --> forcément un doublon !
                    delete trajet; //Le trajet sera stocké nulle part, il faut donc bien le supprimer avant !!
                    return DOUBLON;

                }else if(typeid(*trajet) == typeid(TrajetCompo) && typeid(*actuel->GetContenu()) == typeid(TrajetCompo)) {
                    //Le deux sont des trajets compo ! Il faut comparer leur nombre d'étapes pour commencer.
                    const TrajetCompo * tCompoA = dynamic_cast<const TrajetCompo *> (trajet); //Transtypage ici nécessaire pour récup la liste des étapes
                    const TrajetCompo * tCompoB = dynamic_cast<const TrajetCompo *> (actuel->GetContenu());

                    if(tCompoA->GetListe()->GetLength() == tCompoB->GetListe()->GetLength()) {
                        //Deux trajets composés de même taille : doublon si toutes les étapes sont identiques
                        const Maillon * maillonA = tCompoA->GetListe()->GetPos(0); //Récup des étapes du trajet à ajouter
                        const Maillon * maillonB = tCompoB->GetListe()->GetPos(0); //Et récup des étapes trajet 'identique' à comparer

                        //On compare les étapes 1 à 1 pour voir si elles ont toutes la même ville de départ et ville d'arrivée
                        while(maillonA!=nullptr && strcmp(maillonA->GetContenu()->GetDepart(),maillonB->GetContenu()->GetDepart()) == 0 && strcmp(maillonA->GetContenu()->GetArrivee(),maillonB->GetContenu()->GetArrivee()) == 0) {
                            maillonA = maillonA->GetNext();
                            maillonB = maillonB->GetNext();
                        }

                        if(maillonA == nullptr) {
                            //On est sorti du while : si maillonA vaut nullptr alors toutes les étapes sont égales ! C'est donc un doublon
                            delete trajet;
                            return DOUBLON;
                        } else {
                            liste->AddPos(trajet,i);
                            return FAIT;
                        }
                    } else {
                        //Nombre d'étapes différent : pas un doublon
                        liste->AddPos(trajet,i);
                        return FAIT;
                    }
                }
                actuel=actuel->GetNext();

            }
            //Sinon si l'on a un TrajetSimple et unTrajetCompo alors ce n'est PAS un doublon !
            liste->AddPos(trajet,i);
            return FAIT;
        }
    }
}//----- Fin de AjoutCatalogue



codeRecherche Catalogue::RechercheSimple(const char * depart,const char * arrivee) const
//Algorithme:
//      Parcourt la liste et affiche chaque trajet ayant la même ville de départ et d'arrivée
//      que les villes passées en paramètres.
{
    cout<<"Recherche simple de "<<depart<<" a "<< arrivee<<" : "<<endl<<endl;

    if(liste->GetLast() == nullptr) { //Liste initialement vide
        cout<<"Erreur 001 (liste vide)"<<endl;
        return PAS_TROUVE;
    }

    int i = 0;
    const Maillon * actuel = liste->GetPos(0);
    while(actuel!=nullptr && strncmp(depart,actuel->GetContenu()->GetDepart(), plusPetitString(depart,actuel->GetContenu()->GetDepart()))>=0) {
        /*Vu que c'est trié par ordre alphabétique, on peut arrêter notre parcours
        quand la ville départ sélectionnée dépasse alphabétiquement celle recherchée*/
        if(strncmp(depart,actuel->GetContenu()->GetDepart(), plusPetitString(depart,actuel->GetContenu()->GetDepart()))==0 && strncmp(arrivee,actuel->GetContenu()->GetArrivee(), plusPetitString(arrivee,actuel->GetContenu()->GetArrivee()))==0) {
            i++;
            cout<<i<<" : ";
            actuel->GetContenu()->Afficher();
            cout<<endl;
        }
        actuel = actuel->GetNext();
    }
    if(i>0) {
        cout<<endl<<"Total : "<<i<<" parcour(s) possible(s)."<<endl;
        return TROUVE;
    } else {
        cout<<endl<<"Le trajet n'a pas ete trouve."<<endl;
        return PAS_TROUVE;
    }
}//----- Fin de RechercheSimple


codeRecherche Catalogue::RechercheAvancee(const char * depart, const char * arrivee) const
//Algorithme:
//      Parcourt la liste jusqu'à la ville de départ passée en paramètre puis appelle la Méthode
//      récursive recherche qui affichera et renverra le nombre de parcours possibles. Si la liste
//      est vide ou que la recherche renvoie 0 alors il n'y a pas de parcours trouvés.
{
    cout<<endl<<"Recherche Avancee de "<<depart<<" a "<< arrivee<<" : "<<endl<<endl;
    if(liste->GetLast() == nullptr) { //Liste initialement vide
        cout<<"Erreur 001 (liste vide)"<<endl;
        return PAS_TROUVE;
    }

    const Maillon * actuel = liste->GetPos(0);
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
        cout<<"Total : "<<parcours<<" parcour(s) possible(s)"<<endl;
        delete cherche;
        delete listeAfficher;
        return TROUVE;
    }

    cout<<"Pas de trajet trouve"<<endl;
    delete cherche;
    delete listeAfficher;
    return PAS_TROUVE;


}//----- Fin de RechercheAvancee



void Catalogue::AfficheCatalogue() const
//Algorithme: Aucun
{
    liste->Afficher();
}//----- Fin de AfficheCatalogue


codeFichier Catalogue::ImportFichier(const string nomFichier)
//Algorithme:
//      Pour ajouter les trajets dans le catalogue, il faut lire le
//      fichier, extraire ses données et distinguer les TrajetSimple
//      des TrajetCompo. S'il est écrit TS dans le fichier alors
//      on récupère les données du TrajetSimple et lorsque le charactère '/' apparait
//      dans le fichier on ajoute ce trajet au Catalogue cat. S'il est écrit TC alors
//      on récupére les données de chaque TrajetSimple comme précedemment jusqu'à
//      trouver le charactère ';' indiquant qu'il faut ajouter un TrajetCompo au Catalogue cat.
{
    ifstream flux(nomFichier + ".cat");
    string lecture;
    string depart, arrivee, transport;
    int compteLigne = 1;

    if(flux) { //True si ouverture valide
        getline(flux,lecture);
        while(lecture!="\0") {
            if(lecture == "TS") {
                getline(flux,depart);
                getline(flux,arrivee);
                getline(flux,transport);
                getline(flux,lecture); //Vérifie que l'on a bien un /
                if(lecture == "/") {
                    AjoutCatalogue(new TrajetSimple(depart.c_str(),arrivee.c_str(),transport.c_str()));
                } else {
                    cout<<"Erreur : Lecture invalide d'un trajet simple à la ligne "<<compteLigne<<endl;
                }
                compteLigne=compteLigne+4;
            }
            if (lecture == "TC") {
                ListeTrajets * listeCompo = new ListeTrajets();
                getline(flux,lecture); //Nécessaire pour dissocier le cas "/ Lyon" et "/ ;"
                while(lecture!=";") {
                    depart = lecture;
                    getline(flux,arrivee);
                    getline(flux,transport);
                    getline(flux,lecture); //Fin d'un trajet simple du trajet compo.
                    if(lecture == "/") {
                        listeCompo->AddLast(new TrajetSimple(depart.c_str(),arrivee.c_str(),transport.c_str()));
                    } else {
                        cout<<"Erreur : Lecture invalide d'un trajet composé à la ligne "<<compteLigne<<endl;
                    }
                    compteLigne=compteLigne+4;
                    getline(flux,lecture);
                }
                compteLigne++;
                AjoutCatalogue(new TrajetCompo(listeCompo));
            }
            getline(flux,lecture);
            compteLigne++;
        }
        return OK;
    } else {
        return ERR;
     }

}//------ Fin de importFichier

codeFichier Catalogue::EcritureFichier(const string nomFichier, const string typeAttendu, const char * villeDepart, const char * villeArrivee)
//Algorithme:
//      Si le flux s'ouvre bien, on parcours le catalogue et on écrit
//      dans nomFichier le contenu de chaque Trajet du catalogue en
//      précisant si c'est un TrajetSimple ou un TrajetCompo.
//      On vérifie aussi si l'utilisateur veut ajouter seulement
//      la ville de départ et/ou la ville d'arrivée, s'il entre All
//      alors on ajoute toutes les villes.
//      Types attendus : ALL/TS/TC
//      villeDepart: ALL/VilleDepart
//      villeArrivee: ALL/villeArrivee
{
    ofstream flux(nomFichier  + ".cat");
    string str;
    if(flux){  //On teste si tout est OK
        const Maillon * actuel = liste->GetPos(0);
        while(actuel!=nullptr){
            if((strcmp(villeDepart,"all")==0 || strcmp(villeDepart,actuel->GetContenu()->GetDepart()) == 0) && (strcmp(villeArrivee,"all")==0 || strcmp(villeArrivee,actuel->GetContenu()->GetArrivee()) == 0 )) {
                if(typeid(*actuel->GetContenu())==typeid(TrajetSimple) && (typeAttendu == "all" || typeAttendu == "ts")) {
                    const TrajetSimple * trajS = dynamic_cast<const TrajetSimple *> (actuel->GetContenu());
                    flux<<"TS"<<endl;
                    str=trajS->GetDepart();
                    flux<<str<<endl;
                    str=trajS->GetArrivee();
                    flux<<str<<endl;
                    str=trajS->GetTransport();
                    flux<<str<<endl;
                    flux<<"/"<<endl;
                }else if(typeid(*actuel->GetContenu())==typeid(TrajetCompo) && (typeAttendu == "all" || typeAttendu == "tc")){
                    const TrajetCompo * trajC = dynamic_cast<const TrajetCompo *> (actuel->GetContenu());
                    flux<<"TC"<<endl;
                    const Maillon * m = trajC->GetListe()->GetPos(0);
                    while(m!=nullptr){
                        const TrajetSimple * trajS = dynamic_cast<const TrajetSimple *> (m->GetContenu());
                        str=trajS->GetDepart();
                        flux<<str<<endl;
                        str=trajS->GetArrivee();
                        flux<<str<<endl;
                        str=trajS->GetTransport();
                        flux<<str<<endl;
                        flux<<"/"<<endl;
                        m=m->GetNext();
                    }
                    flux<<";"<<endl;
                }
            }
            actuel=actuel->GetNext();
        }
        return OK;
    }else{
        return ERR;
    }

}//-----Fin de ecritureFichier

const ListeTrajets * Catalogue::GetListe() const
//Algorithme: Aucun
{
    return liste;
}//----- Fin de GetListe

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes prrivées



int Catalogue::recherche(const char * da,const  char * av, int nbT, ListeTrajets * trajetRech, ListeTrajets * listeAfficher) const
//Algorithme:
//      On parcours la ListeTrajets du Catalogue jusqu'à tomber sur la ville de départ da.
//      Si la ville de départ du Maillon actuel et sa ville d'arrivée sont égaux aux villes da
//      et av alors on incrémente le nombre de parcours trouvés puis on affiche tous les trajets du parcours
//      stockés dans listeAfficher.
//      Si la ville d'arrivée du Maillon actuel n'est pas égale à av mais que la ville de départ est
//      celle attendue (da) alors on ajoute le trajet à la liste de trajet déja recherchés et à la liste du parcours
//      à afficher puis on rappelle recherche avec la nouvelle ville d'arrivée comme ville de départ.
//      Sinon on continue à parcourir la liste jusqu'à changer de ville de départ.
{
    const Maillon * actuel = liste->GetPos(0);
    int nbCharDepart = plusPetitString(da,actuel->GetContenu()->GetDepart());
    int nbCharArrivee= plusPetitString(av,actuel->GetContenu()->GetArrivee());
    while(actuel!=nullptr && strncmp(da,actuel->GetContenu()->GetDepart(), nbCharDepart)>=0) {

            //Si on trouve un trajet arrivant à la ville d'arrivée voulue, on affiche tout le parcour (listeAfficher)
           if(strncmp(da,actuel->GetContenu()->GetDepart(),nbCharDepart)==0 && strncmp(av,actuel->GetContenu()->GetArrivee(),nbCharArrivee)==0 && verif(da,av,trajetRech)){
                nbT++;
                listeAfficher->AddLast(actuel->GetContenu()->Dupliquer());
                cout<<nbT<<" : ";
                listeAfficher->Afficher();
                cout<<endl;
                //On supprime le dernier trajet ajouté pour continuer la recherche avec le trajet du catalogue suivant
                delete listeAfficher->Supprimer();
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

}//----- Fin de recherche


bool Catalogue::verif(const char * da, const char * av, ListeTrajets * listeRech) const
//Algorithme:
//      Parcourt la liste de trajets déja recherchés. Si da et av sont respectivement égaux
//      aux villes de départ et d'arrivée du Maillon actuel ou si da est égal à la ville d'arrivée et
//      av à la ville de départ, la méthode retourne faux pour ne pas refaire une recherche sur ce trajet (et donc
//      éviter une boucle infinie dans recherche)
{
    if(listeRech->GetPos(0)==nullptr){ //liste initialement vide
        return true;
    }

    const Maillon * actuel = listeRech->GetPos(0);
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
}//----- Fin de verif


int Catalogue::plusPetitString(const char * a,const char * b) const
//Algorithme: Aucun
{
    if(strlen(a)>strlen(b)) {
        return strlen(b);
    } else {
        return strlen(a);
    }
}//----- Fin de plusPetitString


//-------------------------------------------- Constructeurs - destructeur

Catalogue::Catalogue()
//Algorithme: Aucun
{
    #ifdef MAP
        cout << "Appel au constructeur de <Catalogue>" << endl;
    #endif
    liste = new ListeTrajets();
}//------ Fin de Catalogue


Catalogue::~Catalogue()
//Algorithme: Aucun
{
    #ifdef MAP
        cout << "Appel au destructeur de <Catalogue>" << endl;
    #endif
    delete liste;
}//----- Fin de ~Catalogue
