//
// Created by Tharald on 06/04/2024.
//

#include "MuseumGalleri.h"

MuseumGalleri::MuseumGalleri(std::ifstream &inn) : Attraksjon(inn) {
    std::string buffer;
    inn >> buffer; inn.ignore(3);
    std::getline(inn, buffer);
    hooydepunkter = buffer;
}

void MuseumGalleri::skrivData() const {
    Attraksjon::skrivData();
    std::cout << "\n\tHooydepunkt :"
    << hooydepunkter << std::endl;
}

void MuseumGalleri::skrivTilFil(std::ofstream &ut) {
    ut << "M ";
    Attraksjon::skrivTilFil(ut);
    ut << "\t\tHighLight:   " << hooydepunkter << std::endl;
}

MuseumGalleri::MuseumGalleri() : Attraksjon() {
    std::string text;
    std::cout << "Skriv hooydepunkter : ";
    std::getline(std::cin, text);

    hooydepunkter = text;
}