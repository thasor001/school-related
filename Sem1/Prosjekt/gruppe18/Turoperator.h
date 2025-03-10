/**
 *   Turoperator-header
 *
 *   @file     Turoperator.h
 *   @author   Gruppe18
 */

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

/**
 * @class Turoperator
 */
class Turoperator {
private:
    std::string gateadresse,
                postnrsted,
                kontaktpers,
                navn,
                mail,
                website;

    int tlf, turopplegg;
public:
    Turoperator(std::ifstream &inn, std::string& navn);
    explicit Turoperator(std::string & navn);
    void endreData();
    void nyttOpplegg();
    void skrivEn() const;
    void skrivData() const;
    void skrivTilFil(std::ofstream &ut) const;
};

#endif //CPP_TUROPERATOR_H