
#if ! defined ( TRAJET_H )
#define TRAJET_H


class Trajet
{

public:

    virtual void Afficher() const = 0;
    virtual char* GetDepart() const = 0;
    virtual char* GetArrivee() const = 0;
    virtual ~Trajet() {};

protected:
    char * villeDepart;
    char * villeArrivee;
};

#endif // ENSEMBLE_H
