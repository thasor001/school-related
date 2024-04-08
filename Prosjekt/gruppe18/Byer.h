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
    void lesFraFil();
    void handling(char valg);
    std::string sjekkEntydig(std::string& input);
    void skrivTilFil();
    bool Entydig(std::string& navn);
};

#endif