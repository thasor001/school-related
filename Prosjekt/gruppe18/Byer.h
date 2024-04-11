/**
 *   Byer-header
 *
 *   @file     Byer.h
 *   @author   Gruppe18
 */

#ifndef CPP_BYER_H
#define CPP_BYER_H

#include <map>
#include "By.h"
#include <string>
#include <fstream>

/**
 * @class Byer
 */
class Byer {
private:
    std::map <std::string, By*> byerMap;
public:
    Byer();
    ~Byer();
    void skrivAlle() const;
    void handling(char valg);
    void skrivTilFil() const;
    std::map <std::string, By*>& getMap();
};

#endif