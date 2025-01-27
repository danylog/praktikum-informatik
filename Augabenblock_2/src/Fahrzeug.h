#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include <string>

extern double dGlobaleZeit;


#include "Simulationsobjekt.h"

//#include "Fahren.h"
//#include "Parken.h"

class Weg;
class Verhalten;


class Fahrzeug : public Simulationsobjekt{
public:
    Fahrzeug(const std::string& name, const double maxGeschwindigkeit); //name und max geschw

    Fahrzeug(const Fahrzeug&) = delete; // copy-construktor verboten

    virtual ~Fahrzeug();

    Fahrzeug& operator=(const Fahrzeug& other) { //gleichungsoperator
        if (this != &other) {
            p_sName = other.p_sName; // name kopieren
            p_dMaxGeschwindigkeit = other.p_dMaxGeschwindigkeit; // geschwindigkeit kopieren
            // die ID wird nicht kopiert, da sie unique sein muss
        }
        return *this;
    }

    void vAusgeben(std::ostream& os) const override;
    virtual void vSimulieren();
    virtual double dTanken( double dMenge = std::numeric_limits<double>::infinity());




    const double dMaxGeschwindigkeit() const { return p_dMaxGeschwindigkeit; }
    virtual double dGeschwindigkeit() const {return p_dMaxGeschwindigkeit;}
    virtual double getAbschnittStrecke() const { return p_dAbschnittStrecke; }
    virtual double getGesamtStrecke() const {return p_dGesamtStrecke;}
    virtual void vZeichnen(const Weg& weg) const = 0;


    std::string getName() const { return p_sName;}
    const Verhalten* getVerhalten() const {
        return p_pVerhalten.get();
    }


    static void vKopf();


    void vNeueStrecke(Weg& weg);

    void vNeueStrecke(Weg& weg, double startzeit);


// //   const double p_dGesamtZeit;
protected:

    double p_dMaxGeschwindigkeit;
    double p_dGesamtStrecke;
    double p_dAbschnittStrecke;
    std::unique_ptr<Verhalten> p_pVerhalten;
private:


friend std::ostream& operator<<(std::ostream& os, Fahrzeug& f);


};





#endif
