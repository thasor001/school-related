#include "iostream"
using namespace std;

struct Tid{
    int time;
    int minutt;
    int sekund;
};


struct Tid storst(const struct Tid tid1, const struct Tid tid2) {
    int total1 = tid1.time * 3600 + tid1.minutt * 60 + tid1.sekund;
    int total2 = tid2.time * 3600 + tid2.minutt * 60 + tid2.sekund;

    if (total1 > total2){
        return tid1;
    } else
        return tid2;
}


int main(){
    struct Tid tid1, tid2, tid3, tid4;

    tid1 = {14, 53, 38};
    tid2 = {12, 26, 8};
    tid3 = {13, 54, 11};
    tid4 = {14, 25, 25};

    int total1 = storst(tid1, tid2).time * 3600 + storst(tid1, tid2).minutt * 60 + storst(tid1, tid2).sekund;
    int total2 = storst(tid3, tid4).time * 3600 + storst(tid3, tid4).minutt * 60 + storst(tid3, tid4).sekund;;

    if (total1 > total2){
        cout << "Time : " << storst(tid1, tid2).time << " Minutt : " << storst(tid1, tid2).minutt
        << " Sekund : " << storst(tid1, tid2).sekund << "\n";
    } else {
        cout << "Time : " << storst(tid3, tid4).time << " Minutt : " << storst(tid4, tid4).minutt
             << " Sekund : " << storst(tid4, tid4).sekund << "\n";
    }

    return 0;
}