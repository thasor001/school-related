/**
 * Week 2 Task 3.
 */

#include <iostream>
#include <iomanip>
#include "LesData.h"
using namespace std;


const int MINTEMP   = -70;   ///<  Absolutt laveste mulige temperatur.
const int MAXTEMP   =  70;   ///<  Absolutt høyeste mulige temperatur.
const int MAXNEDBOR = 200;   ///<  Absolutt høyeste mulige nedbør pr.døgn.
const int MINDAGER  =   5;   ///<  Minimum antall dager i en måned.
const int MAXDAGER  =  31;   ///<  Maksimum antall dager i en måned.


int main ()  {
    char svar;
    int  antDager,
            min,
            max,
            nedbor,
            totMin = 0,
            totMax = 0,
            totNedbor = 0;

    svar = lesChar("Les inn vaerdata for en maand (j/n) : ");

    while (svar != 'N') {
        antDager = lesInt("Antall dager i maaneden : ", MINDAGER, MAXDAGER);

        for (int i = 0;  i < antDager;  i++)  {
            cout <<"\nDag nr" << i+1 <<":\n";

            min = lesInt("Minimums temp : ", MINTEMP, MAXTEMP);
            totMin += min;

            max = lesInt(" Maksimums temp : ", min, MAXTEMP);
            totMax += max;

            nedbor = lesInt("Nedboor : ", 0, MAXNEDBOR);
            totNedbor += nedbor;
        }

        cout <<fixed<<setprecision(2)<<"\n\nGjennomsnittlig min.temp: "<<static_cast <float>(totMin/antDager)<<" grader C\n";
        cout <<fixed<<setprecision(2)<<"Gjennomsnittlig max.temp: "<<static_cast <float>(totMax/antDager)<<" grader C\n";
        cout <<fixed<<setprecision(2)<<"Gjennomsnittlig nedboor: "<<static_cast <float>(totNedbor/antDager)<<" mm\n";
        cout <<"Total nedboor i maaneden:   "<<totNedbor<<" mm\n";

        svar = lesChar("Les inn vaerdata for en maand (j/n) : ");
    }

    cout <<"\n\n\nHa en fortsatt god (vaer(syk))dag!\n\n";

    return 0;
}