//
// Created by Tharald on 02/03/2024.
//

#include "LesData2.h"
#include "string"
#include "fstream"

char command = lesChar("Min or Max? (M/X) ");
float current;
float TA = 0;
size_t space;
std::string date;

void linemanip(std::string & l, const char & c) {
    switch (c) {
        case 'M':
            space = l.substr(30).find_first_not_of(" ");
            current = std::stof(l.substr(30 + space, 11 - space));
            if (current < TA) {
                TA = current;
                date = l.substr(9, 10);
            }
            break;
        case 'X':
            space = l.substr(41).find_first_not_of(" ");
            current = std::stof(l.substr(41 + space, 11 - space));
            if (current > TA) {
                TA = current;
                date = l.substr(9, 10);
            }
            break;
    }
}

int main() {
    std::ifstream file("C:\\Users\\Tharald\\CLionProjects\\Cpp\\WeekTasks\\Task17.dta");
    std::string line;
    std::string condition;

    condition = std::to_string(lesInt("Which date ", 0, 12));
    if (condition.length() == 1) {
        condition = '0' + condition;
    }

    if (!file) {
        std::cout << "File could not be opened" << std::endl;
        return -1;
    }

    while(std::getline(file, line)) {
        if (line.find("Stnr       Dato") != std::string::npos) {
            break;
        }
    }

    int i = 0;
    while(std::getline(file, line)) {
        if (i == 0) {
            space = line.substr(30).find_first_not_of(" ");
            TA = std::stof(line.substr(30 + space, 11 - space));
        }
        if (line.find("18700") == std::string::npos) {
            std::cout << "All lines read. " << std::endl;
            break;
        }
        i++;
        if (condition == "00") {
            linemanip(line, command);
        } else {
            if (line.substr(12, 2) == condition) {
                linemanip(line, command);
            }
        }
    }

    std::cout << std::endl << "Month : " << (condition == "00" ? "All" : condition) << std::endl
    << (command == 'M' ? "Min " : "Max ") << "Temperature : " << TA << "C On Date : " << date
    << std::endl << i << " lines read";

    file.close();
    return 0;
}
