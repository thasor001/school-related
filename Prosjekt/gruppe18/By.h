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
    By();
    ~By();
    void nyAttraksjon();
    void skrivEn() const;
    void skrivAlt() const;
    void slettAttraksjon();
    std::list <Attraksjon*>& getList();
    void skrivTilFil(std::ofstream & ut) const;
};

#endif
