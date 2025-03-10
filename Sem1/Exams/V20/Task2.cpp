/**
 *   Skjelett for eksamen i OOProg (i C++), mai 2020, oppgave 2.
 *
 *   Programmet holder orden på ulike husstander, antall personer i hver
 *   og antall karantenedager disse personene har ifm. en epedemi/pandemi.
 *
 *   Programmet:
 *      - inneholder EN <list> med pekere til 'Husstand'-objekter.
 *        Det KAN forekomme duplikate ID'er ('dagSlutt') i listen,
 *        men INGEN 'Husstand' skal ha kontaktperson med samme navn.
 *      - skriver at ALLE data om ALLE husstander på skjermen
 *      - lar brukeren legge inn EN ny husstand (med alle sine data)
 *      - lar brukeren endre karantenetiden for EN husstand
 *      - lar brukeren slette (hele) husstanden for en NAVNGITT person
 *      - skriver statistikk for/oversikt over alle husstandene/karantenene
 *      - leser (og skriver) HELE datastrukturen fra fil
 *
 *   @file     EX_V20_2.TPL
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <string>                  //  string
#include <list>                    //  list
#include <algorithm>               //  Du får sikkert bruk for noen av disse.
#include "../LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


const int MINKARANTENE =  5;       ///<  Min. antall karantenedager.
const int MAXKARANTENE = 21;       ///<  Max. antall karantenedager.
const int MAXIHUSSTAND = 10;       ///<  Max. antall personer i EN husstand.


/**
 *  Husstand (med hvilke absolutt dagnummer i året karantenen er slutt
 *       (= ID, listen er sortert på dette), antall dager i karantene, antall
 *       personer i husstanden, mobilnummer/navn/adresse til kontaktpersonen).
 */
class Husstand  {
private:
    int    dagSlutt,               //  = ID – er sortert på dette.
    antallDager,
            antallPersoner,
            mobilNr;
    string navn,
            adresse;

public:
    Husstand()  { dagSlutt = antallDager = antallPersoner = mobilNr = 0; }
    Husstand(ifstream & inn);                                   //  Oppgave 2G
    void   endreData();                                         //  Oppgave 2C
    int    hentAntall() const  {  return antallPersoner;  }
    int    hentDager()  const  {  return antallDager;     }
    int    hentID()     const  {  return dagSlutt;        }
    string hentNavn()   const  {  return navn;            }
    void   lesData();                                           //  Oppgave 2B
    void   skrivData() const;                                   //  Oppgave 2A
    void   skrivTilFil(ofstream & ut) const;                    //  Oppgave 2D
};


void endreHusstand();                 //  Oppgave 2C
void fjernHusstander();               //  Oppgave 2D
void lesFraFil();                     //  Oppgave 2G
void nyHusstand();                    //  Oppgave 2B
void skrivAlleHusstander();           //  Oppgave 2A
void skrivMeny();
void slettPersonsHusstand();          //  Oppgave 2F
void statistikk();                    //  Oppgave 2E


int  gDagnummerIAret;                 ///<  Absolutt dagnummer i året (1-344).
//      (344 + MAXKARANTENE = 365)
list <Husstand*> gHusstander;         ///<  ALLE husstandene i karantene.


/**
 *  Hovedprogrammet:
 */
