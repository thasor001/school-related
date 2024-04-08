//
// Created by thara on 3/26/2024.
//

#ifndef CPP_BY_H
#define CPP_BY_H

#include <utility>

#include "string"
#include "list"
#include "Attraksjon.h"

class By {
private:
    std::list <Attraksjon*> Attraksjoner;
    std::string land;
public:
    By(std::string& land, std::ifstream & inn);
    void skrivData() const;
    void nyAttraksjon();
    void slettAttraksjon();
    void skrivTilFil(std::ofstream & ut);
    void skrivEn();
    By();
    ~By();

};

#endif
