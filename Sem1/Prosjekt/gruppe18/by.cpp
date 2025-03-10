/**
 * Funksjoner for by objekt
 *
 * @File by.cpp
 */

#include "By.h"
#include "Kirke.h"
#include "LesData3.h"
#include "Severdighet.h"
#include "MuseumGalleri.h"

/**
 * @Brief Leser inn type attraksjon til den ikke finner '-' mer.
 *
 * @param navn Land sitt navn.
 * @param inn Referance til fil objekt.
 */
By::By(std::string& navn, std::ifstream &inn) {
    land = navn;

    char buffer, type;

    do {
        inn >> buffer >> type;

        switch (type) {
            case 'K': Attraksjoner.push_back(new Kirke(inn));         break;
            case 'M': Attraksjoner.push_back(new MuseumGalleri(inn)); break;
            case 'S': Attraksjoner.push_back(new Severdighet(inn));   break;
            case 'i':                                                return;
            case 'N': inn >> buffer;                                 return;
            default: std::cout << "\n--wrong file Structure--\n";    return;
        }
    } while (buffer == '-');
}

/**
 * @Brief Defualt constructor som leser til by.
 */
By::By() {
    std::cout << "\nSkriv Navn Paa Land : ";
    std::getline(std::cin, land);
}

/**
 * @Breif Free-er memory og sletter pekere.
 */
By::~By() {
    for (auto & val : Attraksjoner)
        delete val;
    Attraksjoner.clear();
}

/**
 * @Brief Brukes for aa gi tilgang til Attraksjoner list i opperatorer.
 *
 * @return Referance til Attraksjoner list.
 */
std::list <Attraksjon*>& By::getList() {
    return Attraksjoner;
}

/**
 * @param ut Referance til fil objekt.
 *
 * @See Attraksjoner/Sub klasser::skrivTilFil()
 */
void By::skrivTilFil(std::ofstream &ut) const {
    ut << land << std::endl;
    for (const auto & val : Attraksjoner) {
        ut << "\t- ";
        val->skrivTilFil(ut);
    }
}

/**
 * @Brief Brukes til aa gi en brief om en by.
 */
void By::skrivEn() const {
    std::cout << "\t\tLand : " << land;
    std::cout << "\t Ant Attraksjoner : ";
    std::cout << Attraksjoner.size() << std::endl;
}

/**
 * @Brief Brukes til aa gi en detaljert beskrivelse av by og attraksjoner.
 *
 * @See Attraksjoner/Sub klasser::skrivData()
 */
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

/**
 * @Brief Legger til ny attraksjon i Attraksjoner list.
 *
 * @See egenLesChar()
 */
void By::nyAttraksjon() {
    char type = egenLesChar("Skriv Type Attraksjon", "KSM");

    switch (type) {
        case 'K': Attraksjoner.push_back(new Kirke);                 break;
        case 'S': Attraksjoner.push_back(new Severdighet);           break;
        case 'M': Attraksjoner.push_back(new MuseumGalleri);         break;
    }
}

/**
 * @Brief Brukes til aa Slette Attraksjon i by.
 *
 * @See lesInt()
 */
void By::slettAttraksjon() {
    if (!Attraksjoner.empty()) {
        std::cout << "0 = ingen" << std::endl;
        int valg = lesInt("Velg Fra Nummer ", 0, Attraksjoner.size());

        if (valg == 0) {
            std::cout << "Ingen Slettet" << std::endl;
            return;
        }

        auto it = Attraksjoner.rend();
        std::prev(it, valg);

        Attraksjoner.erase(it.base());
    } else
        std::cout << "\nIngen Attraksjoner\n";
}