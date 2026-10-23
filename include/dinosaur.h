#ifndef DINOSAUR_H
#define DINOSAUR_H

#include <string>

struct Dinosaur {
    std::string code;
    std::string name;
    std::string period;
    std::string diet;
    double lengthMeters = 0.0;
    double weightTons = 0.0;
    double ageMillionsYears = 0.0;
    std::string discoverySite;
};

#endif
