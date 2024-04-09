//
// Created by Tharald on 06/04/2024.
//

#include "Kirke.h"
#include "funksjoner.h"
#include "LesData3.h"
namespace ff = file_functions;
namespace sm = system_messages;


Kirke::Kirke(std::ifstream &inn) : Attraksjon(inn) {
    std::string buffer;
    int aar, kap;

    inn >> buffer >> buffer;
    if (ff::stringToEnum(buffer) >= 0) {
        Type = ff::stringToEnum(buffer);
    } else {
        sm::sys_error("Failed to read Church Type : --" + buffer);
    }

    inn >> buffer >> buffer >> aar; inn.ignore();
    byggeaar = aar;

    inn >> buffer >> kap; inn.ignore();
    kapasitet = kap;
}

void Kirke::skrivData() const {
    sm::sys_info("Kirke ");
    std::cout << " |";
    Attraksjon::skrivData();
    std::cout << "\n\tByggeaar : " << byggeaar << '\n'
    << "\tKapasitet : " << kapasitet << '\n'
    << "\tType : ";

    switch (Type) {
        case 0: std::cout << "Katedral\n" << std::endl;  break;
        case 1: std::cout << "Kirke\n" << std::endl;     break;
        case 2: std::cout << "Kapell\n" << std::endl;    break;
    }
}

void Kirke::skrivTilFil(std::ofstream &ut) {
    ut << "K ";
    Attraksjon::skrivTilFil(ut);
    ut << "\t\tType:        ";

    switch (Type) {
        case 0: ut << "Katedral\n"; break;
        case 1: ut << "Kirke\n";    break;
        case 2: ut << "Kapell\n";   break;
    }

    ut << "\t\tYear built:  " << byggeaar << std::endl;
    ut << "\t\tCapacity:    " << kapasitet << std::endl;

}

Kirke::Kirke() : Attraksjon() {
    std::string text;

    do {
        std::cout << "Skriv Kirke Type: (Kirke/Kapell/Katedral): ";
        std::getline(std::cin, text);
    } while(ff::stringToEnum(text) < 0);

    Type = ff::stringToEnum(text);

    byggeaar = lesInt("Hvilke byggeaar : ", 0, 2024);

    kapasitet = lesInt("Kapasitet : ", 0, 2000);
}


