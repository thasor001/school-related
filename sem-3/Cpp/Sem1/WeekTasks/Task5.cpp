#include "LesData2.h"
#include <cstring>
#include <iostream>
#include <time.h>

using namespace std;

const int STRLEN = 40;
const int MAXFORELESNINGER = 2;

struct lecture {
    char subject[STRLEN/2],
    lecturer[STRLEN],
    place[STRLEN/2];
    int hourStart, minuteStart,
    hourEnd, minuteEnd;
};


void lectureReadData(lecture* l) {
    string campus[2] = {"Gjoovik", "Trondheim"};

    char sub[STRLEN/2] = "Programming";
    strcpy(l->subject, sub);

    srand(time(nullptr));
    strcpy(l->place, campus[rand() % 2].c_str());

    l->hourStart = rand() % 12;
    l->minuteStart = rand() % 60+1;
    l->hourEnd = rand() % (12+1 - l->hourStart) + l->hourStart;
    l->minuteEnd = 5;
}

void lectureWriteData(const lecture* l) {
    cout << l->subject << "\n";
    cout << "Hour start: " << l->hourStart << " Minute start: " << l->minuteStart << "\n";
    cout << "Hour end: " << l->hourEnd << " Minute end: " << l->minuteEnd << "\n";
    cout << "Place: " << l->place << "\n";
}


int main() {
    lecture lectures[MAXFORELESNINGER];

    for (int i = 0; i < MAXFORELESNINGER; i++) {
        lectureReadData(&lectures[i]);
    }

    for (int i = 0; i < MAXFORELESNINGER; i++) {
        lectureWriteData(&lectures[i]);
    }

    return 0;
}