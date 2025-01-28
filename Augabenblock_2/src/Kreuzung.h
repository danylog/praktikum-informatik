#ifndef KREUZUNG_H
#define KREUZUNG_H

#include "Simulationsobjekt.h"
#include "Weg.h"
#include <iostream>
#include <list>
#include <memory>

class Kreuzung : public Simulationsobjekt {
public:
    // Constructor with name and optional gas station volume
    Kreuzung(const std::string& name, double tankstelle = 0.0);

    // Destructor
    virtual ~Kreuzung() = default;

    // Static method to connect two intersections with roads
    static void vVerbinde(const std::string& hinweg,
                             const std::string& rueckweg,
                             double laenge,
                             std::shared_ptr<Kreuzung> kreuzung1,
                             std::shared_ptr<Kreuzung> kreuzung2,
                             Tempolimit tempolimit = Tempolimit::Autobahn);

        // Get outgoing roads as references to avoid ownership issues
        const std::list<std::shared_ptr<Weg>>& getWege() const { return p_pWege; }

    // Implementation of pure virtual function from Simulationsobjekt
    virtual void vSimulieren();

    // Method to tank vehicles
    double dTanken(double dMenge);



    std::string getName() const { return p_sName;}

    // Method to add an outgoing road
    void vAnnahmeWeg(std::shared_ptr<Weg> weg);

private:
    std::list<std::shared_ptr<Weg>> p_pWege;  // List of outgoing roads
    double p_dTankstelle;  // Gas station volume
};

#endif
