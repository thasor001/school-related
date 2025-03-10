/**
 * Funksjoner til Turoperator klasse.
 *
 * @File Turoperator.cpp
 */

#include "Opplegg.h"
#include "Turoperator.h"

Opplegg gOppleggsBase; ///< Opplegg objekt.

/**
 * @See get_liens()
 *
 * @param inn Referance til fil objekt.
 * @param navn Navn til Turoperator.
 */
Turoperator::Turoperator(std::ifstream &inn, std::string& navn) {
    std::string buffer;
    this->navn = navn;

    inn >> turopplegg; inn.ignore();

    get_lines(inn, gateadresse, 8);
    get_lines(inn, kontaktpers, 8);
    get_lines(inn, mail, 9);
    get_lines(inn, website, 13);
    get_lines(inn, postnrsted, 10);

    inn >> buffer >> buffer >> buffer >> tlf;
    inn.ignore();
}

/**
 * @Brief constructor som leser til Turoperator.
 *
 * @param navn Navn til Turoperator.
 */
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

/**
 * @Brief Brukes for aa sende variabler videre til nyttOpplegg.
 *
 * @See Opplegg::nyttOpplegg()
 */
void Turoperator::nyttOpplegg() {
    gOppleggsBase.nyttOpplegg(navn, turopplegg);
}

/**
 * @Brief Brukes til aa endre data til Turoperator.
 *
 * @See egenLesChar()
 * @See Turoperator::skrivData()
 */
void Turoperator::endreData() {
    char valg;
    std::string name;
    std::cout << "\nQ = Quit ";

    std::cout << "\n|P - PostNr   |\n"
                 "|S - Sted     |\n"
                 "|K - KontPers |\n"
                 "|G - GateAdr  |\n"
                 "|M - Mail     |\n"
                 "|W - Webiste  |\n";

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
    std::cout << "\nNy Tur Opperator :\n";
    std::cout << "\n\t" + navn + "\t";
    Turoperator::skrivData();
}

/**
 * @Brief Brukes til aa gi en brief om en Turoperator.
 */
void Turoperator::skrivEn() const {
    std::cout << "\tNavn : " << navn;
    std::cout << "\t\t" << turopplegg << " : Opplegg";
    std::cout << "\tEmail : " << mail << std::endl;
}

/**
 * @Brief Skriver detaljert all sin data.
 */
void Turoperator::skrivData() const {
    std::cout << "\n\t" + navn + "\t";
    std::cout << "\t" << turopplegg << " Opplegg\t" << website << std::endl;
    std::cout << "\t" << gateadresse << ", " << postnrsted << std::endl;
    std::cout << "\t" << kontaktpers << ", "
    << tlf << ", " << mail << std::endl;
}

/**
 * @param ut Referance til fil objekt.
 */
void Turoperator::skrivTilFil(std::ofstream &ut) const {
    ut << turopplegg << std::endl;
    ut << " - Street Address:        " << gateadresse << std::endl;
    ut << " - Contact Person:        " << kontaktpers << std::endl;
    ut << " - Email Address:         " << mail << std::endl;
    ut << " - Home Page:             " << website << std::endl;
    ut << " - Post/Sted Nr:          " << postnrsted << std::endl;
    ut << " - Phone Number:          " << tlf;
}