/**
 *   Krike-header
 *
 *   @file     Kirke.h
 *   @author   Gruppe18
 */

#ifndef CPP_KIRKE_H
#define CPP_KIRKE_H

#include "Enum.h"
#include "Consts.h"
#include "LesData3.h"
#include "Attraksjon.h"

/**
 * @class Krike
 * @parent Attraksjon
 */
class Kirke : public Attraksjon {
private:
    int byggeaar;
    int kapasitet;
    Ktype Type;
public:
    Kirke();
    explicit Kirke(std::ifstream &inn);
    void skrivData() const override;
    void skrivTilFil(std::ofstream &ut) const override;
};

#endif //CPP_KIRKE_H