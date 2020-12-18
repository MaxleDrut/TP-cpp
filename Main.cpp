/*************************************************************************
                           Main  -  description
                             -------------------
    début                : 13/12/20
    copyright            : (C) 2020 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Main> (fichier Main.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//------------------------------------------------------ Include personnel

#include "TrajetSimple.h"
#include "ListeTrajets.h"
#include "Maillon.h"
#include "TrajetCompo.h"
#include "Catalogue.h"

//----------------------------------------------------------------- Types
enum codeFichier {OK,ERR};

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
codeFichier importFichier(const string nomFichier, Catalogue * cat);
codeFichier ecritureFichier(const string nomFichier, Catalogue * cat);

int main()
//Algorithme:
//      L'uilisateur saisie une action à faire dans le terminal. En fonction
//      de la saisie, la méthode Main va utiliser les différentes méthodes
//      de pointeur de type Catalogue crée au début du code.
{
    string nomFichier;
    char saisie [100];
    char depart[100];
    char arrivee[100];
    char transport[100];
    saisie[0] = '\0';
    codeAjout resultat;
    codeFichier retourFichier;
    Catalogue * cat = new Catalogue();


    cout<<"Easy Travel : la solution intelligente pour tous vos deplacements"<<endl;
    cout<<"(dans la limite des trajets disponibles)"<<endl<<endl;

    while(strcmp(saisie,"fin")!=0) {
        cout<<"Lexique :"<<endl<<"import : importe les trajets d'un fichier .cat"<<endl<<"ajout : Creer un trajet"<<endl<<"rs : Recherche simple"<<endl<<"ra : Recherche avancee"<<endl<<"voir : Afficher le catalogue"<<endl<<"fin : Detruit le catalogue et ferme l'application"<<endl<<"sauver : Sauvegarde le catalogue actuel dans un fichier .cat"<<endl<<endl;
        cin>>saisie;
        if(strcmp(saisie,"ajout")==0) {
            int nbTraj;
            resultat = FAIT;
            cout<<"Combien de trajets ? (1 = Trajet simple | >1 = Trajet Compose)"<<endl;
            cin>>nbTraj;
            while(nbTraj<1) {
                cout<<"Veuillez taper un nombre valide (>0)"<<endl;
                fflush(stdin);
                cin>>nbTraj;
            }
            cout<<"Veuillez renseigner le trajet sous la forme <depart> <arrivee> <transport>"<<endl;

            if(nbTraj==1) { //Trajet simple
                cin>>depart>>arrivee>>transport;
                resultat = cat->AjoutCatalogue(new TrajetSimple(depart,arrivee,transport));
            } else { //Si il y a plusieurs trajet demandés, on crée une liste à laquelle on ajoute chque trajet rentrée par l'utilisateur. On crée ensuite notre TrajetCompo qu'on ajoute au Catalogue
                ListeTrajets * listeCompo = new ListeTrajets();
                for(int i=1;i<=nbTraj;i++) {
                    cout<<"Trajet "<<i<<" : ";
                    cin>>depart>>arrivee>>transport;

                    if(i>1 && strcmp(listeCompo->GetLast()->GetContenu()->GetArrivee(),depart)!=0)  {
                        cout<<"Etape invalide : le depart doit etre egal a l'arrivee precedente"<<endl;
                        i--;
                    } else {
                        listeCompo->AddLast(new TrajetSimple(depart,arrivee,transport));
                    }
                }
                resultat = cat->AjoutCatalogue(new TrajetCompo(listeCompo));
            }
            if(resultat == FAIT) {
                cout<<"Trajet ajoute !"<<endl;
            } else {
                cout<<"Le trajet existe deja !"<<endl;
            }
        }
        if(strcmp(saisie,"rs")==0){
            cout<<"Veuillez renseigner la requete sous la forme <depart> <arrivee>"<<endl;
            cin>>depart>>arrivee;
            cat->RechercheSimple(depart,arrivee);
        }
        if(strcmp(saisie,"ra")==0){
            cout<<"Veuillez renseigner la requete sous la forme <depart> <arrivee>"<<endl;
            cin>>depart>>arrivee;
            cat->RechercheAvancee(depart,arrivee);
        }
        if(strcmp(saisie,"voir")==0){
            cat->AfficheCatalogue();
        }
        if(strcmp(saisie,"import")==0) {
            cout<<"Nom du fichier source ? (sans l'extension .cat)"<<endl;
            cin>>nomFichier;
            retourFichier = importFichier(nomFichier,cat);
            if(retourFichier==OK) {
                cout<<"Import du fichier reussi !"<<endl;
            } else {
                cout<<"Erreur : le fichier n'a pas ete trouve / n'a pas pu etre ouvert"<<endl;
            }
        }
        if(strcmp(saisie,"sauver")==0){
            cout<<"Veuiller renseigner le nom du fichier (sans l'extension .cat) pour la sauvegarde"<<endl;
            cin>>nomFichier;
            retourFichier = ecritureFichier(nomFichier,cat);
            if(retourFichier==OK) {
                cout<<"Sauvegarde du fichier reussie !"<<endl;
            } else {
                cout<<"Erreur : impossible d'ouvrir le fichier"<<endl;
            }
        }
        cout<<endl;
    }

    delete cat;
    cout<<"Passez une bonne journee !";
    return 0;
}//----Fin du Main

codeFichier importFichier(const string nomFichier, Catalogue * cat) {
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
                    cat->AjoutCatalogue(new TrajetSimple(depart.c_str(),arrivee.c_str(),transport.c_str()));
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
                cat->AjoutCatalogue(new TrajetCompo(listeCompo));
            }
            getline(flux,lecture);
            compteLigne++;
        }
        return OK;
    } else {
        return ERR;
     }

}

codeFichier ecritureFichier(const string nomFichier, Catalogue * cat)
//Algorithme:
//      Si le flux s'ouvre bien, on parcours le catalogue et on écrit
//      dans nomFichier le contenu de chaque Trajet du catalogue en
//      précisant si c'est un TrajetSimple ou un TrajetCompo
{
    ofstream flux(nomFichier  + ".cat");
    string str;
    if(flux){  //On teste si tout est OK
        const Maillon * actuel = cat->GetListe()->GetPos(0);
        while(actuel!=nullptr){
            if(typeid(*actuel->GetContenu())==typeid(TrajetSimple)){
                const TrajetSimple * trajS = dynamic_cast<const TrajetSimple *> (actuel->GetContenu());
                flux<<"TS"<<endl;
                str=trajS->GetDepart();
                flux<<str<<endl;
                str=trajS->GetArrivee();
                flux<<str<<endl;
                str=trajS->GetTransport();
                flux<<str<<endl;
                flux<<"/"<<endl;
            }else if(typeid(*actuel->GetContenu())==typeid(TrajetCompo)){
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
            actuel=actuel->GetNext();
        }
        return OK;
    }else{
        return ERR;
    }

}//-----Fin de ecritureFichier
