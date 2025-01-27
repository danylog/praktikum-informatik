#ifndef VERHALTEN_H
#define VERHALTEN_H

#include <string>
#include <iomanip>
class Weg;
class Fahrzeug;

// Abstract class to represent the behavior of a vehicle
class Verhalten {
public:
    // Constructor that stores a reference to the Weg
    Verhalten(Weg& weg) : p_rWeg(weg) {}

    virtual ~Verhalten() = default;

    // Abstract method for calculating the distance a vehicle can travel
    virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const = 0;

    // Abstract method for describing the behavior
    virtual std::string sBeschreibung() const = 0;

    Weg& getWeg() const { return p_rWeg; }

protected:
    Weg& p_rWeg;  // Reference to Weg to access the road's properties
};

#endif
