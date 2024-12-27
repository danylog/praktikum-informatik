#ifndef SIMULATIONSOBJEKT_H
#define SIMULATIONSOBJEKT_H

#include <string>

class Simulationsobjekt{
public:
	Simulationsobjekt();
	Simulationsobjekt(const std::string& name); // nur mit name
	virtual ~Simulationsobjekt();

	bool operator==(const Simulationsobjekt& other) const {
	    return p_iID == other.p_iID;
	}

	virtual void vAusgeben(std::ostream& os) const;

    const std::string& sName() const { return p_sName; }						//GETTERS
    const int iID() const { return p_iID; }

private:
    const int p_iID;
    static int p_iMaxID;

protected:
    std::string p_sName;
    double p_dGesamtZeit = 0.0;
    double p_dZeit = 0.0;

};

#endif