int main() {
    char valg;

    lesFraFil();                                     //  Oppgave 2G

    fjernHusstander();                               //  Oppgave 2D

    cout << "\nI dag er det den " << gDagnummerIAret << ".dagen i året.\n\n";

    skrivMeny();
    valg = lesChar("\n\nKommando");

    while (valg != 'Q') {
        switch (valg) {
            case 'A': skrivAlleHusstander();   break;  //  Oppgave 2A
            case 'N': nyHusstand();            break;  //  Oppgave 2B
            case 'E': endreHusstand();         break;  //  Oppgave 2C
            case 'S': statistikk();            break;  //  Oppgave 2E
            case 'P': slettPersonsHusstand();  break;  //  Oppgave 2F
            default:  skrivMeny();             break;
        }
        valg = lesChar("\n\nKommando");
    }

    cout << "\n\n";
    return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2G - Leser inn ALLE egne data fra fil.
 *
 *  @param  inn  -  Filobjektet det leses inn data fra
 */
Husstand::Husstand(ifstream & inn)  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2C - Endrer karantenetiden for hele husstanden.
 */
void Husstand::endreData()  {
    Husstand::skrivData();
    antallDager = lesInt("Antall Dager igjen ", 1, MAXKARANTENE);
    dagSlutt = antallDager + gDagnummerIAret;
    Husstand::skrivData();
}


/**
 *  Oppgave 2B - Leser inn ALLE egne data fra tastaturet.
 */
void Husstand::lesData()  {
    std::cout << "Navn : "; std::getline(std::cin, navn);
    std::cout << "Adresse : "; std::getline(std::cin, adresse);

    antallDager = lesInt("Antall Dager ", MINKARANTENE , MAXKARANTENE);
    dagSlutt = antallDager + gDagnummerIAret;
    antallPersoner = lesInt("Antall Personer ", 0, MAXIHUSSTAND);
    mobilNr = lesInt("Mobli nummer ", 10000000, 99999999);
}


/**
 *  Oppgave 2A - Skriver ALLE egne data ut på skjermen.
 */
void Husstand::skrivData() const  {
    std::cout << "\nNavn          : " << navn << std::endl;
    std::cout << "Adresse         : " << adresse << std::endl;

    std::cout << "Dag Slutt       : " << dagSlutt << std::endl;
    std::cout << "Antall dager    : " << antallDager << std::endl;
    std::cout << "Antall Personer : " << antallPersoner << std::endl;
    std::cout << "Mobil nummer    : " << mobilNr << std::endl;
}


/**
 *  Oppgave 2D - Skriver ALLE egne data ut på fil.
 *
 *  @param   ut  -  Filobjektet det skrives ut data til
 */
void Husstand::skrivTilFil(ofstream & ut) const  {
    ut << std::endl << dagSlutt << " " << antallDager << " " << antallPersoner
    << " " << mobilNr << std::endl << navn << std::endl << adresse;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2C - Endrer (om mulig) en nummerangitt husstand
 *               sine antall karantenedager.
 */
void endreHusstand()  {
    if (gHusstander.empty()) {
        std::cout << "\nIngen Hustander\n";
        return;
    }

    int index = lesInt("Skriv nummer ", 0, gHusstander.size());

    auto rit = gHusstander.rbegin();
    std::prev(rit, index);

    if (rit == gHusstander.rbegin()) {
        std::cout << "\nBruker Angrer seg\n";
        return;
    }

    (*rit)->endreData();
    gHusstander.sort([](Husstand *p1, Husstand *p2){ return p1->hentID() < p2->hentID(); });
}


/**
 *  Oppgave 2D - Fjerner ALLE husstander hvis karantene utgår I DAG.
 */
void fjernHusstander()  {
    std::ofstream app(R"(C:\Users\Tharald\CLionProjects\Cpp\Exams\V20\KARANTENEFERDIG.DTA)", std::ios::app);

    int antall = gHusstander.size();

    gHusstander.remove_if([&](auto & val){
        if (val->hentID() == gDagnummerIAret) {
            val->skrivTilFil(app);
            delete val;
            return 1;
        }
        return 0;
    });

    if (antall > gHusstander.size()) {
        std::cout << "Slettet : " << antall - gHusstander.size() << "Hustander\n";
        std::cout << "Alle Skrevet til fil\n";
    }

    app.close();
}


/**
 *  Oppgave 2G - Leser ALLE husstandene i karantene inn fra fil.
 */
void lesFraFil()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2B - Legger inn en ny husstand i karantene.
 */
void nyHusstand()  {
    auto *h = new Husstand();
    h->lesData();
    gHusstander.push_back(h);

    gHusstander.sort([](Husstand *p1, Husstand *p2){ return p1->hentID() < p2->hentID(); });
}


/**
 *  Oppgave 2A - Går gjennom og skriver HELE 'gHusstander' sitt innhold.
 */
void skrivAlleHusstander()  {
    std::cout << "Dag i aaret : " << gDagnummerIAret << std::endl;

    for (const auto & val : gHusstander)
        val->skrivData();

    std::cout << "Antall Hustander : " << gHusstander.size() << std::endl;
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny()  {
    cout << "\nFølgende kommandoer er tilgjengelige:\n"
         << "   A  - skriv Alle husstander\n"
         << "   N  - Ny husstand i karantene\n"
         << "   E  - Endre karantenedagene for en husstand\n"
         << "   S  - Statistikk om alle husstander i karantene\n"
         << "   P  - slett en navngitt Persons husstand\n"
         << "   Q  - Quit / avslutt\n";
}


/**
 *  Oppgave 2F - Sletter (om mulig) en navngitt kontaktpersons sin husstand.
 */
void slettPersonsHusstand()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2E - Skriver statistikk over:
 *                1) Antall husstander ute av karantene om X (1-21) dager
 *                2) Antall personer/husstander med Y (1-21) dagers karantene.
 */
void statistikk()  {
    int antall = 0;

    for (int i = 1; i < MAXKARANTENE; i++) {
        std::for_each(gHusstander.begin(), gHusstander.end(), [&](const auto & val)
        {if (val->hentID() == i) antall++;});
        std::cout << "Antall Hustander som skal ut om " << i << " Dager : " << antall << std::endl;
        antall = 0;
    }
    for (int i = 1; i < MAXKARANTENE; i++) {

    }
}