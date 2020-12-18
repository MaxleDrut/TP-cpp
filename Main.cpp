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
codeFichier lectureFichier(const string nomFichier, Catalogue * cat);
codeFichier ecritureFichier(const string nomFichier, Catalogue * cat);

int main()
//Algorithme:
//      L'uilisateur saisie une action à faire dans le terminal. En fonction
//      de la saisie, la méthode Main va utiliser les différentes méthodes
//      de pointeur de type Catalogue crée au début du code.
{

    char saisie [100];
    char depart[100];
    char arrivee[100];
    char transport[100];
    saisie[0] = '\0';
    Catalogue * cat = new Catalogue();
    cout<<"Easy Travel : la solution intelligente pour tous vos deplacements"<<endl;
    cout<<"(dans la limite des trajets disponibles)"<<endl<<endl;

    while(strcmp(saisie,"fin")!=0) {
        cout<<"Lexique :"<<endl<<"ajout : Creer un trajet"<<endl<<"rs : Recherche simple"<<endl<<"ra : Recherche avancee"<<endl<<"voir : Afficher le catalogue"<<endl<<"fin : Detruit le catalogue et ferme l'application"<<endl<<endl;
        cin>>saisie;
        if(strcmp(saisie,"ajout")==0) {
            int nbTraj;
            codeAjout resultat = FAIT;
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
        cout<<endl;
    }

    delete cat;
    cout<<"Passez une bonne journee !";
    return 0;
}//----Fin du Main

codeFichier lectureFichier(const string nomFichier, Catalogue * cat) {
    ifstream flux(nomFichier);
    string lecture;
    string depart, arrivee, transport;
    
    if(flux) { //True si ouverture valide


    } else {
         cout<<"Erreur : Fichier introuvable"<<endl;
         return ERR;
     }
}

codeFichier ecritureFichier(const string nomFichier, Catalogue * cat)
//Algorithme:
{
    ofstream flux(nomFichier);

    if(flux){  //On teste si tout est OK


    }else{
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
        return ERR;
    }

}//-----Fin de ecritureFichier
