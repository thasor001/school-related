#include "LesData.h"
#include <iomanip>
#include <iostream>

using namespace std;

const int STRLEN = 40;
const int MAXFORELESNINGER = 1;

struct lecture {
    char subject[STRLEN/2],
    lecturer[STRLEN],
    place[STRLEN/2];
    int hourStart, minuteStart,
    hourEnd, minuteEnd;
};


void lectureReadData(lecture* l) {
     char sub[STRLEN/2] = "Math";
    strcpy(l->subject, sub);
    strcpy(l->lecturer, sub);
    strcpy(l->place, sub);
    l->hourStart = 2;
    l->minuteStart = 15;
    l->hourEnd = 6;
    l->minuteEnd = 5;
}

void lectureWriteData(const lecture* l) {
    cout << l->subject;
}


int main() {
    struct lecture lectures[MAXFORELESNINGER];

    for (int i = 0; i < MAXFORELESNINGER; i++) {
        lectureReadData(&lectures[i]);
    }

    for (int i = 0; i < MAXFORELESNINGER; i++) {
        lectureWriteData(&lectures[i]);
    }

    return 0;
}