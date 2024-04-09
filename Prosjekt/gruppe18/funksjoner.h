#ifndef __funksjoner_h
#define __funksjoner_h

#include <list>
#include <vector>
#include "string"
#include "Enum.h"
#include "fstream"
#include "iostream"
#include "algorithm"
#include "Attraksjon.h"

void skrivMeny();
char egenLesChar(const std::string & text, std::string && choices);


// Template Funksjoner skal være i header filer.
template<typename P1, typename P2>
bool Entydig(const std::string & text, std::string & navn, P1 p_start, P2 p_end) {
    std::cout << "\nSkriv navn paa " << text << " : ";
    std::getline(std::cin, navn);
    std::transform(navn.begin(), navn.end(), navn.begin(), ::toupper);
    std::string original = navn;
    int count = 0;

    for (auto it = p_start; it != p_end; it++) {
        if (it->first.substr(0, original.size()) == original) {
            navn = it->first; count++;
            if (it->first == original)
                return true;
        }
    }

    if (count > 1) {
        std::cout << "\n" + original + " er ikke Entydig\n\n";
        return false;
    }

    auto predicate = [&](const auto & pair){return pair.first == navn;};
    auto it = std::find_if(p_start, p_end, predicate);

    if (it == p_end) {
        std::cout << "\n" + original + " Finnes ikke\n\n";
        return false;
    }

    return true;
}

namespace system_messages {
    void sys_print(const std::string& text);
    void sys_info(const std::string& text);
    void sys_error(const std::string& text);
}

namespace file_functions {
    void init_by(std::ifstream & inn, std::string& country, std::string& city);
    void get_lines(std::ifstream & inn, std::string & text, int t);
    Ktype stringToEnum(const std::string &text);
}

#endif
