
#if ! defined ( MAILLON_H )
#define MAILLON_H

#include "Trajet.h"

class Maillon
{

public:
    Maillon (Trajet * t, Maillon * suiv = nullptr); //Si ça n'est pas null, on s'en sert pour ajouter en milieu de chaîne
    Maillon ();
    Maillon(const Maillon & unMaillon);
    virtual ~Maillon();

    Trajet * GetContenu();
    Maillon * GetNext();

    Trajet * GetContenuConst() const;
    Maillon * GetNextConst() const;
    void SetNext(Maillon * m);


private:
    Trajet * contenu;
    Maillon * next;
};

#endif
