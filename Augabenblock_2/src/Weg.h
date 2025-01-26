#ifndef WEG_H
#define WEG_H


#include <list>
#include <memory>
#include <iostream>
#include <string>
#include "Simulationsobjekt.h"
#include "Tempolimit.h"

class Fahrzeug;




class Weg : public Simulationsobjekt{
public:
	Weg();
	Weg(const std::string& name, double laenge, Tempolimit tempolimit = Tempolimit::Autobahn);
	virtual ~Weg();

	double getTempolimit() {return double(p_eTempolimit);}

	virtual void vAusgeben(std::ostream& os) const override;

	virtual void vSimulieren();

	static void vKopf(std::ostream& os);

	double getLength() const { return p_dLaenge; }

	void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug);

    friend std::ostream& operator<<(std::ostream& os, const Weg& weg);


protected:

private:
	const double p_dLaenge;
	std::list<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
	Tempolimit p_eTempolimit;

};

#endif
