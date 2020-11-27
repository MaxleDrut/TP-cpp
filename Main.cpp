#include "TrajetSimple.h"
#include "ListeTrajets.h"

#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char texte1[] = "Lyon";
    char texte2[] = "Paris";
    TrajetSimple trajetUn(texte1,texte2,"Voiture");

    ListeTrajets liste (&trajetUn);
    ListeTrajets autreListe;

    cout<<liste.ToString();

}
