//
// Created by Tharald on 24/02/2024.
//

#include "Task15.h"
#include <vector>

std::vector <Vehicles*> gVehicles;

int main() {
    Vehicles * newVehicle;
    char command = lesChar("Write command ");

    while (command != 'Q') {
        switch (command) {
            case 'C':
                newVehicle = new Car;
                newVehicle->readData();
                gVehicles.push_back(newVehicle);
                break;
            case 'T':
                newVehicle = new Train;
                newVehicle->readData();
                gVehicles.push_back(newVehicle);
                break;
            default: std::cout << "Illegal command : " << command << "\n"; break;
        }
        command = lesChar("Write command ");
    }

    std::cout << "Amount of Vehicles : " << gVehicles.size() << "\n";
    for (int i = 0; i < gVehicles.size(); i++) {
        gVehicles[i]->display();
        if (gVehicles[i]->empty()) {
            std::string name = typeid(*gVehicles[i]).name();
            std::cout << name.substr(1, -1) << " is empty index : " << i << "\n";
        }
        delete gVehicles[i];
    }

    gVehicles.clear();

    return 0;
}