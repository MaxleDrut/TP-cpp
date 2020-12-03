#include "TrajetSimple.h"
#include "ListeTrajets.h"
#include "Maillon.h"
#include "TrajetCompo.h"
#include "Catalogue.h"

#include <iostream>
#include <cstring>
using namespace std;

// ajout pour ajouter (specifier les étapes après)
//rs recherche simple
//ra avancée
//voir
//fin

int main() {
    char saisie [100];
    char depart[100];
    char arrivee[100];
    char transport[100];
    saisie[0] = '\0';
    Catalogue * cat = new Catalogue();
    cout<<"Easy Travel : la solution intelligente pour tous vos déplacements"<<endl;
    cout<<"(dans la limite des trajets précédemment disponibles)"<<endl<<endl;
    cout<<"Lexique :"<<endl<<"ajout : Creer un trajet"<<endl<<"rs : Recherche simple"<<endl<<"ra : Recherche avancee"<<endl<<"voir : Afficher le catalogue"<<endl<<"fin : Detruit le catalogue et ferme l'application"<<endl<<endl;

    cin>>saisie;
    while(strcmp(saisie,"fin")!=0) {
        if(strcmp(saisie,"ajout")==0) {
            int nbTraj;
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
                cat->AjoutCatalogue(new TrajetSimple(depart,arrivee,transport));
            } else {
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
                cat->AjoutCatalogue(new TrajetCompo(listeCompo));
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
        cin>>saisie;
    }

    delete cat;
    cout<<"Passez une bonne journee !"<<endl;
    return 0;
}
