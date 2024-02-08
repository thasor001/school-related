//
// Created by Tharald Roland Søresnsen on 2/6/2024.
//

#include <iomanip>
#include "LesData2.h"
#include <string>
#include <vector>
using namespace std;

struct Restaurant {
    string name, address, type, eval;
    int diceRoll;
};

vector <Restaurant*> gRestaurants;

void newRestaurant(Restaurant & res);//
void writeAllRestaurants();//
void writeRestaurant(const struct Restaurant* r);//
void writeMenu();//

/**
 * Main program
 */
int main() {
    Restaurant * newRes;

    writeMenu();
    char command = lesChar("Write command ");

    while (command != 'Q') {
        switch (command) {
            case 'N':
                // Creating new Restaurant here instead of in new function.
                newRes = new Restaurant;
                newRestaurant(*newRes);
                gRestaurants.push_back(newRes);
                break;
            case 'W':
                writeAllRestaurants();
                break;
            default:
                cout << "Wrong command : " << command << "\n";
                break;
        }
        cout << "\nN - W - Q\n";
        command = lesChar("Write command ");
    }

    // Deleting all gRestaurants and pointers inside.
    // did it here instead of in a new function since I think this is cleaner,
    // and it wasn't specified that we needed to use every function.
    for (auto Restaurant : gRestaurants) {
        delete Restaurant;
    }
    gRestaurants.clear();

    cout << "\nCode finished\n";

    return 0;
}

/**
 * Write Menu
 */
void writeMenu() {
    cout << "\n\nN - New \n";
    cout << "W - Write all restaurants \n";
    cout << "Q - End program \n";
}

/**
 * Print elements of one struct.
 * @param r
 */
void writeRestaurant(const struct Restaurant* r) {
    cout <<"Name : " << r->name <<"\n";
    cout <<"Address : " << r->address << "\n";
    cout <<"Resturant type : " << r->type << "\n";
    cout <<"Evaluation : " << r->eval << "\n";
    cout <<"Dice Roll : " << r->diceRoll << "\n";
}

/**
 * Goes through all Restaurants and uses writeRestaurant() to print all elements.
 */
void writeAllRestaurants() {
    for (auto & gRestaurant : gRestaurants) {
        writeRestaurant(gRestaurant);
    }
}

/**
 * Assigns data members for every variable in the new struct.
 * @param res
 */
void newRestaurant(Restaurant & res) {
    cout <<"Name : "; getline(cin, res.name);
    cout <<"Address : "; getline(cin, res.address);
    cout <<"Type : "; getline(cin, res.type);
    cout <<"Evaluation : "; getline(cin, res.eval);
    res.diceRoll = lesInt("Dice Roll : ", 1, 6);
}