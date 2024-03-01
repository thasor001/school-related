//
// Created by Tharald on 01/03/2024.
//

#include "string"
#include "iostream"

int main() {
    std::string test = "19.02 Hello World";
    float number;
    int num;

    num = std::stoi(test.substr(0, 5));
    number = std::stof(test.substr(0, 5)); // 19.02
    std::cout << test.substr(0, 5) << " Number form F : " << number
    << " Number Form I : " << num << std::endl;


    return 0;
}