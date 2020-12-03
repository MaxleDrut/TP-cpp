#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

#include "ListeTrajets.h"
#include "Trajet.h"
#include "Maillon.h"
#include "TrajetSimple.h" //Nécessaire pour tester le type dans Ajout

enum codeAjout{FAIT,DOUBLON};
enum codeRecherche{TROUVE,PAS_TROUVE};

class Catalogue{

public:
    Catalogue();
    virtual ~Catalogue();

    codeAjout AjoutCatalogue(Trajet * trajet);
    codeRecherche RechercheSimple(const char * depart, const char * arrivee) const;
    codeRecherche RechercheAvancee(const char * depart, const char * arrivee) const;
    void AfficheCatalogue() const;

private:
    int plusPetitString(const char * a,const char * b) const;
    int recherche(const char * da,const  char * av, int nbT, ListeTrajets * trajetRech, ListeTrajets * listeAfficher) const;
    bool verif(const char * da,const  char * av, ListeTrajets * liste )const ;
    ListeTrajets * liste;

};

#endif
