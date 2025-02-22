#ifndef WEG_H
#define WEG_H


#include <list>
#include <memory>
#include <iostream>
#include <string>
#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"
#include <random>



class Fahrzeug;
class Kreuzung;



class Weg : public Simulationsobjekt{
public:
	Weg();
	Weg(const std::string& name, double laenge, Tempolimit tempolimit = Tempolimit::Autobahn);
	virtual ~Weg();

    double getTempolimit() const {
        return ::getTempolimit(p_eTempolimit);  // Use the global getTempolimit function
    }

	virtual void vAusgeben(std::ostream& os) const override;

	virtual void vSimulieren();

	static void vKopf(std::ostream& os);

	double getLength() const { return p_dLaenge; }

	void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug);
	    void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double startzeit);
	    std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fahrzeug);



    std::string getName() const { return p_sName;}

    friend std::ostream& operator<<(std::ostream& os, const Weg& weg);
    // Add these new members:
    Weg* getRandomNextWeg() const;

       // Add getter and setter for ZielKreuzung
       void setZielKreuzung(std::shared_ptr<Kreuzung> kreuzung) {
           p_pZielKreuzung = kreuzung;
       }

       std::shared_ptr<Kreuzung> getZielKreuzung() const {
           return p_pZielKreuzung.lock();
       }


protected:

private:
	const double p_dLaenge;
    vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
	Tempolimit p_eTempolimit;
	  std::weak_ptr<Kreuzung> p_pZielKreuzung;

};

#endif
