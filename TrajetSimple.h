/*La classe TrajetSimple hérite de la classe Trajet.
En plus d'une ville d'arrivée et d'une ville de départ,
on ajoute au trajet un moyen de transport entre les deux villes.*/

#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H

#include "Trajet.h"

class TrajetSimple : public Trajet {

public:

    void Afficher() const;
    Trajet * Dupliquer();
    char* GetDepart() const;
    char* GetArrivee() const;
    char* GetTransport() const;

    TrajetSimple(const char * depart, const char * arrivee, const char * transport);
    TrajetSimple();
    virtual ~TrajetSimple();

private:
    char* transport;
};

#endif
