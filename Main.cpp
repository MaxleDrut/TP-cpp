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

    Maillon m2(&trajetDeux);

    if(m2.GetNext() == nullptr) {
            cout<<m2.GetContenu()->ToString();
    }
    //cout<<m1.GetContenu()->ToString();
    Maillon m1(&trajetUn,&m2);
}
