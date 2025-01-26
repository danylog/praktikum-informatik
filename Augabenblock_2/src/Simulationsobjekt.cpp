#include "Simulationsobjekt.h"
#include <string>
// Static member initialization
int Simulationsobjekt::p_iMaxID = 0;

// Default constructor
Simulationsobjekt::Simulationsobjekt()
    : p_iID(++p_iMaxID), p_sName("Default") {}

// Constructor with name
Simulationsobjekt::Simulationsobjekt(const std::string& name)
    : p_iID(++p_iMaxID), p_sName(name) {}

// Destructor
Simulationsobjekt::~Simulationsobjekt() {}

// Output function
void Simulationsobjekt::vAusgeben(std::ostream& os) const{
}
