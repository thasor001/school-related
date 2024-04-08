#ifndef CPP_TUROPERATORER_H
#define CPP_TUROPERATORER_H

#include <map>
#include <string>
#include "Turoperator.h"
#include "fstream"

class Turoperatorer {
private:
    std::map <std::string, Turoperator*> turOp;
public:
    void lesFraFil();
    void handlinger();
    void skrivTilFil();
    bool Entydig(std::string& navn);
    std::string sjekkEntydig(std::string& input);
    ~Turoperatorer();
};

#endif