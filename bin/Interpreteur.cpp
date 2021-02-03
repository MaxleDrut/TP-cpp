/*************************************************************************
                           Interpreteur  -  description
                             -------------------
    début                : 22/01/2021
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

#include "Interpreteur.h"

codeInter Interpreteur::LireCommande(int argc, char ** argv) {
//Algorithme :
//      Interprete une commande renseignée sur analog et crée son tableau de spécifications.
//      Renvoie un code qui indique si la lecture a été valide ou non.

    //On reçoit un seul argument : Forcément une erreur car on ne renseigne pas de log !
    if(argc==1) {
        cerr<<errLog<<endl;
        return ERR;
    }
    string speci; //Contiendra la specification renseignée (-os, -e...)
    string attribut; //Contiendra l'attribut lié s'il existe
    //Lecture des options
    for(int i=1;i<argc-1;i++) {
        speci = argv[i];
        if(speci == "-g") {
            //Création d'un graph :
            attribut = argv[i+1];
            //Vérifie que l'on renseigne .log à la fin du nom du fichier
            if(attribut.find(".dot") != attribut.length()-4) {
                cerr<<errGraph<<endl;
                return ERR;
            }
            spe->ajoutSpeci(speci,attribut);
            i++;//<-- On lit l'attribut et la specification, il faut donc avancer de 2 cases dans argv[] !!
        } else if(speci=="-t") {
            //Lecture d'un temps
            int j = 0;

            //On parcourt la string char par char jusqu'à trouver un non digit
            while(isdigit(argv[i+1][j]) == true) {
                j++;
            }
            //S'il s'agit d'un symbole de fin de chaîne, c'est que le string est un nombre. Sinon --> Erreur
            if(argv[i+1][j] != '\0') {
                cerr<<errTemps<<endl;
                return ERR;
            }
            attribut = argv[i+1];
            int temps = stoi(attribut);
            //L'heure doit être comprise entre 0 et 23.
            if(temps < 0 || temps >= 24) {
                cerr<<errTemps<<endl;
                return ERR;
            }
            if(temps<10) {
                //Rajoute le 0 devant l'heure si elle est inférieure à 10
                //Pour correspondre au format des logs
                spe->ajoutSpeci(speci,"0"+attribut);
            } else {
                spe->ajoutSpeci(speci,attribut);
            }
            i++;
        } else if(speci=="-p") {
            //Poids mini. Vérifier s'il s'agit d'un nombre positif
            int j = 0;
            while(isdigit(argv[i+1][j]) == true) {
                j++;
            }
            if(argv[i+1][j] != '\0') {
                cerr<<errPoids<<endl;
                return ERR;
            }
            attribut = argv[i+1];
            int poids = stoi(attribut);
            if(poids<=0) {
                cerr<<errPoids<<endl;
                return ERR;
            }
            spe->ajoutSpeci(speci,attribut);
            i++;
        } else if(speci == "-ip" || speci == "-os") {
            //Regroupe les codes attendant des attributs sans vérification complémentaire.
            attribut = argv[i+1];
            spe->ajoutSpeci(speci,attribut);
            i++;
        } else if(speci=="-e" || speci=="-err") {
            //Codes sans attribut. Juste indiquer s'il sont présents
            spe->ajoutSpeci(speci,"Present");
        } else {
            //La spécification n'est pas reconnue
            cerr<<errSpeci<<speci<<endl;
            return ERR;
        }
    }

    //Le dernier paramètre sera le fichier log. Vérifions s'il est valide
    attribut = argv[argc-1];
    if(attribut.find(".log") != attribut.length()-4) {
        cerr<<errLog<<endl;
        return ERR;
    }
    spe->ajoutSpeci("log",attribut);
    return OK;
}//----------- Fin de LireCommande

Specifications * Interpreteur::GetObjSpeci() const {
//Algorithme : Aucun
    return spe;
}//---------- Fin de GetObjSpeci

Interpreteur::Interpreteur() {
    //Constructeur par défaut, crée la structure de spécification
    #ifdef MAP
        cout << "Appel au constructeur de <Interpreteur>" << endl;
    #endif
    spe = new Specifications();
}//---------- Fin du constructeur

Interpreteur::~Interpreteur() {
    //Destructeur par défaut
    #ifdef MAP
        cout << "Appel au destructeur de <Interpreteur>" << endl;
    #endif
    delete spe;
}//---------- Fin du destructeur
