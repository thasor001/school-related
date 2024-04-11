/**
 *   Attraksjon-header
 *
 *   @file     Attraksjon.h
 *   @author   Gruppe18
 */

#ifndef CPP_ATTRAKSJON_H
#define CPP_ATTRAKSJON_H

#include "string"
#include "fstream"
#include "iostream"
#include "funksjoner.h"

/**
 * @class Attraksjon
 */
class Attraksjon {
private:
    std::string ID, beskrivelse, adresse, website;
public:
    Attraksjon();
    Attraksjon(std::ifstream &inn);
    std::string writeID();
    virtual void skrivData() const;
    virtual void skrivTilFil(std::ofstream &ut) const;
};

#endif //CPP_ATTRAKSJON_H