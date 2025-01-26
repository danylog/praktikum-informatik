#ifndef SIMULATIONSOBJEKT_H
#define SIMULATIONSOBJEKT_H

#include <string>
#include <ostream>


class Simulationsobjekt {
public:
    // Default constructor
    Simulationsobjekt();

    // Constructor with name
    Simulationsobjekt(const std::string& name);

    // Virtual destructor
    virtual ~Simulationsobjekt();

    // Comparison operator
    bool operator==(const Simulationsobjekt& other) const {
        return p_iID == other.p_iID;
    }

    // Virtual function to output object information
    virtual void vAusgeben(std::ostream& os) const;

    // Getters
    const std::string& sName() const { return p_sName; }
    int iID() const { return p_iID; }

private:
    const int p_iID;  // Unique ID for each object
    static int p_iMaxID;  // Tracks the maximum ID assigned

protected:
    std::string p_sName;  // Name of the object
    double p_dGesamtZeit = 0.0;  // Total simulation time
    double p_dZeit = 0.0;  // Local simulation time
};

#endif
