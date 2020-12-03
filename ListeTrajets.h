
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
    void AddFirst(Trajet * t);
    codeAdd AddPos(Trajet * t, int pos);
    Maillon * Supprimer();

    int GetLength();
    Maillon * GetLast();
    Maillon * GetPos(int pos);
    void Afficher() const;
private:
    Maillon * first;
    Maillon * last;
};

#endif
