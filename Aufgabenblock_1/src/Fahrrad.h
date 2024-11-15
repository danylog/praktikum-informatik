#include "Fahrzeug.h"

#ifndef FAHRRAD_H
#define FAHRRAD_H
class Fahrrad : public Fahrzeug{


public:
	Fahrrad(const std::string& name, const double maxGeschwindigkeit): Fahrzeug(name, maxGeschwindigkeit){};
	virtual void vAusgeben();

};

#endif
