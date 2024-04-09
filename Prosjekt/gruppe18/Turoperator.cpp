#include "Opplegg.h"
#include "Turoperator.h"

namespace ff = file_functions;
namespace sm = system_messages;

extern Opplegg gOppleggsBase;

Turoperator::Turoperator(std::ifstream &inn, std::string& navn) {
    std::string buffer;

    inn >> turopplegg; inn.ignore();

    ff::get_lines(inn, gateadresse, 8);
    ff::get_lines(inn, kontaktpers, 8);
    ff::get_lines(inn, mail, 9);
    ff::get_lines(inn, website, 13);
    ff::get_lines(inn, postnrsted, 10);

    inn >> buffer >> buffer >> buffer >> tlf;
    inn.ignore();
    this->navn = navn;
}

Turoperator::Turoperator(std::string & navn) {
    std::cout << "Post/Sted Nummer : ";
    std::getline(std::cin, postnrsted);

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

void Turoperator::nyttOpplegg() {
    gOppleggsBase.nyttOpplegg(navn, turopplegg);
}

void Turoperator::endreData() {
    char valg;
    sm::sys_info("\nQ = Quit ");
    std::string name;

    std::cout << "|P - PostNr| ""|S - Sted| "
    "|K - KontPers| ""|G - GateAdr| ""|M - Mail| ""|W - Webiste|\n";

    do {
        valg = egenLesChar("Endre paa : ", "PKGMW");
        switch (valg) {
            case 'G':
                std::cout << "\n\tNy GateAdr : ";
                std::getline(std::cin, gateadresse);
                break;
            case 'P':
                std::cout << "\n\tNy Post Nr : ";
                std::getline(std::cin, postnrsted);
                break;
            case 'K':
                std::cout << "\n\tNy Kontakt Pers : ";
                std::getline(std::cin, kontaktpers);
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
    std::cout << "\t" << gateadresse << ", " << postnrsted << std::endl;
    std::cout << "\t" << kontaktpers << ", "
    << tlf << ", " << mail << std::endl;
}

void Turoperator::skrivEn() const {
    std::cout << "\t\t" << turopplegg; sm::sys_info(" : Opplegg");
    sm::sys_info("\tEmail : "); std::cout << mail << std::endl;
}

void Turoperator::skrivTilFil(std::ofstream &ut) const {
    ut << " - Street Address:        " << gateadresse << std::endl;
    ut << " - Contact Person:        " << kontaktpers << std::endl;
    ut << " - Email Address:         " << mail << std::endl;
    ut << " - Home Page:             " << website << std::endl;
    ut << " - Post/Sted Nr:          " << postnrsted << std::endl;
    ut << " - Phone Number:          " << tlf;
}
