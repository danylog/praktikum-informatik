#include "Weg.h"
#include "Fahrzeug.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "Fahrausnahme.h"
#include "Losfahren.h"
#include "Streckenende.h"
#include <vector>
#include "Kreuzung.h"
#include <random>
//std::string& defaultname = "DefaultWeg";


Weg::Weg() : Simulationsobjekt("weg"), p_dLaenge(100), p_eTempolimit(Tempolimit::Autobahn){};

Weg::Weg(const std::string& name, double laenge, Tempolimit tempolimit)
    : Simulationsobjekt(name),
      p_dLaenge(laenge),
      p_eTempolimit(tempolimit) {}


Weg::~Weg(){}

// In Weg.cpp


void Weg::vSimulieren() {
    p_pFahrzeuge.vAktualisieren();

    // Make a copy of the vehicles to process
    std::vector<Fahrzeug*> fahrzeuge_to_process;
    for (const auto& fahrzeug : p_pFahrzeuge) {
        fahrzeuge_to_process.push_back(fahrzeug.get());
    }

    // Process each vehicle
    for (Fahrzeug* fahrzeug : fahrzeuge_to_process) {
        try {
            // Find the corresponding unique_ptr in the list
            auto it = std::find_if(p_pFahrzeuge.begin(), p_pFahrzeuge.end(),
                [fahrzeug](const std::unique_ptr<Fahrzeug>& ptr) {
                    return ptr.get() == fahrzeug;
                });

            if (it != p_pFahrzeuge.end()) {
                (*it)->vSimulieren();
                (*it)->vZeichnen(*this);
            }
        }
        catch (const Streckenende& ausnahme) {
            ausnahme.vBearbeiten();
            // Vehicle will be removed in vAktualisieren()
        }
        catch (const Losfahren& ausnahme) {
            ausnahme.vBearbeiten();
            // Vehicle's behavior is updated, but stays in the list
        }
    }

    p_pFahrzeuge.vAktualisieren();
}




void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug) {
    fahrzeug->vNeueStrecke(*this);  // Set behavior first
    p_pFahrzeuge.push_back(std::move(fahrzeug));
    p_pFahrzeuge.vAktualisieren();
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double startzeit) {
    fahrzeug->vNeueStrecke(*this, startzeit);  // Set parking behavior first
    p_pFahrzeuge.push_front(std::move(fahrzeug));
    p_pFahrzeuge.vAktualisieren();
}
std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fahrzeug) {
    std::unique_ptr<Fahrzeug> result = nullptr;

    for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
        if (it->get() == &fahrzeug) {
            // Transfer ownership to result
            result = std::move(*it);
            // Mark for removal from list
            p_pFahrzeuge.erase(it);
            break;
        }
    }

    // Process the removal
    p_pFahrzeuge.vAktualisieren();
    return result;
}

void Weg::vAusgeben(std::ostream& out) const {
    Simulationsobjekt::vAusgeben(out);
    out << std::setw(20) << p_sName
        << std::setw(20) << p_dLaenge << std::endl;

    // List all vehicles on this road
    for (const auto& fahrzeug : p_pFahrzeuge) {
        out << *fahrzeug << std::endl;
    }
}

void Weg::vKopf(std::ostream& os) {
    os << std::setw(5) << "ID"
       << " | " << std::setw(10) << "Name"
       << " | " << std::setw(10) << "Laenge"
       << " | " << "Fahrzeuge" << "\n"
       << std::string(50, '-') << "\n"; // @suppress("Symbol is not resolved")
}






Weg* Weg::getRandomNextWeg() const {
           // Lock the weak_ptr to get a shared_ptr
           if (auto zielKreuzung = p_pZielKreuzung.lock()) {
               if (zielKreuzung->getWege().empty()) {
                   return nullptr;
               }

               static std::random_device rd;
               static std::mt19937 gen(rd());

               const auto& wege = zielKreuzung->getWege();
               std::uniform_int_distribution<> dis(0, wege.size() - 1);

               auto it = wege.begin();
               std::advance(it, dis(gen));

               return it->get();
           }
           return nullptr;
       }


std::ostream& operator<<(std::ostream& os, const Weg& weg) {
    weg.vAusgeben(os); // Call the vAusgeben function
    return os; // Return the stream reference
}

