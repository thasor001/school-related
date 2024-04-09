//
// Created by Tharald on 08/04/2024.
//

#ifndef CPP_OPPLEGG_H
#define CPP_OPPLEGG_H

#include "By.h"
#include "Byer.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "LesData3.h"
#include "funksjoner.h"
#include "Attraksjon.h"
#include "Turoperatorer.h"



class Opplegg {
private:
    std::vector <std::pair<std::pair<int, std::string>, std::list <Attraksjon*>>> gDager;
    std::string beskrivelse;
    int antDager, antOpplegg;
public:
    Opplegg() {antOpplegg = 0;};
    void nyttOpplegg(std::string & TurOpperator);
};


#endif //CPP_OPPLEGG_H