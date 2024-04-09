#include "iostream"
#include "Byer.h"
#include "funksjoner.h"
#include "algorithm"
namespace ff = file_functions;
namespace sm = system_messages;

Byer::Byer() {
    std::ifstream inn("Byer.dta");

    std::string country, city, buffer;

    if (!inn) {
        sm::sys_error("Could Not Find File Byer.dta"); return;
    }
    sm::sys_print("File : Byer.dta Opened");

    while(std::getline(inn, buffer)) {

        ff::init_by(inn, country, city);
        byerMap[city] = new By(country, inn);

    }

    inn.close();

    sm::sys_print("All Lines Read");
    std::string message = "Antall Byer Read : "; message += std::to_string(byerMap.size());
    sm::sys_print(message);
}

Byer::~Byer() {
    for (auto & val : byerMap) {
        delete val.second;
    }
    byerMap.clear();
}

std::map <std::string, By*>& Byer::getMap() {
    return byerMap;
}

void Byer::skrivAlle() const {
    sm::sys_info("\tFoolgende Byer Finnes : \n\n");

    for (const auto &val : byerMap) {
        sm::sys_info("\tNavn : "); std::cout << val.first;
        val.second->skrivEn();
    }
}

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
                    sm::sys_info("\nNavn : " + navn + " ");
                    byerMap[navn]->skrivAlt();
                    break;
                case 'N':
                    if (Entydig("By", navn, byerMap.begin(), byerMap.end()))
                        return;
                    byerMap[navn] = new By();
                    break;
                case 'F':
                    if (!Entydig("By", navn, byerMap.begin(), byerMap.end()))
                        return;

                    delete byerMap[navn];
                    byerMap.erase(navn);
                    sm::sys_info("Fjernet : " + navn);
                    break;
            }
            break;
        case 'A':
            valg2 = egenLesChar("Skriv char her", "NFQ");
            if (valg2 == 'N') {
                if (!Entydig("By", navn, byerMap.begin(), byerMap.end()))
                    return;

                sm::sys_info("\nNy attraksjon i : " + navn + "\n");
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

void Byer::skrivTilFil() const {
    std::ofstream ut("Byer.dta2");
    int nr = 1;

    for (auto it = byerMap.begin(); it != byerMap.end(); it++) {
        ut << "City :\n" << nr << ". " << it->first << ", ";
        it->second->skrivTilFil(ut);
        nr++;
    }
    ut << "END";

    sm::sys_info("Lukket Byer.dta2\n");
    ut.close();
}
