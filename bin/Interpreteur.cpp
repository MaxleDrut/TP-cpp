/*************************************************************************
                           Interpreteur  -  description
                             -------------------
    début                : 22/01/2021
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

#include "Interpreteur.h"

codeInter Interpreteur::LireCommande(int argc, char ** argv) {
    //Algorithme : Interprete une commande renseignée sur analog et met à jour son
    //tableau de spécifications.

    //Un seul argument : Forcément une erreur car on ne renseigne pas de log !
    if(argc==1) {
        cerr<<errLog<<endl;
        return ERR;
    }
    string speci;
    string attribut;
    //Lecture des options
    for(int i=1;i<argc-1;i++) {
        speci = argv[i];
        if(speci == "-g") {
            //Graph :
            attribut = argv[i+1];
            //Vérifie que l'on a bien .log a la fin du nom du fichier
            if(attribut.find(".dot") != attribut.length()-4) {
                cerr<<errGraph<<endl;
                return ERR;
            }
            spe->ajoutSpeci(speci,attribut);
            i++;
        } else if(speci=="-t") {
            //Temps
            int j = 0;
            //On parcourt char par char jusqu'à trouver un non digit
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
            if(temps < 0 || temps >= 24) {
                cerr<<errTemps<<endl;
                return ERR;
            }
            spe->ajoutSpeci(speci,attribut);
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
            //Codes avec attributs sans vérification.
            attribut = argv[i+1];
            spe->ajoutSpeci(speci,attribut);
            i++;
        } else if(speci=="-e" || speci=="-err") {
            //Codes sans attribut. Juste indiquer s'il sont présents
            spe->ajoutSpeci(speci,"Present");
        } else {
            cerr<<errSpeci<<speci<<endl;
            return ERR;
        }
    }

    //Le dernier paramètre est le fichier log. Vérifions s'il est valide
    attribut = argv[argc-1];
    if(attribut.find(".log") != attribut.length()-4) {
        cerr<<errLog<<endl;
        return ERR;
    }
    spe->ajoutSpeci("log",attribut);
    return OK;
} //----- Fin de LireCommande

Specifications * Interpreteur::GetObjSpeci() const {
    return spe;
}

Interpreteur::Interpreteur() {
    //Constructeur vide
    #ifdef MAP
        cout << "Appel au constructeur de <Interpreteur>" << endl;
    #endif
    spe = new Specifications();
}

Interpreteur::~Interpreteur() {
    #ifdef MAP
        cout << "Appel au destructeur de <Interpreteur>" << endl;
    #endif
    delete spe;
}
