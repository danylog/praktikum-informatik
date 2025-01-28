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
    // First process any pending changes
    p_pFahrzeuge.vAktualisieren();

    // Use iterator-based loop since we might modify the list
    for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); /*no increment here*/) {
        try {
            // Get reference to the current vehicle
            auto& fahrzeug = *it;
            fahrzeug->vSimulieren();
            fahrzeug->vZeichnen(*this);
            // Only increment if no exception was thrown
            ++it;
        }
        catch (const Losfahren& ausnahme) {
            ausnahme.vBearbeiten();
            // Don't increment iterator - vehicle stays in same position
            ++it;
        }
        catch (const Streckenende& ausnahme) {
            ausnahme.vBearbeiten();
            // Mark for deletion using VListe's erase
            p_pFahrzeuge.erase(it);
            // Don't increment - erase handles the iterator
            break;  // Exit loop since list is modified
        }
    }

    // Process all pending changes after simulation
    p_pFahrzeuge.vAktualisieren();
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug) {
    // Set up the vehicle's behavior before adding it to the list
    fahrzeug->vNeueStrecke(*this);  // <-- Add this line
    // Add moving vehicle at the back
    p_pFahrzeuge.push_back(std::move(fahrzeug));
    p_pFahrzeuge.vAktualisieren();
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double startzeit) {
    // Set up the vehicle's parking behavior before adding it to the list
    fahrzeug->vNeueStrecke(*this, startzeit);  // <-- Add this line
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

