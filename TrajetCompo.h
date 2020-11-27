#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETCOMPO_H

#include "Trajet.h"

class TrajetCompo : public Trajet {

public:

    char* ToString() const;
    char* getDepart() const;
    char* getArrivee() const;


    TrajetCompo(const char * depart, const char * arrivee, const char * transport);
    TrajetCompo();
    virtual ~TrajetCompo();

private:

};

#endif
