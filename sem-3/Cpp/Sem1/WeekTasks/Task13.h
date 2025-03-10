//
// Created by Tharald on 21/02/2024.
//

#ifndef CPP_TASK13_H
#define CPP_TASK13_H

#include "LesData2.h"
#include <string>

class Publication {
private:
    std::string name;
    int year;
public:
    virtual void readData() {
        std::cout << "Write Name : ";
        std::getline(std::cin, name);
        year = lesInt("Write Year of Publication ", 1960, 2024);
    }
    virtual void writeData() const {
        std::cout << "Name : " << name << "\n";
        std::cout << "Year of Release : " << year << "\n";
    }
};

class Bok : public Publication {
private:
    std::string Author;
    std::string ISBN;
    float price;
public:
    void readData() override {
        Publication::readData();
        std::cout << "Author Name : "; std::getline(std::cin, Author);
        std::cout << "ISBN : "; std::getline(std::cin, ISBN);
        price = lesFloat("What is the price $ ", 1, 25);

    }
    void writeData() const override {
        Publication::writeData();
        std::cout << "Author : " << Author << "\n";
        std::cout << "ISBN : " << ISBN << "\n";
        std::cout << "Price $ : " << price << "\n";
    }
};

class Magazine : public Publication {
private:
    int number;
    int weekNumber;
    bool yearSubscription;
public:
    void readData() override {
        Publication::readData();
        number = lesInt("Issue ", 1, 100);
        weekNumber = lesInt("Week Number ", 1, 52);
        yearSubscription = lesInt("Year Subscription ", 0, 1);
    }
    void writeData() const override {
        Publication::writeData();
        std::cout << "Issue Number : " << number << "\n";
        std::cout << "Week Number : " << weekNumber << "\n";
        std::cout << (yearSubscription ? "Yearly sub" : "Not Yearly sub") << "\n";
    }
};



#endif //CPP_TASK13_H
