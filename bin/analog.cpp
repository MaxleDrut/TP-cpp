/*************************************************************************
                           Analog - Classe principale
                             -------------------
    début                : 22/01/21
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

#include <iostream>
using namespace std;

#include "Interpreteur.h"
#include "Analyseur.h"

int main(int argc, char ** argv) {
//Algorithme :
//      lis la commande renseignée par l'utilisateur. Si elle est correcte,
//      exécute la lecture et le traitement du fichier log renseigné.
    Interpreteur inter;
    if(inter.LireCommande(argc,argv) == ERR) {
        return 1;
    } else {
        Analyseur ana;
        if(ana.ChargementLogs(inter.GetObjSpeci()) == PASBON) {
            return 2;
        } else {
            ana.AfficherTop10();
        }
    }
    return 0;
}
