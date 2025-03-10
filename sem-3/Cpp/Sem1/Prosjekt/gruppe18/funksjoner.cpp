/**
 * Fil med funksjoner brukt flere steder i programmet.
 *
 * @File funksjoner.cpp
 */

#include "map"
#include <iomanip>
#include <algorithm>
#include "funksjoner.h"

/**
 * NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!
 *
 * Template funksjoner skrevet i header fil. (siden de maa vaere der :D)
 * Aka gaa i funksjoner.h for aa see Entydig funksjon.
 *
 * NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!NB!
 */


/**
 * @Brief Skriver meny.
 */
void skrivMeny() {
    std::cout << std::setw(3)
              << "--------Meny----------\n"
                 "T A       - Skriver alle Turoperatorene\n"
                 "T 1       - Skriver alt om en Turoperator\n"
                 "T N       - Ny Turoperator\n"
                 "T E*      - Endre noe om en Turoperator\n"
                 "T O       - Lag Opplegg for en Turoperator\n"
                 "T F       - Fjern / Slett en Turoperator\n\n"
                 "B A       - Skriv alle Byer\n"
                 "B 1       - Skriv alt om en By\n"
                 "B N       - Ny By\n"
                 "B F       - Fjern/Slett en By\n\n"
                 "A N       - Ny Atteraksjon i en by\n"
                 "A F       - Fjern/Slett en Atteraksjon i en by\n\n"
                 "Q         - Quit/Avslutt\n";
}

/**
 * @Brief egen les char funksjon.
 *
 * @param text Text som skal bli printet.
 * @param choices String som inneholder valg muligheter for innlesning av char.
 * @return toUpper(char) som er innenfor "choices" string + 'Q'
 */
char egenLesChar(const std::string & text, std::string && choices) {
    char c;
    std::transform(choices.begin(), choices.end(), choices.begin(), ::toupper);

    do {
        if (choices.find('Q') == std::string::npos)
            std::cout << "\n" << text << " (" + choices << ") : ";
        std::cin >> c;
        c = toupper(c);
        std::cin.ignore();
    } while (choices.find(c) == std::string::npos && c != 'Q');

    return c;
}

/**
 * @Brief Funksjon som leser inn navn paa by og land.
 *
 * @param inn Referance til fil objekt.
 * @param land lvalue string.
 * @param by lvalue string.
 */
void init_by(std::ifstream & inn, std::string& land, std::string &by) {
    std::string buffer;
    inn >> buffer >> by; by.pop_back();
    inn >> land; inn.ignore();
}

/**
 * @Brief funksjon som henter linjer og ignorerer " "'s.
 *
 * @param inn Referance til fil objekt.
 * @param land lvalue string
 * @param t antall " " som skal ignoreres.
 */
void get_lines(std::ifstream & inn, std::string & land, int t) {
    std::string buffer;
    inn >> buffer >> buffer >> buffer; inn.ignore(t);
    std::getline(inn, land);
}

/**
 * @Brief Funksjon som gjør fil/user input text til enum type.
 *
 * @param text User input
 * @return Kirke enum type.
 */
Ktype stringToEnum(std::string &text) {
    std::transform(text.begin(), text.end(), text.begin(), ::toupper);

    std::map <std::string, Ktype> enum_map = {
            {"KATEDRAL", katedral},
            {"KIRKE", kirke},
            {"KAPELL", kapell}
    };
    return enum_map[text];
}