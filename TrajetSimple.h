
#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H


class TrajetSimple : public Trajet {

public:

    char* toString() const;
    char* getDepart() const;
    char* getArrivee() const;
    char* getTransport() const;

    TrajetSimple(const char * depart, const char * arrivee, const char * transport);
    TrajetSimple();
    virtual ~TrajetSimple();

private:
    char* transport;
};

#endif
