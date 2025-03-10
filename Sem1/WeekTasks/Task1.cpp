/**
 * Week 1 Task 1.
 */

#include <iostream>     // printf, scanf
#include <iomanip>      // setprecision
#include <string>       // toUpper

using namespace std;
const int MAXLOPERE = 10;


int main()  {
    int distanse,
    ant500,
    min, sek, hundr,
    antallLopere;
    float poeng;
    char  brukerSvar;

    do  {
        do  {
            cout <<"\nSkriv en skoytedistanse (500, 1500, 3000, 5000):  ";
            cin >> distanse;
        } while (distanse != 500   &&  distanse != 1500 &&
                 distanse != 3000  &&  distanse != 5000);

        ant500 = distanse / 500;

        do  {
            cout <<"\nAntall lopere aa lese tider for (1-"<<MAXLOPERE<<") :";
            cin >> antallLopere;
        } while (antallLopere < 1  ||  antallLopere > MAXLOPERE);

        for (int i = 1;  i <= antallLopere;  i++)  {
            do  {
                cout <<"\nTid (mm ss hh):  ";
                cin >> min >> sek >> hundr;
            } while (min < 0  ||  sek < 0  || hundr < 0);

            poeng =  ((min*60) + sek + (hundr/100.0)) / ant500;

            cout << fixed << setprecision(3) <<"\tPoengsum:  "<<poeng;
        }

        cout <<"\n\nLese tider om en ny distanse (j/N):  ";
        cin >> brukerSvar;
        brukerSvar = toupper(brukerSvar);
    } while (brukerSvar == 'J');

    return 0;
}