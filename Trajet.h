/*La classe Trajet représente un trajet qu'il soit simple ou composé,
un trajet comporte une ville de départ et une ville d'arrivée.*/

#if ! defined ( TRAJET_H )
#define TRAJET_H


class Trajet
{

public:

    virtual void Afficher() const = 0;
    virtual char* GetDepart() const = 0;
    virtual char* GetArrivee() const = 0;
    virtual Trajet * Dupliquer() = 0;
    virtual ~Trajet(){};

protected:
    char * villeDepart;
    char * villeArrivee;
};

#endif // ENSEMBLE_H
