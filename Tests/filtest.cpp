//
// Created by Tharald on 25/02/2024.
//
#include "LesData2.h"
#include <fstream>
#include <string>
#include <vector>

std::vector <float*> numbers;
std::vector <std::string>* text;

int main() {
    std::ifstream file("C:/Users/Tharald/CLionProjects/Cpp/Tests/test.dta");
    std::vector <bool> check;
    std::string placeholder;

    if (!file) {
        std::cout << "File did not open" << std::endl;
        return -1;
    }
    text = new std::vector <std::string>;
    for (int i = 0; i < 2; i++) {
        std::getline(file, placeholder);
        text->push_back(placeholder);
        std::cout << (*text)[i] << std::endl;
    }

    std::getline(file, placeholder);
    std::istringstream line(placeholder);
    float * newFloat;
    float numb;

    while (line >> numb) {
        newFloat = new float;
        (*newFloat) = numb;
        numbers.push_back(newFloat);
    }
    std::cout << "\nNumebrs Read : " << std::endl;

    for (auto & val : numbers) {
        std::cout << (*val) << " ";
    }
    std::cout << std::endl;

    file.close();

    return 0;
}

