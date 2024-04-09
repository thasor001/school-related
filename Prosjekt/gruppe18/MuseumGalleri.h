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
    MuseumGalleri();
    explicit MuseumGalleri(std::ifstream &inn);
    void skrivData() const override;
    void skrivTilFil(std::ofstream &ut) override;
};


#endif //CPP_MUSEUMGALLERI_H
