//
// Created by Tharald on 19/02/2024.
//

#ifndef CPP_OBLIG2CLASSES_H
#define CPP_OBLIG2CLASSES_H

#include "LesData2.h"
#include <iostream>
#include <string>

// resource for std::move() : https://stackoverflow.com/questions/3413470/what-is-stdmove-and-when-should-it-be-used

class Dyr {
private:
    std::string name;

public:
    Dyr() {name = "";}
    Dyr(std::string name) {this->name = name;}

    void readData() {
        std::cout << "Name : ";
        getline(std::cin, name);
    }

    virtual void writeData() const {
        std::cout << "\n\nName : " << name << "\n";
    }
};

class DyrILuft : public Dyr {
private:
    float wingSpan;

public:
    DyrILuft() {wingSpan = 0; Dyr::readData();}

    void readData() {
        wingSpan = lesFloat("Write Wing Span ", 0, 1.44);
    }

    void writeData() const {
        Dyr::writeData();
        std::cout << "Wing span : " << wingSpan << "\n";
    }
};

class Innsekt : public DyrILuft {
private:
    int legs;

public:
    Innsekt() {legs = 0; DyrILuft::readData();}

    void readData() {
        legs = lesInt("How many legs ", 0, 1000);
    }

    void writeData() const override {
        DyrILuft::writeData();
        std::cout << "Legs : " << legs << "\n";
    }
};

class Fugl : public DyrILuft {
private:
    int topVelocity;

public:
    Fugl() {topVelocity = 0; DyrILuft::readData();}

    void readData() {
        topVelocity = lesInt("Top Velocity m/s ", 0, 50);
    }

    void writeData() const override {
        DyrILuft::writeData();
        std::cout << "Top velocity : " << topVelocity << "\n";
    }
};

class DyrIVann : public Dyr {
private:
    int preferedDepth;

public:
    DyrIVann() {preferedDepth = 0; Dyr::readData();}
    DyrIVann(std::string n) : Dyr(std::move(n)) {
        Dyr::writeData();
        DyrIVann::readData();
    }

    void readData() {
        preferedDepth = lesInt("Which depth does it live at km ", 0, 10);
    }

    void writeData() const {
        Dyr::writeData();
        std::cout << "Prefered depth : " << preferedDepth << "\n";
    }
};

class Fisk : public DyrIVann {
private:
    int fins;

public:
    Fisk() {fins = 2; DyrIVann::readData();}
    Fisk(std::string n) : DyrIVann(std::move(n)) {Fisk::readData();}

    void readData() {
        fins = lesInt("How many fins ", 2, 6);
    }

    void writeData() const override {
        DyrIVann::writeData();
        std::cout << "Fins : " << fins << "\n";
    }
};

class Skalldyr : public DyrIVann {
private:
    int legs;

public:
    Skalldyr() {legs = 4; DyrIVann::readData();}

    void readData() {
        legs = lesInt("How many legs ", 4, 10);
    }

    void writeData() const override {
        DyrIVann::writeData();
        std::cout << "Legs : " << legs << "\n";
    }
};

#endif //CPP_OBLIG2CLASSES_H