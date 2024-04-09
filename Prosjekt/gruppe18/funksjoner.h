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

template <typename P1, typename P2, typename PRED>
std::vector <std::string> for_if (P1 p_start, P2 p_end, PRED pred) {
    std::vector <std::string> navn;
    for (; p_start != p_end; p_start++)
        if (pred((*p_start))) {
            navn.push_back(p_start->first);
        }
    return navn;
}

// Template Funksjoner skal være i header filer.
template<typename P1, typename P2>
bool Entydig(const std::string &text, std::string &n, P1 p_start, P2 p_end) {
    std::cout << "\nSkriv navn paa " << text << " : ";
    std::getline(std::cin, n);
    std::transform(n.begin(), n.end(), n.begin(), ::toupper);

    auto vec = for_if(p_start, p_end, [&](auto & pair){return pair.first.substr(0, n.size()) == n;});
    if (std::find(vec.begin(), vec.end(), n) != vec.end())
        return true;
    else if (vec.size() == 1) {
        n = vec[0];
        return true;
    } else if (vec.size() > 1) {
        std::cout << '\n' << n << " er ikke Entydig\n";
        return false;
    } else {
        std::cout << '\n' << n << " finnes ikke\n";
        return false;
    }
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
