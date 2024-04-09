//
// Created by Tharald on 08/04/2024.
//

#ifndef CPP_OPPLEGG_H
#define CPP_OPPLEGG_H

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
    std::vector <std::pair<std::pair<int, std::string>,std::list <Attraksjon*>>> Dager;
public:
    void nyttOpplegg(const std::string & Operator, int & opplegg);
};


#endif //CPP_OPPLEGG_H