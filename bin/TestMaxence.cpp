#include <string>
#include <iostream>
using namespace std;

#include "Interpreteur.h"
#include "Analyseur.h"
#include "Grapheur.h"

int main(int argc, char ** argv) {

    Interpreteur * inter = new Interpreteur();
    inter->LireCommande(argc,argv);
    Analyseur * analyseur = new Analyseur();
    analyseur->ChargementLogs(inter->GetObjSpeci());
    delete inter;
    delete analyseur;

    return 0;
}
