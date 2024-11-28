#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include <string>
extern double dGlobaleZeit;
class Fahrzeug {
public:
    Fahrzeug(); //default

    Fahrzeug(const std::string& name); // nur mit name

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

    virtual void vAusgeben(std::ostream& os);
    virtual void vSimulieren();
    virtual double dTanken( double dMenge = std::numeric_limits<double>::infinity());



    const std::string& sName() const { return p_sName; }						//GETTERS
    const int iID() const { return p_iID; }
    const double dMaxGeschwindigkeit() const { return p_dMaxGeschwindigkeit; }
    virtual double dGeschwindigkeit() {return p_dMaxGeschwindigkeit;}


    static void vKopf();

private:
    const int p_iID;
    static int p_iMaxID;

// //   const double p_dGesamtZeit;
protected:
    std::string p_sName;
    double p_dMaxGeschwindigkeit;
    double p_dGesamtStrecke = 0.0;
    double p_dGesamtZeit = 0.0;
    double p_dZeit = 0.0;

friend std::ostream& operator<<(std::ostream& os, Fahrzeug& f);


};





#endif
