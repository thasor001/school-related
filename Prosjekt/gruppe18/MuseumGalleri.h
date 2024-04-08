//
// Created by thara on 3/26/2024.
//

#ifndef CPP_MUSEUMGALLERI_H
#define CPP_MUSEUMGALLERI_H

#include "Attraksjon.h"

class MuseumGalleri : public Attraksjon {
private:
    std::string hooydepunkter;
public:
    MuseumGalleri(std::ifstream &inn);
    virtual void skrivData() const override;
    virtual void skrivTilFil(std::ofstream &ut) override;
    MuseumGalleri();
};


#endif //CPP_MUSEUMGALLERI_H
