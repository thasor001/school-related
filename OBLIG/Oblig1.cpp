//
// Created by thara on 1/31/2024.
//

#include <iomanip>
#include "LesData2.h"
#include <string>
#include <vector>
using namespace std;

struct Resturant {
    string name, address, type, eval;
    int diceRoll;
};

vector <Resturant*> gResturants;

void newResturant(Resturant & res);//
void writeAllResturants();//
void writeResturant(const struct Resturant* r);//
void writeMenu();//


int main() {
    Resturant * newRes;

    writeMenu();
    char command = lesChar("Write command ");

    while (command != 'Q') {
        switch (command) {
            case 'N':
                newRes = new Resturant;
                newResturant(*newRes);
                gResturants.push_back(newRes);
                break;
            case 'W':
                writeAllResturants();
                break;
            default:
                cout << "Wrong command : " << command << "\n";
                break;
        }

        command = lesChar("Write command ");
    }

    // Deleting all gResturants
    for (auto Resturant : gResturants) {
        delete Resturant;
    }
    gResturants.clear();

    return 0;
}

void writeMenu() {
    cout << "\n\nN - New \n";
    cout << "W - Write all resturants \n";
    cout << "Q - End program \n";
}

void writeResturant(const struct Resturant* r) {
    cout <<"Name : " << r->name <<"\n";
    cout <<"Address : " << r->address << "\n";
    cout <<"Resturant type : " << r->type << "\n";
    cout <<"Evaluation : " << r->eval << "\n";
    cout <<"Dice Roll : " << r->diceRoll << "\n";
}

void writeAllResturants() {
    for (int i = 0; i < gResturants.size(); i++) {
        writeResturant(gResturants[i]);
    }
}

void newResturant(Resturant & res) {
    cout <<"Name : "; getline(cin, res.name);
    cout <<"Address : "; getline(cin, res.address);
    cout <<"Type : "; getline(cin, res.type);
    cout <<"Evaluation : "; getline(cin, res.eval);
    res.diceRoll = lesInt("Dice Roll : ", 1, 6);
}