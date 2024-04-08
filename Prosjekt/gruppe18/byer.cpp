#include "iostream"
#include "Byer.h"
#include "funksjoner.h"
#include "algorithm"
namespace ff = file_functions;
namespace sm = system_messages;

extern Byer gByerBase;

std::string Byer::sjekkEntydig(std::string& input) {
    int count = 0;
    std::string name;
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);
    for (auto it = byerMap.begin(); it != byerMap.end(); it++) {
        if (it->first.substr(0, input.length()) == input) {
            name = it->first; count++;
        }
        if (count > 1)
            return input;
    }
    return name;
}

void Byer::lesFraFil() {
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

bool Byer::Entydig(std::string& navn) {
    sm::sys_info("Skriv navn paa By : ");
    std::getline(std::cin, navn);
    std::transform(navn.begin(), navn.end(), navn.begin(), ::toupper);

    navn = Byer::sjekkEntydig(navn);
    if (byerMap.find(navn) == byerMap.end()) {
        sm::sys_info("\nFinnes ikke i byerMap\n");
        return false;
    }
    return true;
}

void Byer::handling(char valg) {
    char valg2;
    int size = 1;
    std::string navn;

    switch (valg) {
        case 'B':
            valg2 = egenLesChar("Skriv char her", "A1NFQ");
            switch (valg2) {
                case 'A':
                    sm::sys_info("Skriver Byer Data : \n\n");
                    sm::sys_info("\tFoolgende Byer Finnes : \n\n");

                    for (const auto &val : byerMap) {
                        sm::sys_info("\tNavn : "); std::cout << val.first;
                        val.second->skrivEn();
                    }
                    break;
                case '1':
                    Byer::Entydig(navn);
                    sm::sys_info("\nNavn : " + navn + " ");
                    byerMap[navn]->skrivData();
                    break;
                case 'N':
                    Byer::Entydig(navn);
                    byerMap[navn] = new By();
                    break;
                case 'F':
                    Byer::Entydig(navn);

                    delete byerMap[navn];
                    byerMap.erase(navn);
                    sm::sys_info("Fjernet : " + navn);
                    break;
            }
            break;
        case 'A':
            valg2 = egenLesChar("Skriv char her", "NFQ");
            switch (valg2) {
                case 'N':
                    Byer::Entydig(navn);
                    byerMap[navn]->nyAttraksjon();
                    break;
                case 'F':
                    Byer::Entydig(navn);

                    byerMap[navn]->skrivData();
                    byerMap[navn]->slettAttraksjon();
                    break;
            }
            break;
        default: sm::sys_error("Unexpected Kommand i Byer::Handling"); return;
    }
}

void Byer::skrivTilFil() {
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
