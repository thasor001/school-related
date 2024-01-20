/**
* Week 2, Task 4.
*/

#include <iostream>

using namespace std;

struct Time{
    int hour,
    minute,
    seconds;
};

float biggestTime(const struct Time t1, const struct Time t2) {
    float time1 = (t1.hour + t1.minute/100.0 + t1.seconds/10000.0);
    float time2 = (t2.hour + t2.minute/100.0 + t2.seconds/10000.0);

    return (time1>time2) ? time1 : time2;
}

int main() {
    Time time1;
    time1.hour = 12;
    time1.minute = 11;
    time1. seconds = 13;

    Time time2;
    time2.hour = 12;
    time2.minute = 11;
    time2.seconds = 10;

    Time time3;
    time3.hour = 10;
    time3.minute = 12;
    time3.seconds = 10;

    Time time4;
    time4.hour = 5;
    time4.minute = 11;
    time4.seconds = 56;

    int hour, minute, second;

    float num1 = biggestTime(time1, time2);
    float num2 = biggestTime(time3, time4);

    if (num1 > num2) {
        hour = num1;
        minute = num1*100 - hour*100;
        second = num1*10000 - minute*100 - hour*10000;
        cout << "Highest time is: ";
        cout << hour <<" Hours " << minute <<" Minutes " << second <<" Seconds";
    } else {
        hour = num2;
        minute = num2*100 - hour*100;
        second = num2*10000 - minute*100 - hour*10000;
        cout << "Highest time is: ";
        cout << hour <<" Hours " << minute <<" Minutes " << second <<" Seconds";
    }

    return 0;
}