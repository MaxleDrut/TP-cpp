/*************************************************************************
                           Ensemble  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Ensemble> (fichier Ensemble.h) ----------------
#if ! defined ( ENSEMBLE_H )
#define ENSEMBLE_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes
const unsigned int CARD_MAX = 5;

enum crduEstInclus {NON_INCLUSION,INCLUSION_LARGE,INCLUSION_STRICTE};
enum crduAjouter {DEJA_PRESENT,PLEIN,AJOUTE};

//------------------------------------------------------------------------
// Rôle de la classe <Ensemble>
//
//
//------------------------------------------------------------------------

class Ensemble 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    void Afficher (void);
    
    Ensemble ( unsigned int cardMax = CARD_MAX ); // TU01
	Ensemble ( int t [ ], unsigned int nbElements ); // TU02
	bool EstEgal ( const Ensemble & unEnsemble ) const ; // TU03
	crduEstInclus EstInclus ( const Ensemble & unEnsemble ) const; // TU04
	crduAjouter Ajouter (int aAjouter); // TU05
	unsigned int Ajuster ( int delta ); // TU06
	bool Retirer ( int element ); // TU07
	unsigned int Retirer ( const Ensemble & unEnsemble ); // TU08
	int Reunir ( const Ensemble & unEnsemble ); // TU09
	unsigned int Intersection ( const Ensemble & unEnsemble ); // TU10 

//------------------------------------------------- Surcharge d'opérateurs
    Ensemble & operator = ( const Ensemble & unEnsemble );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Ensemble ( const Ensemble & unEnsemble );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Ensemble ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Ensemble ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
	int dansEnsemble(int val) const;
//------------------------------------------------------------------ PRIVE

protected:
// Méthodes protégées
	int *tab;
	unsigned int tailleMax;
	unsigned int cardActu;
	
private:
	void triEnsemble();

};

//-------------------------------- Autres définitions dépendantes de <Ensemble>

#endif // ENSEMBLE_H

