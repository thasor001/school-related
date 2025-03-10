/**
 * Funksjoner for Attraksjons klasse.
 *
 * @File Attraksjon.cpp
 */

#include "Attraksjon.h"

/**
 * @Brief Leser fra fil.
 *
 * @param inn Referance til fil objekt.
 */
Attraksjon::Attraksjon(std::ifstream &inn) {
    std::string buffer; inn.ignore();
    std::getline(inn, buffer);
    ID = buffer;

    inn >> buffer; inn.ignore();
    std::getline(inn, buffer);
    beskrivelse = buffer;

    inn >> buffer; inn.ignore(5);
    std::getline(inn, buffer);
    adresse = buffer;

    inn >> buffer; inn.ignore(7);
    std::getline(inn, buffer);
    website = buffer;
}

/**
 * @Brief @Brief Defualt constructor som leser til attraksjon.
 */
Attraksjon::Attraksjon() {
    std::cout << "Skriv ID : ";
    std::getline(std::cin, ID);

    std::cout << "Skriv Beskrivelse : ";
    std::getline(std::cin, beskrivelse);

    std::cout << "Skriv Website : ";
    std::getline(std::cin, website);

    std::cout << "Skriv Adresse : ";
    std::getline(std::cin, adresse);
}

/**
 * @Brief Brukes for bl.a printe Attraksjoner sitt navn i opperatorer.
 *
 * @return Attraksjon sin ID.
 */
std::string Attraksjon::writeID() {
    return ID;
}

/**
 * @Brief Skriver detaljert all sin data.
 */
void Attraksjon::skrivData() const {
    std::cout << " " << ID << " | " << adresse << "\n\n"
    << "\tBeskrivelse : " << beskrivelse << "\n"
    << "\tEmail :       " << website;
}

/**
 * @param ut Referance til fil objekt.
 */
void Attraksjon::skrivTilFil(std::ofstream &ut) const {
    ut << ID << std::endl;
    ut << "\t\tDescription: " << beskrivelse << std::endl;
    ut << "\t\tAddress:     " << adresse <<     std::endl;
    ut << "\t\tEmail:       " << website <<     std::endl;
}