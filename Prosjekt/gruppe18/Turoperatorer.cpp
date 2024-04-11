/**
 * Funksjoner for Turoperatorer objekt
 *
 * @File Turoperatorer.cpp
 */

#include "Turoperatorer.h"

/**
 *  @Brief Bruker constructor til aa lese fra fil istedet for lesfrafil func.
 *
 *  @See Turoperator::Turoperator(string, ifstream)
 */
Turoperatorer::Turoperatorer() {
    std::ifstream inn("Turoperatorer.dta");
    std::string navn;

    if (!inn) {
        std::cout << "\n--Fant ikke fil Turoperatorer.dta--\n";
        return;
    }
    std::cout << "\n--File : Turoperatorer.dta Opened--\n";

    while(inn >> navn)
        turOp[navn] = new Turoperator(inn, navn);

    std::cout << "\n--Alle Turoperatorer Lest --"+
    std::to_string(turOp.size()) << "--\n";
    inn.close();
}

/**
 * @Brief Free-er memory til alle Tuoperator-er i turOp map, og sletter pointers.
 */
Turoperatorer::~Turoperatorer() {
    for (auto & val : turOp)
        delete val.second;
    turOp.clear();
}

/**
 * @Brief Brukes til aa haandtere input til Turoperatorer.
 *
 * @See egenLesChar()
 * @See Entydig()
 * @See Turoperator::skrivEn()
 * @See Turoperator::skrivData()
 * @See Turoperator::Turoperator(string)
 * @See Turoperator::endreData()
 * @See Turoperator::nyttOpplegg()
 */
void Turoperatorer::handlinger() {
    std::string navn;
    char valg = egenLesChar("Skriv char her", "A1NEFOQ");
    auto it = turOp.begin();

    switch (valg) {
        case 'A':
            std::cout << "\tFoolgende Turoperatorer Finnes : \n\n";

            for (const auto &val : turOp)
                val.second->skrivEn();

            break;
        case '1':
            if (!Entydig("TurOperator", navn, turOp.begin(), turOp.end()))
                return;

            turOp[navn]->skrivData();
            break;
        case 'N':
            std::cout << "\nSkriv navn paa ny Turoperator";
            std::getline(std::cin, navn);
            std::transform(navn.begin(), navn.end(), navn.begin(), ::toupper);
            for (auto & val : turOp)
                if (navn == val.first)
                    return;

            turOp[navn] = new Turoperator(navn);
            break;
        case 'E':
            if (!Entydig("TurOperator", navn, turOp.begin(), turOp.end()))
                return;
            std::cout << "\nEndrer paa : " + navn + "\n";

            turOp[navn]->endreData();
            break;
        case 'O':
            if (!Entydig("TurOperator", navn, turOp.begin(), turOp.end()))
                return;
            std::cout << "\nNavn : " + navn + "\n\n";

            turOp[navn]->nyttOpplegg();
            break;
        case 'F':
            if (!Entydig("TurOperator", navn, turOp.begin(), turOp.end()))
                return;

            delete turOp[navn];
            turOp.erase(navn);
            std::cout << "\nFjernet : " + navn + "\n";
            break;
    }
}

/**
 * @See Turoperator::skrivTilFil()
 */
void Turoperatorer::skrivTilFil() const {
    std::ofstream ut("Turoperatorer.dta2");
    auto iter = turOp.rbegin();
    std::advance(iter, 1);

    for (auto it = turOp.begin(); it != turOp.end(); it++) {
        ut << it->first << " ";
        it->second->skrivTilFil(ut);
        if (it != iter.base())
            ut << std::endl;
    }
    std::cout << "\nLukker Turoperatorer.dta2\n";
    ut.close();
}