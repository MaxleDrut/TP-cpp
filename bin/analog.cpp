#include <iostream>
using namespace std;

#include "Interpreteur.h"
#include "Analyseur.h"

int main(int argc, char ** argv) {

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
