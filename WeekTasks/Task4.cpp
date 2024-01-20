/**
* Week 2, Task 4.
*/

#include "LesData.h"
#include <iomanip>
#include <string>
#include <iostream>
using namespace std;

struct Time{
    int hour,
    minute,
    seconds;
};

void menu() {
    cout << "N - Stops program"
    << "\nJ - Check what time is biggest";
}

void createTime() {
    struct Time time1;
    time1.hour = 2;
    time1.minute = 10;
    time1. seconds = 50;

    struct Time time2;
    time2.hour = 2;
    time2.minute = 11;
    time2.seconds = 10;

    struct Time time3;
    time3.hour = 1;
    time3.minute = 12;
    time3.seconds = 10;

    struct Time time4;
    time4.hour = 5;
    time4.minute = 11;
    time4.seconds = 56;
}

void biggestTime(const struct time, const struct time) {

}

int main() {
    menu();
    createTime();

    char ans;

    do {
        ans = lesChar("\n\nAdd time structs ");

        switch (ans) {
            case 'J':

                break;
            default:
                cout << "\nWrong" << ans << " command";
                break;
        }



    } while (ans != 'N');

    return 0;
}