
#if ! defined ( TRAJET_H )
#define LISTETRAJETS_H

enum codeAdd {DONE,OFB};
#include "Trajet.h"

class ListeTrajets
{

public:
    ListeTrajets(Trajet * t, ListeTrajets * l = nullptr); //Si ça n'est pas null, on s'en sert pour ajouter en milieu de chaîne
    ListeTrajets ();
    virtual ~ListeTrajets();

    void AddLast(Trajet * t);
    codeAdd AddPos(Trajet * t, int pos);

    int GetLength() const;
    ListeTrajets * GetNext();
    Trajet * GetContent();

    void SetNext(ListeTrajets *);

    char * ToString() const;

private:
    Trajet * current;
    ListeTrajets * next;
};

#endif // ENSEMBLE_H
