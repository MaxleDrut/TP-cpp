
#if ! defined ( LISTETRAJETS_H )
#define LISTETRAJETS_H

enum codeAdd {DONE,OFB};
#include "Trajet.h"
#include "Maillon.h"

class ListeTrajets
{

public:
    ListeTrajets ();
    virtual ~ListeTrajets();

    void AddLast(Trajet * t);
    codeAdd AddPos(Trajet * t, int pos);

    int GetLength();
    Maillon * GetLast();
    Maillon * GetPos(int pos);
    char * ToString();

private:
    Maillon * first;
    Maillon * last;
};

#endif
