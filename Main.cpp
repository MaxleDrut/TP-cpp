#include "TrajetSimple.h"
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char texte1[] = "Lyon";
    char texte2[] = "Paris";
    TrajetSimple trajetUn(texte1,texte2,"Voiture");
    TrajetSimple trajetDeux;

    //TrajetSimple trajetDeux();
    cout<<trajetUn.ToString()<<endl<<trajetDeux.ToString()<<endl<<trajetUn.getDepart();

}
