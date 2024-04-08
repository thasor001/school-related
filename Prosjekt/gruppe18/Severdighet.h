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
    Severdighet(std::ifstream &inn);
    virtual void skrivData() const override;
    virtual void skrivTilFil(std::ofstream &ut) override;
    Severdighet();
};


#endif //CPP_SEVERDIGHET_H
