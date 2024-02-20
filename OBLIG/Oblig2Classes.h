//
// Created by Tharald on 19/02/2024.
// Finished 20/02/2024
//

#ifndef CPP_OBLIG2CLASSES_H
#define CPP_OBLIG2CLASSES_H

#include "LesData2.h"
#include <iostream>
#include <string>

// resource for std::move() : https://stackoverflow.com/questions/3413470/what-is-stdmove-and-when-should-it-be-used
// Its overkill and I am not even sure if it makes the program even one nanosecond faster, but just wanted to try :).
// Changes the variable from "Ivalue" (Named variable) to a "Xvalue" which makes the compiler instead of making a copy,
// of a variable and store that in a new variable, rather swap that old variable into the new one.

/***********************************************************************************************************************
 *  ... Header File with all the classes for "Oblig 2".
 *  ... Wanted to use a module for all the classes but found out that modules aren't well supported in c++.
 *  ... These classes could've been in the main file but i wanted the files to look a little "cleaner" so I,
 *  ... Opted to split the program, and just have the main functionality in the main file and fillers such,
 *  ... as classes which will clutter the screen and make you have to scroll down in a separate file.
 **********************************************************************************************************************/

/**
 * Dyr class.
 *
 * Parent class for all other classes.
 */
class Dyr {
private:
    std::string name;

public:
    // Constructors.
    Dyr() {name = "";}
    Dyr(std::string name) {this->name = std::move(name);}

    // No need to make this virtual as it does not need to be overridden later (not used in main program).
    void readData() {
        std::cout << "Name : ";
        getline(std::cin, name);
    }

    // Virtual function since it will be later overridden by writeData to subclasses.
    virtual void writeData() const {
        std::cout << "\n\nName : " << name << "\n";
    }
};

/**
 * DyrILuft class.
 *
 * sub class of Dyr.
 * Parent class of Fugl and Innsekt classes.
 */
class DyrILuft : public Dyr {
private:
    float wingSpan;

public:
    // Constructor.
    DyrILuft() {wingSpan = 0; Dyr::readData();}

    /**
     * Read and writeData. Reads and writes data :)!
     * Will be basically the same for every class.
     */
    void readData() {wingSpan = lesFloat("Write Wing Span ", 0, 1.5);}

    void writeData() const {
        Dyr::writeData();
        std::cout << "Wing span : " << wingSpan << "\n";
    }
};

/**
 * Innsekt class.
 *
 * sub class of DyrILuft.
 */
class Innsekt : public DyrILuft {
private:
    int legs;

public:
    // Constructor.
    Innsekt() {DyrILuft::readData(); Innsekt::readData();}

    void readData() {legs = lesInt("How many legs ", 0, 1000);}

    // Override as it overrides the virtual function to the parent class.
    void writeData() const override {
        DyrILuft::writeData();
        std::cout << "Legs : " << legs << "\n";
    }
};

/**
 * Fugl class.
 *
 * sub class of DyrILuft.
 */
class Fugl : public DyrILuft {
private:
    int topVelocity;

public:
    // Constructor.
    Fugl() {DyrILuft::readData(); Fugl::readData();}

    void readData() {topVelocity = lesInt("Top Velocity m/s ", 0, 50);}

    // Override as it overrides the virtual function to the parent class.
    void writeData() const override {
        DyrILuft::writeData();
        std::cout << "Top velocity : " << topVelocity << "\n";
    }
};

/**
 * DyrIVann class.
 *
 * sub class of Dyr.
 * Parent class of Fisk and Skalldyr.
 */
class DyrIVann : public Dyr {
private:
    int preferedDepth;

public:
    // Constructor.
    DyrIVann() {preferedDepth = 0; Dyr::readData();}
    DyrIVann(std::string n) : Dyr(std::move(n)) {
        Dyr::writeData();
        DyrIVann::readData();
    }

    void readData() {preferedDepth = lesInt("Which depth does it live at km ", 0, 10);}

    void writeData() const {
        Dyr::writeData();
        std::cout << "Prefered depth : " << preferedDepth << "\n";
    }
};

/**
 * Fisk class.
 *
 * sub class of DyrIVann.
 */
class Fisk : public DyrIVann {
private:
    int fins;

public:
    // Constructors.
    Fisk() {DyrIVann::readData(); Fisk::readData();}
    Fisk(std::string n) : DyrIVann(std::move(n)) {Fisk::readData();}

    void readData() {fins = lesInt("How many fins ", 2, 6);}

    // Override as it overrides the virtual function to the parent class.
    void writeData() const override {
        DyrIVann::writeData();
        std::cout << "Fins : " << fins << "\n";
    }
};

/**
 * Skalldyr class.
 *
 * sub class of DyrIVann.
 */
class Skalldyr : public DyrIVann {
private:
    int legs;

public:
    // Constructor.
    Skalldyr() {DyrIVann::readData(); Skalldyr::readData();}

    void readData() {legs = lesInt("How many legs ", 4, 10);}

    // Override as it overrides the virtual function to the parent class.
    void writeData() const override {
        DyrIVann::writeData();
        std::cout << "Legs : " << legs << "\n";
    }
};

#endif //CPP_OBLIG2CLASSES_H