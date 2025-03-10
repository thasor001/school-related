/**
 * Funksjoner til Kirke klasse.
 *
 * @File Kirke.cpp
 */

#include "Kirke.h"

/**
 * @Brief Leser fra fil.
 *
 * @param inn Referance til fil objekt.
 *
 * @See stringToEnum()
 * @See Attraksjon::Attraksjon(std::ifstream)
 */
Kirke::Kirke(std::ifstream &inn) : Attraksjon(inn) {
    std::string buffer;
    int aar, kap;

    inn >> buffer >> buffer;
    if (stringToEnum(buffer) >= 0)
        Type = stringToEnum(buffer);
    else
        std::cout << "\n--Failed to read Church Type : --" + buffer + "--\n";

    inn >> buffer >> buffer >> aar; inn.ignore();
    byggeaar = aar;

    inn >> buffer >> kap; inn.ignore();
    kapasitet = kap;
}

/**
 * @Breif Defualt constructor som leser til Krike.
 *
 * @See Attraksjon::Attraksjon()
 * @See stringToEnum()
 */
Kirke::Kirke() : Attraksjon() {
    std::string text;

    do {
        std::cout << "Skriv Kirke Type: (Kirke/Kapell/Katedral): ";
        std::getline(std::cin, text);
    } while(stringToEnum(text) < 0);

    Type = stringToEnum(text);

    byggeaar = lesInt("Hvilke byggeaar : ", 0, maxByggeaar);
    kapasitet = lesInt("Kapasitet : ", 0, maxKapasitet);
}

/**
 * @Brief Skriver detaljert all sin data.
 */
void Kirke::skrivData() const {
    std::cout << "Kirke "" |";
    Attraksjon::skrivData();
    std::cout
    << "\n\tByggeaar :    " << byggeaar << '\n'
    << "\tKapasitet :   " << kapasitet << '\n'
    << "\tType :        ";

    switch (Type) {
        case 0: std::cout << "Katedral\n" << std::endl;  break;
        case 1: std::cout << "Kirke\n" << std::endl;     break;
        case 2: std::cout << "Kapell\n" << std::endl;    break;
    }
}

/**
 * @param ut Referance til fil objekt.
 */
void Kirke::skrivTilFil(std::ofstream &ut) const {
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