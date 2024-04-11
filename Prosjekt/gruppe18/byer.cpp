/**
 * Funksjoner for byer objekt
 *
 * @File byer.cpp
 */

#include "Byer.h"
#include <iostream>
#include <algorithm>
#include "funksjoner.h"

/**
 *  @Brief Bruker constructor til aa lese fra fil istedet for egen lesfrafil func.
 *
 *  @See By::By(string, ifstream)
 *  @See init_by()
 */
Byer::Byer() {
    std::ifstream inn("Byer.dta");
    std::string land, by, buffer;

    if (!inn) {
        std::cout << "\n--Could Not Find File Byer.dta--\n"; return;
    }
    std::cout << "\n--File : Byer.dta Opened--\n";

    // while: Getline "City :"
    while(std::getline(inn, buffer)) {

        // Henter land og by navn.
        init_by(inn, land, by);
        byerMap[by] = new By(land, inn);

    }

    inn.close();
    std::cout << "\nAll Lines Read\n";
    std::cout << "\nAntall Byer Read : " + std::to_string(byerMap.size()) << "\n";
}

/**
 * @Brief Free-er memory til alle By-er i byerMap map, og sletter pointers.
 */
Byer::~Byer() {
    for (auto & val : byerMap)
        delete val.second;
    byerMap.clear();
}

/**
 * @Brief Brukes for aa gi tilgang til byerMap map i opperatorer.
 *
 * @return referance til byerMap.
 */
std::map <std::string, By*>& Byer::getMap() {
    return byerMap;
}

/**
 * @See By::skrivEn()
 */
void Byer::skrivAlle() const {
    std::cout << "\tFoolgende Byer Finnes : \n\n";

    for (const auto &val : byerMap) {
        std::cout << "\tNavn : "  << val.first;
        val.second->skrivEn();
    }
}

/**
 * @Brief Brukes til aa haandtere input til Byer.
 *
 * @See egenLesChar()
 * @See Entydig()
 * @See Byer::skrivAlle()
 * @See By::skrivAlt()
 * @See By::By()
 * @See By::nyAttraksjon()
 * @See By::slettAttraksjon()
 *
 * @param valg brukes for aa sjekke om A eller B.
 */
void Byer::handling(char valg) {
    char valg2;
    std::string navn;

    switch (valg) {
        case 'B':
            valg2 = egenLesChar("Skriv char her", "A1NFQ");
            switch (valg2) {
                case 'A':
                    Byer::skrivAlle();
                break;
                case '1':
                    if (!Entydig("By", navn, byerMap.begin(), byerMap.end()))
                        return;
                    std::cout << "\nNavn : " + navn + " ";
                    byerMap[navn]->skrivAlt();
                    break;
                case 'N':
                    std::cout << "\nSkriv Navn paa by : ";
                    std::getline(std::cin, navn);
                    std::transform(navn.begin(), navn.end(), navn.begin(), ::toupper);
                    for (const auto & val : byerMap)
                        if (val.first == navn)
                            return;

                    byerMap[navn] = new By();
                    break;
                case 'F':
                    if (!Entydig("By", navn, byerMap.begin(), byerMap.end()))
                        return;

                    delete byerMap[navn];
                    byerMap.erase(navn);
                    std::cout << "Fjernet : " + navn;
                    break;
            }
            break;
        case 'A':
            valg2 = egenLesChar("Skriv char her", "NFQ");
            if (valg2 == 'N') {
                if (!Entydig("By", navn, byerMap.begin(), byerMap.end()))
                    return;

                std::cout << "\nNy attraksjon i : " + navn + "\n";
                byerMap[navn]->nyAttraksjon();
            }
            else if (valg2 == 'F') {
                if (!Entydig("By", navn, byerMap.begin(), byerMap.end()))
                    return;

                byerMap[navn]->skrivAlt();
                byerMap[navn]->slettAttraksjon();
            }
            break;
    }
}

/**
 * @See By::skrivTilFil()
 */
void Byer::skrivTilFil() const {
    std::ofstream ut("Byer.dta2");
    int nr = 1;

    for (auto it = byerMap.begin(); it != byerMap.end(); it++) {
        ut << "City :\n" << nr << ". " << it->first << ", ";
        it->second->skrivTilFil(ut);
        nr++;
    }
    ut << "END";

    std::cout << "Lukket Byer.dta2\n";
    ut.close();
}