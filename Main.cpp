#include "TrajetSimple.h"
#include "ListeTrajets.h"
#include "Maillon.h"
#include "TrajetCompo.h"
#include "Catalogue.h"

#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char texte1[] = "Lyon";
    char texte2[] = "Paris";
    TrajetSimple * trajetUn = new TrajetSimple(texte1,texte2,"Voiture");
    TrajetSimple * trajetDeux = new TrajetSimple("Redon","Bourg","Kayak");

    ListeTrajets * listeCompo = new ListeTrajets();
    listeCompo->AddLast(new TrajetSimple("Paris","Dijon","Voiture"));
    listeCompo->AddLast(new TrajetSimple("Dijon","Geneve","Ski"));
    listeCompo->AddLast(new TrajetSimple("Geneve","Lyon","Avion qui pollue"));
    TrajetCompo * trajetComplet = new TrajetCompo(listeCompo);

    Catalogue * cat = new Catalogue();
    cat->AjoutCatalogue(trajetDeux);
    cat->AjoutCatalogue(trajetUn);
    cat->AjoutCatalogue(trajetComplet);
    cat->AjoutCatalogue(new TrajetSimple("Redon","Albuquerque","Bateau"));
    cat->AjoutCatalogue(new TrajetSimple("Redon","Bourg","Velo"));
    cat->AfficheCatalogue();

    cat->RechercheSimple("Lyon","Paris");
    delete cat;
}
