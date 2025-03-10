/**
 *   Turoperatorer-header
 *
 *   @file     Turoperatorer.h
 *   @author   Gruppe18
 */

#ifndef CPP_TUROPERATORER_H
#define CPP_TUROPERATORER_H

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "funksjoner.h"
#include "Turoperator.h"

/**
 * @class Turoperatorer
 */
class Turoperatorer {
private:
    std::map <std::string, Turoperator*> turOp;
public:
    Turoperatorer();
    ~Turoperatorer();
    void handlinger();
    void skrivTilFil() const;
};

#endif