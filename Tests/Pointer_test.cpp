#include <iostream>

class testClass {
private:
    int dato;
    int ting;
public:
    testClass() {dato = 2014; ting = 1000;}
    int hentID() {return dato;}
    int hentTING() {return ting;}
};

struct megaHack {
    int dta;
    int aduhawuhdauud;
};


int main() {
    testClass test;

    std::cout << "Old unhacked ID :" << test.hentID() << std::endl;
    megaHack *hacking = reinterpret_cast<megaHack *>(&test);
    hacking->dta = 999999;

    std::cout << "New hacked ID :  " << test.hentID() << std::endl;
    std::cout << "TING : " << test.hentTING() << std::endl;


    std::cin.get();
    return 0;
}