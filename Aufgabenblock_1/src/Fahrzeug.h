#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include <string>

class Fahrzeug {
public:
    Fahrzeug();
    Fahrzeug(const std::string& name);
    Fahrzeug(const std::string& name, const double maxGeschwindigkeit);
    virtual ~Fahrzeug();

   virtual void vAusgeben();

protected:
    std::string p_sName;
    const double p_dMaxGeschwindigkeit;
   const double p_dGesamtStrecke =0.0;

private:

    const int p_iID;
    static int p_iMaxID;

// //   const double p_dGesamtZeit;

};





#endif
