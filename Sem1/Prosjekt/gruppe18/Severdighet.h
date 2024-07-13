/**
 *   Severdighet-header
 *
 *   @file     Severdighet.h
 *   @author   Gruppe18
 */

#ifndef CPP_SEVERDIGHET_H
#define CPP_SEVERDIGHET_H

#include "fstream"
#include "Attraksjon.h"

/**
 * @class Severdight
 * @parent Attraksjon
 */
struct Severdighet : public Attraksjon {
private:
    std::string Opplevelser;
public:
    Severdighet();
    explicit Severdighet(std::ifstream &inn);
    void skrivData() const override;
    void skrivTilFil(std::ofstream &ut) const override;
};


#endif //CPP_SEVERDIGHET_H