//
// Created by thara on 3/26/2024.
//

#ifndef CPP_SEVERDIGHET_H
#define CPP_SEVERDIGHET_H

#include "Attraksjon.h"
#include "fstream"

struct Severdighet : public Attraksjon {
private:
    std::string Opplevelser;
public:
    Severdighet();
    explicit Severdighet(std::ifstream &inn);
    void skrivData() const override;
    void skrivTilFil(std::ofstream &ut) override;
};


#endif //CPP_SEVERDIGHET_H
