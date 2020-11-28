
#if ! defined ( TRAJET_H )
#define TRAJET_H


class Trajet
{

public:

    virtual char* ToString() = 0;
    virtual char* getDepart() const = 0;
    virtual char* getArrivee() const = 0;
    virtual ~Trajet() {};

protected:
    char * villeDepart;
    char * villeArrivee;
};

#endif // ENSEMBLE_H
