//
// Created by Tharald on 13/02/2024.
//

#include <iostream>
#include <string>
#include <vector>
#include "LesData2.h"
using namespace std;

class Date {
private:
     int day, month, year;

public:
    Date() {
        day = month = 1, year = 2000;
    }

    Date(int day, int month, int year) {
        this->day = day, this->month = month, this->year = year;
    }

    bool sameYear(const Date date) {
        return year==date.year;
    }

    bool sameDay(const Date date) {
        return (date.day==day) && (date.month==month);
    }

    bool earlier(const Date date) {
         return (date.day>day) && (date.month>month) && (date.year>year);
    }

    void readData();
    void writeData();
};

int main() {
    Date date1 {30, 12, 2024};
    Date date2 {};
    date2.readData();

    date1.writeData();
    date2.writeData();

    cout << "Same year ? " << date1.sameYear(date2) << "\n"
    << "Same day and month ? " << date1.sameDay(date2) << "\n";

    if (!(date1.sameDay(date2) && (date1.sameYear(date2)))) {
        (date1.earlier(date2)) ? date1.writeData() : date2.writeData();
        cout << "\n";
    } else {
        cout << "Same Date" << "\n";
    }

    return 0;
}


void Date::readData() {
    day = lesInt("Write Day ", 1, 30);
    month = lesInt("Write Month ", 1, 12);
    year = lesInt("Write Year ", 2000, 2024);
}

void Date::writeData() {
    cout << day << "/" << month << "-" << year << "\n";
}