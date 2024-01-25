//
// Created by Tharald on 25/01/2024.
//

#include <iomanip>
#include "LesData2.h"
#include <string>
using namespace std;


struct Time {
    int hour,
    min,
    sec;
};

void read(string & s);
void read(Time & t);
void write(const Time & t);


int main() {

    string str[3];
    struct Time t[3];

    for (int i = 0; i < 3; i++) {
        read(str[i]);
    }

    for (int i = 0; i < 3; i++) {
        read(t[i]);
    }

    for (int i = 0; i < 3; i++) {
        cout << str[i] << "\n";
    }

    for (int i = 0; i < 3; ++i) {
        write(t[i]);
    }


    return 0;
}

void read(string & s) {
    do {
        cout << "\nWrite Shit : ";
        getline(cin, s);
    } while (s == "\0");
}

void read(Time & t) {
    t.hour = lesInt("Write Hour ", 0, 24);
    t.min = lesInt("Write Minute ", 0, 59);
    t.sec = lesInt("Write sec ", 0, 59);
}

void write(const Time & t) {
    cout << ((t.hour < 10) ? "0" : "") << t.hour << ":"
    << ((t.min < 10) ? "0" : "") << t.min << ":"
    << ((t.sec < 10) ? "0" : "") << t.sec << "\n";
}
