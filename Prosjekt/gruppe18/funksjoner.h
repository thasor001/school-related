/**
 *   funksjoner-header
 *
 *   @file     funksjoner.h
 *   @author   Gruppe18
 */

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

/**
 * @Brief Funksjon som finner entydige navn.
 *
 * @tparam P1 typename obj for iterator.
 * @tparam P2 typename obj for iterator.
 * @tparam PRED typename ojb for Predikat.
 * @param p_start Iterator til start av maps.
 * @param p_end Iterator til slutt av maps.
 * @param pred Funksjon.
 * @return Vector med entydige navn.
 */
template <typename P1, typename P2, typename PRED>
std::vector <std::string> for_each_if (P1 p_start, P2 p_end, PRED pred) {
    std::vector <std::string> navn;
    for (; p_start != p_end; p_start++)
        if (pred(p_start->first))
            navn.push_back(p_start->first);
    return navn;
}

/**
 * @Brief Funksjon som sjekker om input er Entydig.
 *
 * @tparam P1 typename obj for iterator.
 * @tparam P2 typename obj for iterator.
 * @param text tekst som skal printes.
 * @param n Navn.
 * @param p_start Iterator til start av maps.
 * @param p_end Iterator til slutt av maps.
 * @return Input navn entydig / ikke entydig.
 */
template<typename P1, typename P2>
bool Entydig(const std::string &text, std::string &n, P1 p_start, P2 p_end) {
    std::cout << "\nSkriv navn paa " << text << " : ";
    std::getline(std::cin, n);
    std::transform(n.begin(), n.end(), n.begin(), ::toupper);

    auto vec = for_each_if(p_start, p_end, [&](auto & val){return val.substr(0, n.size()) == n;});
    if (std::find(vec.begin(), vec.end(), n) != vec.end())
        return true;
    else if (vec.size() == 1) {
        n = vec[0];
        return true;
    } else if (vec.size() > 1)
        std::cout << '\n' << n << " er ikke Entydig\n";
    else
        std::cout << '\n' << n << " finnes ikke\n";
    return false;
}

void init_by(std::ifstream & inn, std::string& country, std::string& city);
void get_lines(std::ifstream & inn, std::string & text, int t);
Ktype stringToEnum(std::string &text);

#endif