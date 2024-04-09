//
// Created by thara on 3/26/2024.
//

#ifndef CPP_KIRKE_H
#define CPP_KIRKE_H

#include "Attraksjon.h"
#include "Enum.h"

class Kirke : public Attraksjon {
private:
    int byggeaar;
    int kapasitet;
    Ktype Type;
public:
    Kirke();
    explicit Kirke(std::ifstream &inn);
    void skrivData() const override;
    void skrivTilFil(std::ofstream &ut) override;
};


#endif //CPP_KIRKE_H
