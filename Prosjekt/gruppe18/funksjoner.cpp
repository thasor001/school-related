#include "funksjoner.h"
#include "windows.h"
#include <iomanip>
#include "Byer.h"
#include "map"
#include "algorithm"
namespace sm = system_messages;

// For changing Text Color in terminal.
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void skrivMeny(){
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

char egenLesChar(std::string && text, std::string && choices) {
    char c;
    std::transform(choices.begin(), choices.end(), choices.begin(), ::toupper);

    do {
        if (choices.find('Q') == std::string::npos) {
            SetConsoleTextAttribute(h, 10);
            std::cout << "\n" << text << " (" + choices << ") : ";
            SetConsoleTextAttribute(h, 15);
        }
        std::cin >> c;
        c = toupper(c);
        std::cin.ignore();
    } while (choices.find(c) == std::string::npos && c != 'Q');

    return c;
}

namespace system_messages {

    void sys_print(const std::string& text) {
        SetConsoleTextAttribute(h, 2);
        std::cout << "\nSystem Message : --" << text << "--\n" << std::endl;
        SetConsoleTextAttribute(h, 15);
    }

    void sys_info(const std::string& text) {
        SetConsoleTextAttribute(h, 3);
        std::cout << text << " ";
        SetConsoleTextAttribute(h, 15);
    }

    void sys_error(const std::string& text) {
        SetConsoleTextAttribute(h, 4);
        std::cout << "\nSystem Message : --" << text << "--\n" << std::endl;
        SetConsoleTextAttribute(h, 15);
    }

}

namespace file_functions {
    void init_by(std::ifstream & inn, std::string& country, std::string &city) {
        std::string buffer;
        inn >> buffer >> city; city.pop_back();
        inn >> country; inn.ignore();
    }

    void get_lines(std::ifstream & inn, std::string & text, int t) {
        std::string buffer;
        inn >> buffer >> buffer >> buffer; inn.ignore(t);
        std::getline(inn, text);
    }

    Ktype stringToEnum(const std::string &text) {
        std::map <std::string, Ktype> enum_map = {
                {"Katedral", katedral},
                {"Kirke", kirke},
                {"Kapell", kapell}
        };
        return enum_map[text];
    }
}