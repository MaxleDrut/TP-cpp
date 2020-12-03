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
    TrajetSimple(const TrajetSimple & unTrajet);
    virtual ~TrajetSimple();

private:
    char* transport;
};

#endif
