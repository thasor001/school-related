//
// Created by Tharald on 2/14/2024.
//
#include <iostream>
#include <string>
#include <vector>
#include "LesData2.h"
using namespace std;

class Position {
public:
    int degree, minute, second;
    char direction;
private:
    Position() {
        degree = minute = second = 0;
        direction = ' ';
    }
    void readData(int degree, char dir1, char dir2) {
        this->degree = 0-degree;
        direction = dir1;
    }
    void writeData() const {
        cout << degree << "º" << minute << "'"
        << second << "'' " << direction << "\n";
    }
};
