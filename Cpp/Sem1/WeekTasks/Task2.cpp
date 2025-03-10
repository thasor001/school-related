/**
 * Week 1 Task 3.
 */

#include <iostream>
#include <string>
#include <iomanip>
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

    cout << "\nLese inn vaerdata for en maaned (J/n): ";
    cin >> svar;
    svar = toupper(svar);

    while (svar != 'N') {
        do {
            cout << "Antall dager i maaneden ( "<<MINDAGER<< "-" <<MAXDAGER<<" )";
            cin >> antDager;

        } while (antDager < MINDAGER  ||  antDager > MAXDAGER);

        for (int i = 0;  i < antDager;  i++)  {
            cout <<"\nDag nr" << i+1 <<":\n";

            do {
                cout <<"\tMinimumstemp ("<<MINTEMP<<" til "<<MAXTEMP<<"): ";
                cin >> min;
                cout << "\n min:" << min;
            } while(min < MINTEMP ||  min > MAXTEMP);
            totMin += min;

            do {
                cout <<"\tMaksimumstemp ("<<min<<" til "<<MAXTEMP<<"): ";
                cin >> max;
            } while(max < min  ||  max > MAXTEMP);
            totMax += max;

            do {
                cout <<"\tNedboor (0 til "<<MAXNEDBOR<<"): ";
                cin >> nedbor;
                cout << "\n nedbor:" << nedbor << "\n";
            } while(nedbor < 0  ||  nedbor > MAXNEDBOR);
            totNedbor += nedbor;
        }

        cout <<fixed<<setprecision(2)<<"\n\nGjennomsnittlig min.temp: "<<static_cast <float>(totMin/antDager)<<" grader C\n";
        cout <<fixed<<setprecision(2)<<"Gjennomsnittlig max.temp: "<<static_cast <float>(totMax/antDager)<<" grader C\n";
        cout <<fixed<<setprecision(2)<<"Gjennomsnittlig nedboor: "<<static_cast <float>(totNedbor/antDager)<<" mm\n";
        cout <<"Total nedboor i maaneden:   "<<totNedbor<<" mm\n";

        cout <<"\nLese inn vaerdata for en maaned til (J/n): ";
        cin >> svar;
        svar = toupper(svar);
    }

    cout <<"\n\n\nHa en fortsatt god (vaer(syk))dag!\n\n";

    return 0;
}