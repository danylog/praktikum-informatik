#include "Weg.h"
#include "Fahrzeug.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "Fahrausnahme.h"
#include "Losfahren.h"
#include "Streckenende.h"
//std::string& defaultname = "DefaultWeg";


Weg::Weg() : Simulationsobjekt("weg"), p_dLaenge(100), p_eTempolimit(Tempolimit::Autobahn){};

Weg::Weg(const std::string& name, double laenge, Tempolimit tempolimit)
    : Simulationsobjekt(name),
      p_dLaenge(laenge),
      p_eTempolimit(tempolimit) {}


Weg::~Weg(){}

// In Weg.cpp
void Weg::vSimulieren() {
    // First process any pending changes from previous simulation step
    p_pFahrzeuge.vAktualisieren();

    // Create a temporary list of vehicles to be removed
    std::vector<std::list<std::unique_ptr<Fahrzeug>>::iterator> toRemove;

    // Simulate each vehicle
    for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
        try {
            // Get reference to the unique_ptr
            auto& fahrzeug = *it;
            if (fahrzeug) {
                // Set the current road for the vehicle
                fahrzeug->vSetzeWeg(*this);
                // Simulate the vehicle
                fahrzeug->vSimulieren();
                // Draw the vehicle
                fahrzeug->vZeichnen(*this);
            }
        }
        catch (const Streckenende& ausnahme) {
            // Mark for removal but don't remove during iteration
            toRemove.push_back(it);
            ausnahme.vBearbeiten();
        }
    }

    // Remove vehicles that have reached the end
    for (const auto& it : toRemove) {
        p_pFahrzeuge.erase(it);
    }

    // Process all pending changes after simulation
    p_pFahrzeuge.vAktualisieren();
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug) {
    // Add moving vehicle at the back
    p_pFahrzeuge.push_back(std::move(fahrzeug));
    p_pFahrzeuge.vAktualisieren();
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double startzeit) {
    // Add parked vehicle at the front
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




std::ostream& operator<<(std::ostream& os, const Weg& weg) {
    weg.vAusgeben(os); // Call the vAusgeben function
    return os; // Return the stream reference
}

