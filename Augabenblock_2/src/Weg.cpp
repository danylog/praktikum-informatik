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

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug) {
    fahrzeug->vNeueStrecke(*this);
    p_pFahrzeuge.push_back(std::move(fahrzeug));
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double startzeit) {
    fahrzeug->vNeueStrecke(*this, startzeit);
    p_pFahrzeuge.push_front(std::move(fahrzeug));
}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fahrzeug) {
    for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
        if (it->get() == &fahrzeug) {
            std::unique_ptr<Fahrzeug> temp = std::move(*it);
            p_pFahrzeuge.erase(it);
            return temp;
        }
    }
    return nullptr;
}

void Weg::vSimulieren() {
    // Make a copy of the list size since it might change during iteration
    size_t originalSize = p_pFahrzeuge.size();
    size_t processed = 0;

    for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end() && processed < originalSize;) {
        try {
            if (*it) {
                (*it)->vSimulieren();
                (*it)->vZeichnen(*this);
                ++it;
                ++processed;
            } else {
                it = p_pFahrzeuge.erase(it);
            }
        }
        catch (const Losfahren& ausnahme) {
            ausnahme.vBearbeiten();
            ++it;
            ++processed;
        }
        catch (const Streckenende& ausnahme) {
            ausnahme.vBearbeiten();
            it = p_pFahrzeuge.erase(it);  // Remove the vehicle here directly
            // Don't increment processed since we removed an element
        }
    }
}


void Weg::vKopf(std::ostream& os) {
    os << std::setw(5) << "ID"
       << " | " << std::setw(10) << "Name"
       << " | " << std::setw(10) << "Laenge"
       << " | " << "Fahrzeuge" << "\n"
       << std::string(50, '-') << "\n"; // @suppress("Symbol is not resolved")
}

void Weg::vAusgeben(std::ostream& os) const {
    os << std::setw(5) << iID()
       << " | " << std::setw(10) << sName()
       << " | " << std::setw(10) << std::fixed << std::setprecision(2) << p_dLaenge
       << " | (";

    bool first = true;
    for (const auto& fahrzeug : p_pFahrzeuge) {
        if (!first) os << ", ";
        os << fahrzeug->sName();
        first = false;
    }
    os << ")" << std::endl;

    if (!p_pFahrzeuge.empty()) {
        os << std::setw(30) << " " << "Fahrzeuge:" << std::endl;
        Fahrzeug::vKopf();
        for (const auto& fahrzeug : p_pFahrzeuge) {
            fahrzeug->vAusgeben(os);
            os << std::endl;
        }
    }
}


std::ostream& operator<<(std::ostream& os, const Weg& weg) {
    weg.vAusgeben(os); // Call the vAusgeben function
    return os; // Return the stream reference
}

