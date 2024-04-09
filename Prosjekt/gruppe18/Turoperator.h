#ifndef CPP_TUROPERATOR_H
#define CPP_TUROPERATOR_H

#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "LesData3.h"
#include "funksjoner.h"

class Turoperator {
private:
    std::string gateadresse;
    std::string postnrsted;
    std::string kontaktpers;
    std::string navn;
    std::string mail;
    std::string website;

    int tlf;
    int turopplegg;
public:
    Turoperator(std::ifstream &inn, std::string& navn);
    explicit Turoperator(std::string & navn);
    void endreData();
    void skrivEn() const;
    void skrivData() const;
    void skrivTilFil(std::ofstream &ut) const;
    void nyttOpplegg();
};

#endif //CPP_TUROPERATOR_H
