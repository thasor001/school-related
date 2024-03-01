//
// Created by Tharald on 24/02/2024.
//

#ifndef CPP_TASK16_H
#define CPP_TASK16_H

#include <string>
#include "iostream"
#include "fstream"

class Publications {
private:
    std::string title;
    float price;
public:
    Publications(std::ifstream & in) {
        in >> price;
        in.ignore();
        std::getline(in, title);
    }
    virtual void writeToFile(std::ofstream & out) {
        out << price << " " << title << std::endl;
    }
};

class Bok : public Publications {
private:
    std::string author;
    int pages;
public:
    Bok(std::ifstream & in) : Publications(in) {
        in >> pages;
        in.ignore();
        std::getline(in, author);
    }

    void writeToFile(std::ofstream & out) override {
        out << "B ";
        Publications::writeToFile(out);
        out << pages << " " << author << std::endl;
    }
};

class Magazine : public Publications {
private:
    int year, volume;
public:
    Magazine(std::ifstream & in) : Publications(in) {
        in >> year >> volume;
        in.ignore();
    }
    void writeToFile(std::ofstream & out) override {
        out << "M ";
        Publications::writeToFile(out);
        out << year << " " << volume << std::endl;

    }
};

#endif //CPP_TASK16_H
