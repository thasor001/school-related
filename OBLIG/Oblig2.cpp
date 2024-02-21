//
// Created by Tharald on 19/02/2024.
// Finished 20/02/2024.
//

// Header file containing all the classes. and "LesData2", "iostream(inside LesDate2)" and "string".
#include "Oblig2Classes.h"
#include <vector>

void menu() {
    std::cout << "F - Fish " << "\t\tI - Bug \n"
    << "C - Crustacean" << "\t\tB - Bird\n"
    << "Q - End Program " << "\tW - Write All\n\n";
}

///< Vector containing Dyr pointers
std::vector <Dyr*> gDyr;

/**
 * Main program.
 */
int main() {
    // Class pointers for different animals
    Fisk * newFish;
    Innsekt * newBug;
    Fugl * newBird;
    Skalldyr * newCrab;
    std::string name;

    menu();
    char command = lesChar("\nWrite command ");

    while (command != 'Q') {
        switch (command) {
            case 'B':
                // Creating a new instance of Class.
                newBird = new Fugl;
                // Pushing this instance to the back of gDyr vector.
                // This instance can be pushed into a vector with pointers to Dyr even though,
                // it isn't a Dyr class, but it is a subclass of Dyr. The logic goes like this:
                // Fugl != Dyr class, but it's still an "animal".
                gDyr.push_back(newBird);
                break;
            case 'I':
                newBug = new Innsekt;
                gDyr.push_back(newBug);
                break;
            case 'F':
                std::cout << "Name : ";
                getline(std::cin, name);
                // using .empty instead of == '\n' since getline reads until '\n' then removes it,
                // therefore == '\n' wouldn't work since it is not stored in name variable.
                if (name.empty()) {
                    newFish = new Fisk;
                    gDyr.push_back(newFish);
                } else {
                    newFish = new Fisk(name);
                    gDyr.push_back(newFish);
                }
                break;
            case 'C':
                newCrab = new Skalldyr;
                gDyr.push_back(newCrab);
                break;
            case 'W':
                // Go through all gDyr pointers and writeData, this does not just write their name,
                // since the writeData in Dyr class is a virtual and is overridden by the writeData in,
                // the subclasses "Fisk, Fugl, Innsekt and Skalldyr", which means it will run the writeData,
                // of these classes.
                for (auto & dyr : gDyr) {
                    dyr->writeData();
                }
                break;
            default: std::cout << "Illegal Command : " << command << "\n"; break;
        }
        std::cout << "\n| F->Fish | I->Bug | C->Crab | B->Bird | W->Write |";
        command = lesChar("\nWrite command ");
    }

    // Goes through all of gDyr and works with the originals in the vector, then deletes.
    for (auto & val : gDyr) {
        delete val;
    }
    // Finally clears the vector.
    gDyr.clear();
    std::cout << "\n\t--Program Terminated--\n";

    return 0;
}
