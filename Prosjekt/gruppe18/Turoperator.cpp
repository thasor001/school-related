#include "Turoperator.h"
#include "iostream"
#include "string"
#include "funksjoner.h"
#include "LesData3.h"
namespace ff = file_functions;
namespace sm = system_messages;

Turoperator::Turoperator(std::ifstream &inn) {
    std::string buffer;

    ff::get_lines(inn, gateadresse, 1);
    ff::get_lines(inn, postnr, 3);
    ff::get_lines(inn, kontaktpers, 1);
    ff::get_lines(inn, mail, 2);
    ff::get_lines(inn, website, 6);

    inn >> buffer >> buffer >> buffer >> tlf;
    inn.ignore();
    turopplegg = 0;
}

Turoperator::Turoperator(std::string &navn) {
    std::cout << "Post Nummer : ";
    std::getline(std::cin, postnr);

    std::cout << "Sted : ";
    std::getline(std::cin, sted);

    std::cout << "Gate Adresse : ";
    std::getline(std::cin, gateadresse);

    std::cout << "Kontaktperson : ";
    std::getline(std::cin, kontaktpers);

    std::cout << "Email : ";
    std::getline(std::cin, mail);

    std::cout << "Website : ";
    std::getline(std::cin, website);

    tlf = lesInt("Telefon Nummer ", 10000, 99999999);

    this->navn = navn;
    turopplegg = 0;
}

void Turoperator::endreData() {
    char valg;
    sm::sys_info("\nQ = Quit ");
    std::string name;

    std::cout << "|N - Navn| ""|P - PostNr| ""|S - Sted| "
    "|K - KontPers| ""|G - GateAdr| ""|M - Mail| ""|W - Webiste|\n";

    do {
        valg = egenLesChar("Endre paa : ", "NPSKGMW");
        switch (valg) {
            case 'G':
                std::cout << "\n\tNy GateAdr : ";
                std::getline(std::cin, gateadresse);
                break;
            case 'P':
                std::cout << "\n\tNy Post Nr : ";
                std::getline(std::cin, postnr);
                break;
            case 'S':
                std::cout << "\n\tNytt Sted : ";
                std::getline(std::cin, sted);
                break;
            case 'K':
                std::cout << "\n\tNy Kontakt Pers : ";
                std::getline(std::cin, kontaktpers);
                break;
            case 'N':
                std::cout << "\n\tNytt Navn : ";
                std::getline(std::cin, navn);
                break;
            case 'M':
                std::cout << "\n\tNy Mail : ";
                std::getline(std::cin, mail);
                break;
            case 'W':
                std::cout << "\n\tNy Website : ";
                std::getline(std::cin, website);
                break;
        }
    } while (valg != 'Q');
    sm::sys_info("\nNy Tur Opperator :\n");
    sm::sys_info("\n\t" + navn + "\t");
    Turoperator::skrivData();
}

void Turoperator::skrivData() const {
    std::cout << "\t" << turopplegg << " Opplegg\t" << website << std::endl;
    std::cout << "\t" << gateadresse << ", " << postnr << std::endl;
    std::cout << "\t" << kontaktpers << ", "
    << tlf << ", " << mail << std::endl;
}

void Turoperator::skrivEn() {
    std::cout << "\t\t" << turopplegg; sm::sys_info(" : Opplegg");
    sm::sys_info("\tEmail : "); std::cout << mail << std::endl;
}

void Turoperator::skrivTilFil(std::ofstream &ut) {
    ut << " - Street Address: " << gateadresse << std::endl;
    ut << " - Post Address:   " << postnr << std::endl;
    ut << " - Contact Person: " << kontaktpers << std::endl;
    ut << " - Email Address:  " << mail << std::endl;
    ut << " - Home Page:      " << website << std::endl;
    ut << " - Phone Number:   " << tlf << std::endl;
}
