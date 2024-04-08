//
// Created by thara on 3/26/2024.
//
#include "Turoperatorer.h"
#include "Turoperator.h"
#include "iostream"
#include "funksjoner.h"
#include "algorithm"
namespace sm = system_messages;

extern Turoperator gOprasjonsBase;

void Turoperatorer::lesFraFil() {
    std::ifstream inn("Turoperatorer.dta");
    std::string name;

    if (!inn) {
        sm::sys_error("Fant ikke fil Turoperatorer.dta");
        return;
    }
    sm::sys_print("File : Turoperatorer.dta Opened");

    while(std::getline(inn, name)) {
        turOp[name] = new Turoperator(inn);
    }

    sm::sys_print("Alle Turoperatorer Lest --" + std::to_string(turOp.size()));

    inn.close();
}

bool Turoperatorer::Entydig(std::string& navn) {
    sm::sys_info("Skriv navn paa Tur Operator : ");
    std::getline(std::cin, navn);
    std::transform(navn.begin(), navn.end(), navn.begin(), ::toupper);

    navn = Turoperatorer::sjekkEntydig(navn);
    if (turOp.find(navn) == turOp.end()) {
        sm::sys_info("\nFinnes ikke i turOp\n");
        return false;
    }
    return true;
}

void Turoperatorer::skrivTilFil() {
    std::ofstream ut("Turoperatorer.dta2");
    for (auto it = turOp.begin(); it != turOp.end(); it++) {
        ut << it->first << std::endl;
        it->second->skrivTilFil(ut);
    }
    sm::sys_info("\nLukker Turoperatorer.dta2\n");
    ut.close();
}

std::string Turoperatorer::sjekkEntydig(std::string& input) {
    int count = 0;
    std::string name;
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);
    for (auto it = turOp.begin(); it != turOp.end(); it++) {
        if (it->first.substr(0, input.length()) == input) {
            name = it->first; count++;
        }
        if (count > 1)
            return input;
    }
    return name;
}



void Turoperatorer::handlinger() {
    std::string navn;
    char valg = egenLesChar("Skriv char her", "A1NEFOQ");

    switch (valg) {
        case 'A':
            sm::sys_info("Skriver Turoperatorer Data : \n\n");
            sm::sys_info("\tFoolgende Turoperatorer Finnes : \n\n");

            for (const auto &val : turOp) {
                sm::sys_info("\tNavn : "); std::cout << val.first;
                val.second->skrivEn();
            }
            break;
        case '1':
            Turoperatorer::Entydig(navn);
            sm::sys_info("\n\t" + navn + "\t");
            turOp[navn]->skrivData();
            break;
        case 'N':
            Turoperatorer::Entydig(navn);
            turOp[navn] = new Turoperator(navn);
            break;
        case 'E':
            Turoperatorer::Entydig(navn);
            sm::sys_info("\nEndrer paa : " + navn + "\n");

            turOp[navn]->endreData();
            Turoperator * nyTurOp;
            nyTurOp = turOp[navn];

            turOp.erase(navn);
            turOp[nyTurOp->hentNavn()] = nyTurOp;
            break;
        case 'F':
            Turoperatorer::Entydig(navn);

            delete turOp[navn];
            turOp.erase(navn);
            sm::sys_info("\nFjernet : " + navn + "\n");
            break;
    }

}

Turoperatorer::~Turoperatorer() {
    for (auto & val : turOp) {
        delete val.second;
    }
    turOp.clear();
}