//
// Created by thara on 3/26/2024.
//

#ifndef CPP_ATTRAKSJON_H
#define CPP_ATTRAKSJON_H

#include "string"
#include "fstream"
#include "iostream"
#include "funksjoner.h"

class Attraksjon {
private:
    std::string ID, beskrivelse, adresse, website;
public:
    Attraksjon();
    Attraksjon(std::ifstream &inn);
    virtual void skrivData() const;
    virtual void skrivTilFil(std::ofstream &ut);
    std::string writeID() const;
};

#endif //CPP_ATTRAKSJON_H
