//
// Created by Tharald on 1/30/2024.
//

#include <iomanip>
#include "LesData2.h"
#include <string>
#include <vector>
using namespace std;

struct Fights {
    string home, away;
    int homePoints, awayPoints;
};

void readData(struct Fights & f);
void writeData(const struct Fights * f);

vector <Fights*> gFights;

int main() {
    Fights * newFight;
    char command;

    do {
        command = lesChar("Write command ");
        if (command == 'N') {
            newFight = new Fights;
            readData(*newFight);
            gFights.push_back(newFight);
        } else {
            if (command != 'Q') {
                cout << "Wrong command : " << command << "\n";
            }
        }


    } while (command != 'Q');

    for (int i = 0; i < gFights.size(); i++) {
        writeData(gFights[i]);
    }

    for (int i = 0; i < gFights.size(); i++) {
        delete gFights[i];
    }
    gFights.clear();

    return 0;
}

void readData(struct Fights & f) {
    cout << "Home : ";
    getline(cin, f.home);
    cout << "Away : ";
    getline(cin, f.away);
    f.homePoints = lesInt("Home Points \n", 0, 20);
    f.awayPoints = lesInt("Away Poitns \n", 0, 20);
}

void writeData(const struct Fights * f) {
    cout << "Home : " << f->home << "\n";
    cout << "Away : " << f->away << "\n";
    cout << "Home Points : " << f->homePoints << "\n";
    cout << "Away Points : " << f->awayPoints << "\n";
}