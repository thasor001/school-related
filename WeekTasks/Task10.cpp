//
// Created by Tharald on 13/02/2024.
//
#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  string
#include <vector>                  //  vector
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


/**
 *  Bok (med tittel, forfatter, antall sider og om lest eller ei).
 */
class Bok {
private:
    string tittel,
            forfatter;
    int    antallSider;
    bool   lest;
public:
    Bok() {
        tittel = forfatter = "";
        antallSider = 0, lest = false;
    }

};


void bokLesData(Bok & bok);             //     XXXXXXXXXX
void bokLest(Bok & bok);                //     XXXXXXXXXX
void bokSkrivData(const Bok* bok);      //     XXXXXXXXXX
void bokSkrivData(const Bok bok);
void fjernBok();
void lestBok();
void nyBok();
void skrivAlleBoker1();
void skrivAlleBoker2();
void skrivBok();
void skrivMeny();
void slettAlt();


vector <Bok*> gBokene;       ///<  Alle bøkene i oversikten/datastrukturen.
//    NB:  Trenger nå ikke lengre 'gAntallBoker',
//         da gBokene.size() er dette antallet.

/**
 *  Hovedprogrammet:
 */
int main()  {
    char kommando;

    skrivMeny();
    kommando = lesChar("\nKommando");

    while (kommando != 'Q') {
        switch (kommando) {
            case 'N': nyBok();            break;
            case 'S': skrivBok();         break;
            case '1': skrivAlleBoker1();  break;
            case '2': skrivAlleBoker2();  break;
            case 'L': lestBok();          break;
            case 'F': fjernBok();         break;
            default:  skrivMeny();        break;
        }
        kommando = lesChar("\nKommando");
    }

    slettAlt();

    return 0;
}


/**
 *  Leser inn og fyller ALLE en Bok sine datamedlemmer.
 *
 *  @param   bok  - Structen som får sine datamedlemmer innlest/fylt
 */



/**
 *  Setter en Bok som lest.
 *
 *  @param   bok  - Structen som får 'lest' satt til 'true'
 */
void bokLest(Bok & bok) {
    cout << "\n\tBoken er markert/satt som 'Lest'.\n";
    bok.lest = true;
}


/**
 *  Overloaded funksjon som skriver en structs data (peker som parameter).
 *
 *  @param   bok  - PEKER til structen hvis data utskrives på skjermen
 */
void bokSkrivData(const Bok* bok)  {
    cout << "\t\t\"" << bok->tittel << "\" av " << bok->forfatter
         << ",  " << bok->antallSider << " sider - "
         << ((!bok->lest) ? "IKKE " : "") << "lest\n";
}


/**
 *  Overloaded funksjon som skriver structdata (struct-variabel som paramtr).
 *
 *  @param   bok  - Struct-VARIABEL hvis data utskrives på skjermen
 */
void bokSkrivData(const Bok bok)  {
    cout << "\t\t\"" << bok.tittel << "\" av " << bok.forfatter
         << ",  " << bok.antallSider << " sider - "
         << ((!bok.lest) ? "IKKE " : "") << "lest\n";
}


/**
 *  Ønsket boknummer slettes, og bakerste flyttes til den slettedes plass.
 */
void fjernBok() {
    int nr = lesInt("\tFjerne bok nr", 1, gBokene.size());  //  Ønsket nr.
    delete gBokene[nr-1];                      // Sletter aktuell bok!
    gBokene[nr-1] = gBokene[gBokene.size()-1]; // Bakerst flyttes til plassen.
    gBokene.pop_back();                        // Siste PEKER slettes også!
}


/**
 *  Ønsket boknummer markeres som lest.
 *
 *  @see   boklest(...)
 */
void lestBok() {
    bokLest(*gBokene[lesInt("\tLest bok nr", 1, gBokene.size())-1]);
}


/**
 *  Ny bok legges inn i datastrukturen (vectoren 'gBokene').
 *
 *  @see   bokLesData(...)
 */
void nyBok() {
    Bok* nyBok = new Bok;         //  Oppretter en ny Bok-struct.
    cout << "\nNy bok:\n";
    bokLesData(*nyBok);           //  Alle dens data leses inn.
    gBokene.push_back(nyBok);     //  Legges bakerst i vectoren.
    cout << "\n\tNy bok innlagt har nr." << gBokene.size() << '\n';
}


/**
 *  Overloaded funksjon som skriver alle bøkene vha PEKER.
 *
 *  @see   bokSkrivData(const Bok* bok)
 */
void skrivAlleBoker1() {
    for (int i = 0;  i < gBokene.size();  i++) {
        cout << "\tBok nr." << setw(2) << i+1 << ":\n";
        bokSkrivData(gBokene[i]);
    }
}


/**
 *  Overloaded funksjon som skriver alle bøkene vha STRUCT-VARIABEL.
 *
 *  @see   bokSkrivData(const Bok bok)
 */
void skrivAlleBoker2() {
    for (int i = 0;  i < gBokene.size();  i++) {
        cout << "\tBok nr." << setw(2) << i+1 << ":\n";
        bokSkrivData(*gBokene[i]);
    }
}


/**
 *  Skriver alt en ETT ønsket boknummer.
 *
 *  @see   bokSkrivData(const Bok* bok)
 */
void skrivBok() {
    bokSkrivData(gBokene[lesInt("\tSe bok nr", 1, gBokene.size())-1]);

//     Eller med bruk av '*':  Dermed kalles den andre OVERLOADEDE funksjonen:
//         bokSkrivData(*gBokene[lesInt("\tSe bok nr", 1, gBokene.size())-1]);
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny() {
    cout << "\nFølgende kommandoer er tilgjengelig:\n"
         << "\tN - Ny bok\n"
         << "\tS - Skriv EN gitt bok\n"
         << "\t1 - skriv alle bøkene vha. peker\n"
         << "\t2 - skriv alle bøkene vha. struct-variabel\n"
         << "\tL - Lest en bok\n"
         << "\tF - Fjern en gitt bok\n"
         << "\tQ - Quit / avslutt\n";
}


/**
 *  Sletter/fjerner ALLE tilpekte structer (Bok), og alle pekerne i vectoren.
 */
void slettAlt() {
    //  EN måte (av mange) å fjerne ALT i vectoren:
    while (!gBokene.empty()) {              //  Så lenge PEKERE i vectoren:
        delete gBokene[gBokene.size()-1];   //  Sletter den SISTE TILPEKTE.
        gBokene.pop_back();                 //  Sletter/fjerner SELVE PEKEREN.
    }
/*                            //  En annen (og enklere?) måte:
  for (int i = 0; i < gBokene.size(); i++)  // Sletter ALLE bøkene/struct'ene:
      delete gBokene[i];
  gBokene.clear();                        //  Fjerner ALLE PEKERNE i vectoren.
*/
    cout << "\n\nvectoren er tom - antallet er: " << gBokene.size() << "\n\n";
}