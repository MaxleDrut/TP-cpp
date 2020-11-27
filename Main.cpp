#include "TrajetSimple.h"
#include "ListeTrajets.h"
#include "Maillon.h"

#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char texte1[] = "Lyon";
    char texte2[] = "Paris";
    TrajetSimple trajetUn(texte1,texte2,"Voiture");
    TrajetSimple trajetDeux("Redon","Bourg","Kayak");

    ListeTrajets liste;
    liste.AddLast(&trajetUn);
    liste.AddLast(&trajetDeux);

    //liste.GetLast();
    cout<<liste.GetLast()->GetContenu()->ToString();
}
