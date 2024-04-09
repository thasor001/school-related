#include "Turoperatorer.h"
#include "Opplegg.h"
namespace sm = system_messages;

extern Opplegg gOppleggsBase;

Turoperatorer::Turoperatorer() {
    std::ifstream inn("Turoperatorer.dta");
    std::string navn;

    if (!inn) {
        sm::sys_error("Fant ikke fil Turoperatorer.dta");
        return;
    }
    sm::sys_print("File : Turoperatorer.dta Opened");

    while(std::getline(inn, navn)) {
        turOp[navn] = new Turoperator(inn, navn);
    }

    sm::sys_print("Alle Turoperatorer Lest --" + std::to_string(turOp.size()));
    inn.close();
}

void Turoperatorer::skrivTilFil() const {
    std::ofstream ut("Turoperatorer.dta2");
    auto iter = turOp.begin();
    std::advance(iter, turOp.size() - 1);

    for (auto it = turOp.begin(); it != turOp.end(); it++) {
        ut << it->first << std::endl;
        it->second->skrivTilFil(ut);
        if (it != iter)
            ut << std::endl;
    }
    sm::sys_info("\nLukker Turoperatorer.dta2\n");
    ut.close();
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
            if (!Entydig("TurOperator", navn, turOp.begin(), turOp.end()))
                return;
            sm::sys_info("\n\t" + navn + "\t");
            turOp[navn]->skrivData();
            break;
        case 'N':
            sm::sys_info("\nSkriv navn paa ny Turoperator");
            std::getline(std::cin, navn);
            std::transform(navn.begin(), navn.end(), navn.begin(), ::toupper);
            for (auto & val : turOp) {
                if (navn == val.first)
                    return;
            }

            turOp[navn] = new Turoperator(navn);
            break;
        case 'E':
            if (!Entydig("TurOperator", navn, turOp.begin(), turOp.end()))
                return;
            sm::sys_info("\nEndrer paa : " + navn + "\n");

            turOp[navn]->endreData();
            break;
        case 'O':
            if (!Entydig("TurOperator", navn, turOp.begin(), turOp.end()))
                return;
            sm::sys_info("\nNavn : " + navn + "\n\n");
            gOppleggsBase.nyttOpplegg(navn);
            break;
        case 'F':
            if (!Entydig("TurOperator", navn, turOp.begin(), turOp.end()))
                return;

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