//
// Created by Tharald on 24/02/2024.
//

#ifndef CPP_TASK15_H
#define CPP_TASK15_H

#include "LesData2.h"
#include <string>

class Vehicles {
private:
    std::string registerNumber;
public:
    Vehicles() {registerNumber = "";}

    virtual void readData() {
        std::cout << "Register Number : ";
        std::getline(std::cin, registerNumber);
    }
    virtual void display() const {
        std::cout << "Register Number : " << registerNumber << "\n";
    }
    virtual bool empty() {return false;}
};

class Car : public Vehicles {
private:
    int passengers;
public:
    Car() : Vehicles() {passengers = 0;}

    void readData() override {
        Vehicles::readData();
        passengers = lesInt("How many passengers ", 0, 6);
    }
    void display() const override {
        Vehicles::display();
        std::cout << "Number of passengers : " << passengers << "\n";
    }
    bool empty() override {
        return (passengers == 0);
    }
};

class Train : public Vehicles {
private:
    float load;
public:
    Train() : Vehicles() {load = 0.0;}

    void readData() override {
        Vehicles::readData();
        load = lesFloat("How much weight ", 0, 100);
    }
    void display() const override {
        Vehicles::display();
        std::cout << "Weight : " << load << "\n";
    }
    bool empty() override {
        return (load == 0);
    }
};


#endif //CPP_TASK15_H
