//
// Created by Tharald on 05/04/2024.
//

#include "Attraksjon.h"

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

void Attraksjon::skrivTilFil(std::ofstream &ut) {
    ut << ID << std::endl;
    ut << "\t\tDescription: " << beskrivelse << std::endl;
    ut << "\t\tAddress:     " << adresse <<     std::endl;
    ut << "\t\tEmail:       " << website <<     std::endl;
}

void Attraksjon::skrivData() const {
    std::cout << " " << ID << " | " << adresse << "\n\n"
    << "\tBeskrivelse : " << beskrivelse << "\n"
    << "\tEmail : " << website;
}

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
