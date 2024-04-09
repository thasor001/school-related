#include "Severdighet.h"
namespace sm = system_messages;

Severdighet::Severdighet(std::ifstream &inn) : Attraksjon(inn) {
    std::string buffer;
    inn >> buffer; inn.ignore(3);
    std::getline(inn, buffer);
    Opplevelser = buffer;
}

void Severdighet::skrivData() const {
    sm::sys_info("Severdighet ");
    std::cout << " |";
    Attraksjon::skrivData();
    std::cout << "\n\tOpplevelser : "
    << Opplevelser << std::endl;
}

void Severdighet::skrivTilFil(std::ofstream &ut) {
    ut << "S ";
    Attraksjon::skrivTilFil(ut);
    ut << "\t\tHighLight:   " << Opplevelser << std::endl;
}

Severdighet::Severdighet() : Attraksjon() {
    std::string text;
    std::cout << "Skriv Opplevelser : ";
    std::getline(std::cin, text);

    Opplevelser = text;
}