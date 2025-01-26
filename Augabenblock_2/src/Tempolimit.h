#ifndef TEMPOLIMIT_H
#define TEMPOLIMIT_H

#include <limits>

enum class Tempolimit {
    Innerorts,
    Landstrasse,
    Autobahn
};

inline double getTempolimit(Tempolimit tempolimit) {
    switch (tempolimit) {
        case Tempolimit::Innerorts:
            return 50.0;
        case Tempolimit::Landstrasse:
            return 100.0;
        case Tempolimit::Autobahn:
            return std::numeric_limits<double>::max();
        default:
            return 0.0;
    }
}

#endif
