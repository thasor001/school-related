//
// Created by Tharald on 05/04/2024.
//

#include "By.h"
#include "Kirke.h"
#include "MuseumGalleri.h"
#include "Severdighet.h"
#include "funksjoner.h"
#include "LesData3.h"
namespace sm = system_messages;

By::By(std::string& name, std::ifstream &inn) {
    land = std::move(name);

    char buffer;
    char type;

    do {
        inn >> buffer >> type;

        switch (type) {
            case 'K': Attraksjoner.push_back(new Kirke(inn));         break;
            case 'M': Attraksjoner.push_back(new MuseumGalleri(inn)); break;
            case 'S': Attraksjoner.push_back(new Severdighet(inn));   break;
            case 'i':                                                return;
            case 'N': inn >> buffer;                                 return;
            default:
                sm::sys_error("DEFAULT wrong file Structure");
                return;
        }
    } while (buffer == '-');
}

By::By() {
    std::cout << "\nSkriv Navn Paa Land : ";
    std::getline(std::cin, land);
}

By::~By() {
    for (auto & val : Attraksjoner) {
        delete val;
    }
    Attraksjoner.clear();
}

std::list <Attraksjon*>& By::getList() {
    return Attraksjoner;
}

void By::skrivTilFil(std::ofstream &ut) const {
    ut << land << std::endl;
    for (auto it = Attraksjoner.begin(); it != Attraksjoner.end(); it++) {
        ut << "\t- ";
        (*it)->skrivTilFil(ut);
    }
}

void By::skrivEn() const {
    sm::sys_info("\t\tLand : "); std::cout << land;
    sm::sys_info("\t Ant Attraksjoner : ");
    std::cout << Attraksjoner.size(); std::cout << std::endl;
}

void By::skrivAlt() const {
    int size = 1;

    std::cout << " Land : " << land
    << ", Antall Attraksjoner : " << Attraksjoner.size() << "\n\n";

    for (const auto &val : Attraksjoner) {
        std::cout << size << ". " << "Attraksjons Type : ";

        val->skrivData();
        std::cout << std::endl;
        size++;
    }
}

void By::nyAttraksjon() {
    char type = egenLesChar("Skriv Type Attraksjon", "KSM");

    switch (type) {
        case 'K': Attraksjoner.push_back(new Kirke);                 break;
        case 'S': Attraksjoner.push_back(new Severdighet);           break;
        case 'M': Attraksjoner.push_back(new MuseumGalleri);         break;
    }
}

void By::slettAttraksjon() {
    if (Attraksjoner.size() > 0) {
        std::cout << "0 = ingen" << std::endl;
        int valg = lesInt("Velg Fra Nummer ", 0, Attraksjoner.size());

        if (valg == 0) {
            std::cout << "Ingen Slettet" << std::endl;
            return;
        }

        auto it = Attraksjoner.begin();
        std::advance(it, valg - 1);

        Attraksjoner.erase(it);
    } else {
        std::cout << "Ingen Attraksjoner" << std::endl;
    }
}