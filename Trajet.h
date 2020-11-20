
#if ! defined ( TRAJET_H )
#define TRAJET_H


class Trajet
{

public:

    virtual char* toString();
    virtual char* getDepart();
    virtual char* getArrivee();

protected:
    char * villeDepart;
    char * villeArrivee;
};

#endif // ENSEMBLE_H
