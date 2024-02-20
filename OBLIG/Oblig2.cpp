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
    cout << "F - Fish " << "\t\tI - Bug \n"
    << "C - Crustacean" << "\t\tB - Bird\n"
    << "Q - End Program " << "\tW - Write All\n\n";
}

vector <Dyr*> gDyr;

int main() {
    Fisk * newFish;
    Innsekt * newBug;
    Fugl * newBird;
    Skalldyr * newCrab;
    string name;

    menu();
    char command = lesChar("\nWrite command ");

    while (command != 'Q') {
        switch (command) {
            case 'B':
                newBird = new Fugl;
                gDyr.push_back(newBird);
                break;
            case 'I':
                newBug = new Innsekt;
                gDyr.push_back(newBug);
                break;
            case 'F':
                cout << "Name : "; getline(cin, name);
                if (name != "\n") {
                    newFish = new Fisk(name);
                    gDyr.push_back(newFish);
                } else {
                    newFish = new Fisk;
                    gDyr.push_back(newFish);
                }
                break;
            case 'C':
                newCrab = new Skalldyr;
                gDyr.push_back(newCrab);
                break;
            case 'W':
                for (auto & dyr : gDyr) {
                    dyr->writeData();
                }
                break;
            default: cout << "Illegal Command : " << command << "\n"; break;
        }
        cout << "\nF->Fish ; I->Bug ; C->Crab ; B->Brid ; W->Write";
        command = lesChar("\nWrite command ");
    }

    for (auto & val : gDyr) {
        delete val;
    }
    gDyr.clear();
    cout << "\n\t--Program Terminated--\n";

    return 0;
}
