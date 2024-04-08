#ifndef __funksjoner_h
#define __funksjoner_h

#include "iostream"
#include "string"
#include "fstream"
#include "Enum.h"


void skrivMeny();
char egenLesChar(std::string && text, std::string && choices);

namespace system_messages {
    void sys_print(const std::string& text);
    void sys_info(const std::string& text);
    void sys_error(const std::string& text);
}

namespace file_functions {
    void init_by(std::ifstream & inn, std::string& cuntry, std::string& city);
    void get_lines(std::ifstream & inn, std::string & text, int t);
    Ktype stringToEnum(const std::string &text);
}

#endif
