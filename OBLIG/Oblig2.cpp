//
// Created by Tharald on 19/02/2024.
//

#include "LesData2.h"
#include "Oblig2Classes.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void menu() {
    cout << "V - DyrUnderVann " << "\tL - DyrILuft\n"
    << "V->F - Fish " << "\t\tL->I - Bug \n"
    << "V->C - Crustacean" << "\tL->B - Bird\n"
    << "Q - End Program " << "\tW - Write All\n\n";
}



int main() {
    Fisk * newFish;
    Innsekt * newBug;
    Fugl * newBird;
    Skalldyr * newCrab;

    menu();
    char command = lesChar("Write command ");

    while (command != 'Q') {
        switch (command) {
            case 'V':
                command = lesChar("Fish or Crab (F/C) ");
                switch (command) {
                    case 'F':

                        break;
                    case 'C':

                        break;
                }
                break;
            case 'L':
                command = lesChar("Bird or Bug (B/I) ");
                switch (command) {
                    case 'B':

                        break;
                    case 'I':

                        break;
                }
            default:
                cout << "Illegal Command : " << command << "\n";
                break;
        }

        command = lesChar("Write command ");
    }

    return 0;
}