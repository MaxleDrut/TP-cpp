#include "TrajetSimple.h"
#include "ListeTrajets.h"
#include "Maillon.h"

#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char texte1[] = "Lyon";
    char texte2[] = "Paris";
    TrajetSimple * trajetUn = new TrajetSimple(texte1,texte2,"Voiture");
    TrajetSimple * trajetDeux = new TrajetSimple("Redon","Bourg","Kayak");

    ListeTrajets liste;
    liste.AddLast(trajetUn);
    liste.AddLast(trajetDeux);


    TrajetSimple * cc = new TrajetSimple("A","B","V");
    liste.AddPos(cc,0);

    liste.AddPos(new TrajetSimple("Mcdo","Burger King","Trotinette"),1);

    char * texte = liste.ToString();
    cout<<texte;
    delete[] texte;
}
