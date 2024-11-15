#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include <string>

class Fahrzeug {
public:
    Fahrzeug();
    Fahrzeug(const std::string& name);
    Fahrzeug(const std::string& name, const double maxGeschwindigkeit);
    virtual ~Fahrzeug();

    void vAusgeben();
    void vKopf();


private:
    std::string p_sName;
    const int p_iID;
    static int p_iMaxID;
    const double p_dMaxGeschwindigkeit;
   const double p_dGesamtStrecke =0.0;
// //   const double p_dGesamtZeit;

};

#endif
