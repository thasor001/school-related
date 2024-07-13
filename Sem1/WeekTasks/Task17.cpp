//
// Created by Tharald on 01/03/2024.
//

#include "fstream"
#include "LesData2.h"
#include "string"


int main() {
    std::ifstream file("C:\\Users\\Tharald\\CLionProjects\\Cpp\\WeekTasks\\Task17.dta");
    std::string line;
    std::string deg;
    std::string date;
    float least = 0;
    float degree;

    char command = lesChar("Min or Max (M/X)");

    if (!file) {
        std::cout << "Error, could not open file." << std::endl;
        return -1;
    }

    while (std::getline(file, line)) {
        if (line.find("Stnr       Dato") != std::string::npos) {
            break;
        }
    }

    while (std::getline(file, line)) {
        if (line.find("18700") != 3) {
            std::cout << "All lines read." << std::endl;
            break;
        }
        size_t pos = line.find("18700");
        line = line.substr(pos + 5);
        size_t space = line.find_first_not_of(" ");
        line = line.substr(space);
        deg = line.substr(10, 11);
        degree = std::stof(deg);
        if (command == 'M') {
            if (degree < least) {
                least = degree;
                date = line.substr(0, 10);
            }
        } else {
            if (degree > least) {
                least = degree;
                date = line.substr(0, 10);
            }
        }
    }

    std::cout << least << "C" << " On day : " << date << std::endl;

    file.close();
    return 0;
}
