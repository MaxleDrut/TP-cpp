#if ! defined ( TRAJETCOMPO_H )
#define TRAJETCOMPO_H

#include "Trajet.h"
#include "ListeTrajets.h"
#include "Maillon.h"

class TrajetCompo : public Trajet {

public:

    void Afficher() const;
    Trajet * Dupliquer();
    char* GetDepart() const;
    char* GetArrivee() const;
    ListeTrajets * GetListe();

    TrajetCompo(ListeTrajets * trajets);
    TrajetCompo();
    virtual ~TrajetCompo();

private:
    ListeTrajets * trajets;
};

#endif
