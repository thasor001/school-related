/**
 *   MuseumGalleri-header
 *
 *   @file     MuseumGalleri.h
 *   @author   Gruppe18
 */

#ifndef CPP_MUSEUMGALLERI_H
#define CPP_MUSEUMGALLERI_H

#include "Attraksjon.h"

/**
 * @class MuseumGalleri
 * @parent Attraksjon
 */
class MuseumGalleri : public Attraksjon {
private:
    std::string hooydepunkter;
public:
    MuseumGalleri();
    explicit MuseumGalleri(std::ifstream &inn);
    void skrivData() const override;
    void skrivTilFil(std::ofstream &ut) const override;
};


#endif //CPP_MUSEUMGALLERI_H