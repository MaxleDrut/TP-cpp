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
codeFichier ecritureFichier(const string nomFichier, const string typeAttendu, const char * villeDepart, const char * villeArrivee, Catalogue * cat);
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
            retourFichier = importFichier(nomFichier,cat);
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

            retourFichier = ecritureFichier(nomFichier,typeASauver,depart,arrivee,cat);
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

codeFichier ecritureFichier(const string nomFichier, const string typeAttendu, const char * villeDepart, const char * villeArrivee, Catalogue * cat)
//Algorithme:
//      Si le flux s'ouvre bien, on parcours le catalogue et on écrit
//      dans nomFichier le contenu de chaque Trajet du catalogue en
//      précisant si c'est un TrajetSimple ou un TrajetCompo
//      Types attendus : ALL/TS/TC
{
    ofstream flux(nomFichier  + ".cat");
    string str;
    if(flux){  //On teste si tout est OK
        const Maillon * actuel = cat->GetListe()->GetPos(0);
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
