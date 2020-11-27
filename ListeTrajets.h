
#if ! defined ( LISTETRAJETS_H )
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

    int GetLength();
    ListeTrajets * GetNext();
    Trajet * GetContent();

    void SetNext(ListeTrajets * l);

    char * ToString();

private:
    Trajet * current;
    ListeTrajets * next;
};

#endif // ENSEMBLE_H
