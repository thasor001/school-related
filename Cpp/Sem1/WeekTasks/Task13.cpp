//
// Created by Tharald on 21/02/2024.
//

///< See for classes.
#include "Task13.h"
#include <vector>

///< Vectors containing Publication pointers.
std::vector  <Publication*> gPub;

int main() {
    Bok * newBok;
    Magazine * newMag;
    char command = lesChar("Write command ");
    
    while (command != 'Q') {
        switch (command) {
            case 'B':
                newBok = new Bok;
                newBok->readData();
                gPub.push_back(newBok);
                break;
            case 'M':
                newMag = new Magazine;
                newMag->readData();
                gPub.push_back(newMag);
                break;
            case 'W':
                for (auto & val : gPub) {
                    // typeid returns the string length as well in some IDE's like pycharm.
                    std::cout << "\nType : " << typeid((*val)).name() << "\n";
                    val->writeData();
                }
                break;
            default: std::cout << "Illegal command : " << command << "\n"; break;
        }
        
        command = lesChar("Write command ");
    }

    for (auto & val : gPub) {
        delete val;
    }
    gPub.clear();

    std::cout << "\n\t--Program Finished--\n";

    return 0;
}