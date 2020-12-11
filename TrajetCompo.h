/*La classe TrajetCompo hérite de la classe Trajet.
La classe stocke une liste de trajets (ici uniquement des trajets simples)
qui représente les différentes étapes d'un trajet composé.
On retient en + la ville de départ de la première étape et la ville d'arrivée
de la dernière étape ! */

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
