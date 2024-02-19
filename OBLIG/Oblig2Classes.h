//
// Created by Tharald on 19/02/2024.
//

#ifndef CPP_OBLIG2CLASSES_H
#define CPP_OBLIG2CLASSES_H

#include "LesData2.h"
#include <iostream>
#include <string>
using namespace std;

class Dyr {
private:
    string name;
public:
    Dyr() {name = "";}
    void readName(string name) {this->name = name;}
    void readData() {
        cout << "Name : ";
        getline(cin, name);
    }
    void writeData() {
        cout << "Name : " << name << "\n";
    }
};

class DyrILuft : public Dyr {
private:
    float wingSpan;
public:
    DyrILuft() {
        wingSpan = 0;
        Dyr::readData();
    }
    void readData() {
        wingSpan = lesFloat("Write Wing Span ", 0, 1.44);
    }
    void writeData() {
        Dyr::writeData();
        cout << "Wing span : " << wingSpan << "\n";
    }
};

class Innsekt : public DyrILuft {
private:
    int legs;
public:
    Innsekt() {
        legs = 0;
        DyrILuft::readData();
    }
    void readData() {
        legs = lesInt("How many legs ", 0, 1000);
    }
    void writeData() {
        DyrILuft::writeData();
        cout << "Legs : " << legs << "\n";
    }
};

class Fugl : public DyrILuft {
private:
    int topVelocity;
public:
    Fugl() {
        topVelocity = 0;
        DyrILuft::readData();
    }
    void readData() {
        topVelocity = lesInt("Top Velocity m/s ", 0, 50);
    }
    void writeData() {
        DyrILuft::writeData();
        cout << "Top velocity : " << topVelocity << "\n";
    }
};

class DyrIVann : public Dyr {
private:
    int preferedDepth;
public:
    DyrIVann() {
        preferedDepth = 0;
        Dyr::readData();
    }
    void readData() {
        preferedDepth = lesInt("Which depth does it live at km ", 0, 10);
    }
    void writeData() {
        Dyr::writeData();
        cout << "Prefered depth : " << preferedDepth << "\n";
    }
};

class Fisk : public DyrIVann {
private:
    int fins;
public:
    Fisk() {
        fins = 0;
        DyrIVann::readData();
    }
    Fisk(string name) {Dyr::readName(name);}
    void readData() {
        fins = lesInt("How many fins ", 2, 6);
    }
    void writeData() {
        DyrIVann::writeData();
        cout << "Fins : " << fins << "\n";
    }
};

class Skalldyr : public DyrIVann {
private:
    int legs;
public:
    Skalldyr() {
        legs = 4;
        DyrIVann::readData();
    }
    void readData() {
        legs = lesInt("How many legs ", 4, 10);
    }
    void writeData() {
        DyrIVann::writeData();
        cout << "Legs : " << legs << "\n";
    }
};


#endif //CPP_OBLIG2CLASSES_H
