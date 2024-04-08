//
// Created by thara on 3/26/2024.
//

#ifndef CPP_TUROPERATOR_H
#define CPP_TUROPERATOR_H

#include "string"
#include "fstream"
#include "iostream"
#include "iomanip"

class Turoperator {
private:
    std::string gateadresse;
    std::string postnr;
    std::string sted;
    std::string kontaktpers;
    std::string navn;
    std::string mail;
    std::string website;

    int tlf;
    int turopplegg;
public:
    Turoperator(std::ifstream &inn);
    Turoperator(std::string &navn);
    Turoperator(){};
    std::string hentNavn() {return navn;};
    void skrivTilFil(std::ofstream &ut);
    void skrivData() const;
    void skrivEn();
    void endreData();
};

#endif //CPP_TUROPERATOR_H
