/**
 * Funksjoner til Severdighet klasse.
 *
 * @File Severdighet.cpp
 */

#include "Severdighet.h"

/**
 * @Brief Leser fra fil.
 *
 * @param inn Referance til fil objekt.
 *
 * @See Attraksjon::Attraksjon(std::ifstream)
 */
Severdighet::Severdighet(std::ifstream &inn) : Attraksjon(inn) {
    std::string buffer;
    inn >> buffer; inn.ignore(2);
    std::getline(inn, buffer);
    Opplevelser = buffer;
}

/**
 * @Breif Defualt constructor som leser til Severdighet.
 *
 * @See Attraksjon::Attraksjon()
 */
Severdighet::Severdighet() : Attraksjon() {
    std::string text;
    std::cout << "Skriv Opplevelser : ";
    std::getline(std::cin, text);

    Opplevelser = text;
}

/**
 * @Brief Skriver detaljert all sin data.
 */
void Severdighet::skrivData() const {
    std::cout << "Severdighet "" |";
    Attraksjon::skrivData();
    std::cout << "\n\tOpplevelser : "
    << Opplevelser << std::endl;
}

/**
 * @param ut Referance til fil objekt.
 */
void Severdighet::skrivTilFil(std::ofstream &ut) const {
    ut << "S ";
    Attraksjon::skrivTilFil(ut);
    ut << "\t\tOpplevelse:  " << Opplevelser << std::endl;
}