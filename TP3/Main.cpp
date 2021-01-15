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
//enum codeFichier {OK,ERR};

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void majuscule(char * texte);

int main()
//Algorithme:
//      L'uilisateur saisie une action à faire dans le terminal. En fonction
//      de la saisie, la méthode Main va utiliser les différentes méthodes
//      de pointeur de type Catalogue crée au début du code.
{
    string nomFichier;
    string typeASauver;
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
        cout<<"Menu principal :"<<endl<<"import : Importe les trajets d'un fichier .cat"<<endl<<"ajout : Creer un trajet"<<endl<<"rs : Recherche simple"<<endl<<"ra : Recherche avancee"<<endl<<"voir : Afficher le catalogue"<<endl<<"sauver : Sauvegarde le catalogue actuel dans un fichier .cat"<<endl<<"fin : Detruit le catalogue et ferme l'application"<<endl<<endl;
        cin.getline(saisie,100);
        if(strcmp(saisie,"ajout")==0) {
            int nbTraj;
            resultat = FAIT;
            cout<<"Combien de trajets ? (1 = Trajet simple | >1 = Trajet Compose)"<<endl;

            cin>>nbTraj;
            while( cin.fail() || nbTraj<1) {
                cout<< "Veuiller rentrer un nombre positif (>0)"<<endl;
                cin.clear();
                cin.ignore(100,'\n');
                cin>>nbTraj;
            }

            cin.clear(); //Nécessaire pour la lecture d'une ligne
            cin.ignore(100,'\n');

            if(nbTraj==1) { //Trajet simple
                cout<<"Depart du trajet ?"<<endl;
                cin.getline(depart,100);
                cout<<"Arrivee ?"<<endl;
                cin.getline(arrivee,100);
                cout<<"Transport ?"<<endl;
                cin.getline(transport,100);

                majuscule(depart);
                majuscule(arrivee);

                resultat = cat->AjoutCatalogue(new TrajetSimple(depart,arrivee,transport));
            } else { //Si il y a plusieurs trajet demandés, on crée une liste à laquelle on ajoute chque trajet rentrée par l'utilisateur. On crée ensuite notre TrajetCompo qu'on ajoute au Catalogue
                ListeTrajets * listeCompo = new ListeTrajets();
                cout<<"Depart du trajet ?"<<endl;
                cin.getline(depart,100);
                majuscule(depart);
                for(int i=1;i<=nbTraj;i++) {
                    cout<<"Arrivee du trajet "<<i<<" ?"<<endl;
                    cin.getline(arrivee,100);
                    majuscule(arrivee);
                    cout<<"Transport du trajet "<<i<<" ?"<<endl;
                    cin.getline(transport,100);

                    listeCompo->AddLast(new TrajetSimple(depart,arrivee,transport));
                    strcpy(depart,arrivee); //Le départ du trajet suivant est l'arrivée du précédent
                }
                resultat = cat->AjoutCatalogue(new TrajetCompo(listeCompo));
            }
            if(resultat == FAIT) {
                cout<<endl<<"Trajet ajoute !"<<endl;
            } else {
                cout<<endl<<"Le trajet existe deja !"<<endl;
            }
        }
        if(strcmp(saisie,"rs")==0){
            cout<<"Depart du trajet recherche ?"<<endl;
            cin.getline(depart,100);
            cout<<"Arrivee du trajet ?"<<endl;
            cin.getline(arrivee,100);

            majuscule(depart);
            majuscule(arrivee);
            cat->RechercheSimple(depart,arrivee);
        }
        if(strcmp(saisie,"ra")==0){
            cout<<"Depart du trajet recherche ?"<<endl;
            cin.getline(depart,100);
            cout<<"Arrivee du trajet ?"<<endl;
            cin.getline(arrivee,100);

            majuscule(depart);
            majuscule(arrivee);
            cat->RechercheAvancee(depart,arrivee);
        }
        if(strcmp(saisie,"voir")==0){
            cat->AfficheCatalogue();
        }
        if(strcmp(saisie,"import")==0) {
            cout<<"Nom du fichier source ? (sans l'extension .cat)"<<endl;
            getline(cin,nomFichier); //Oui la syntaxe est différente pour les strings. Allez savoir !
            retourFichier = cat->ImportFichier(nomFichier);
            if(retourFichier==OK) {
                cout<<"Import du fichier reussi !"<<endl;
            } else {
                cout<<"Erreur : le fichier n'a pas ete trouve / n'a pas pu etre ouvert"<<endl;
            }
        }
        if(strcmp(saisie,"sauver")==0){
            cout<<"Nom du fichier pour la sauvegarde ? (sans l'extension .cat)"<<endl;
            getline(cin,nomFichier);
            cout<<"Quels types de trajets enregistrer ? (all = tous, ts = trajets simples, tc = trajets composes)"<<endl;
            getline(cin,typeASauver);
            while(typeASauver!="all" && typeASauver!="ts" && typeASauver!="tc"){
                cout<<"Type invalide (all = tous, ts = trajets simples, tc = trajets composes)"<<endl;
                getline(cin,typeASauver);
            }
            cout<<"Enregistrer selon ville de depart : entrez son nom. Sinon, entrez all"<<endl;
            cin>>depart;
            cout<<"Enregistrer selon ville d'arrivee : entrez son nom. Sinon, entrez all"<<endl;
            cin>>arrivee;

            retourFichier = cat->EcritureFichier(nomFichier,typeASauver,depart,arrivee);
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

void majuscule(char * texte)
//Algorithme:
//      Modifie la chaîne de caractère pour la mettre aux normes
//      du catalogue : on veut une majuscule en début de chaque mot et des minuscules ailleurs
{
    int i=0;

    while(i<100 && texte[i] != '\0') {
        /*Cas 1 : on a une minuscule en début d'un mot
        On passe alors cette lettre en majuscule (code ascii -32)*/
        if((i==0 || texte[i-1]==' ') && texte[i]>=97 && texte[i] <= 122) {
            texte[i] = texte[i] - 32;
        /*Cas 2 : majuscule en milieu d'un mot
        On passe alors la lettre en minuscule*/
        } else if(!(i==0 || texte[i-1]==' ') && texte[i]>=65 && texte[i] <= 90) {
            texte[i] = texte[i] + 32;
        } else {
            texte[i] = texte[i];
        }
        i++;
    }

}//-----Fin de majuscule
