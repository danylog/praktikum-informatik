#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include <string>

class Fahrzeug {
public:
    Fahrzeug();
    Fahrzeug(const std::string& name);
    virtual ~Fahrzeug();

private:
    std::string p_sName;
    const int p_iID;
    static int p_iMaxID;
};

#endif
