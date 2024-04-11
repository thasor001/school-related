/**
 * Funksjoner til MuseumGalleri klasse.
 *
 * @File MuseumGalleri.cpp
 */

#include "MuseumGalleri.h"

/**
 * @Brief Leser fra fil.
 *
 * @param inn Referance til fil objekt.
 *
 * @See Attraksjon::Attraksjon(std::ifstream)
 */
MuseumGalleri::MuseumGalleri(std::ifstream &inn) : Attraksjon(inn) {
    std::string buffer;
    inn >> buffer; inn.ignore(3);
    std::getline(inn, buffer);
    hooydepunkter = buffer;
}

/**
 * @Breif Defualt constructor som leser til MuseumGalleri.
 *
 * @See Attraksjon::Attraksjon()
 */
MuseumGalleri::MuseumGalleri() : Attraksjon() {
    std::string text;
    std::cout << "Skriv hooydepunkter : ";
    std::getline(std::cin, text);

    hooydepunkter = text;
}

/**
 * @Brief Skriver detaljert all sin data.
 */
void MuseumGalleri::skrivData() const {
    std::cout << "MuseumGalleri "" |";
    Attraksjon::skrivData();
    std::cout << "\n\tHooydepunkt : "
    << hooydepunkter << std::endl;
}

/**
 * @param ut Referance til fil objekt.
 */
void MuseumGalleri::skrivTilFil(std::ofstream &ut) const {
    ut << "M ";
    Attraksjon::skrivTilFil(ut);
    ut << "\t\tHighLight:   " << hooydepunkter << std::endl;
}