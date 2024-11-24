#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include <string>
extern double dGlobaleZeit;
class Fahrzeug {
public:
    Fahrzeug();
    Fahrzeug(const std::string& name);
    Fahrzeug(const std::string& name, const double maxGeschwindigkeit);
    virtual ~Fahrzeug();

   virtual void vAusgeben();
   virtual void vSimulieren();
   virtual double dSpeed();
   virtual double dTanken( double dMenge = std::numeric_limits<double>::infinity());
   const std::string& sName() const { return p_sName; }

private:
    const int p_iID;
    static int p_iMaxID;

// //   const double p_dGesamtZeit;
protected:
    std::string p_sName;
    const double p_dMaxGeschwindigkeit;
    double p_dGesamtStrecke = 0.0;
    double p_dGesamtZeit = 0.0;
    double p_dZeit = 0.0;


};





#endif
