#ifndef CPP_BYER_H
#define CPP_BYER_H

#include <fstream>
#include "By.h"
#include <map>
#include <string>


class Byer {
private:
    std::map <std::string, By*> byerMap;
public:
    Byer();
    ~Byer();
    void handling(char valg);
    void skrivTilFil() const;
    std::map <std::string, By*>& getMap();
};

#endif