/**
 *   Skjelett for kontinuasjonseksamen i OOProg (i C++), aug 2020, oppgave 2.
 *
 *   Programmet holder orden på nettarrangementer (konserter og foredrag).
 *
 *   Programmet:
 *      - inneholder EN <map> med key/dato (unike) og pekere til
 *        'NettArrangement' (i praksis 'Musikk'- eller 'Foredrag'-objekter)
 *      - skriver ALLE data om ALLE arrangementene ut på skjermen
 *      - skriver ALLE arrangementene i en viss TIDSPERIODE ut på skjermen
 *      - skriver ALLE foredragene i en viss NAVNGITT SERIE ut på skjermen
 *      - sletter ett arrangement
 *      - legger inn ett nytt arrangement
 *      - leser og skriver HELE datastrukturen fra/til fil
 *
 *   @file     EX_S20_2.TPL
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <string>                  //  string
#include <map>                     //  map
#include <algorithm>               //  find_if
#include "../LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


const int FDATO = 200101;          ///<  Første mulige dato (1/1-2020).
const int SDATO = 301231;          ///<  Siste mulige dato (31/12-2030).


/**
 *  ArrType (arrangementstype som:  'ikkeSatt', 'musikk' og 'foredrag').
 */
enum  ArrType  {  ikkeSatt, musikk, foredrag  };


/**
 *  Kategori (om er arrangert av:  en 'privat' eller 'offentlig' aktør).
 */
enum  Kategori  {  privat,  offentlig  };


/**
 *  NettArrangement (med dato (unik - max ett arrangement hver dag),
 *                   startklokkeslett, Vippsnummer, ca varighet i timer,
 *                   arrangementsnavn, navn på aktør og en enum 'type').
 */
class NettArrangement {
private:
    int     dato,               //  = ID – dette er key'en i <map>en,
    klokken,            //         på formen: ÅÅMMDD.
    vippsNr;
    float   varighet;
    string  arrNavn,
            aktor;
protected:
    ArrType type;
public:
    NettArrangement(const int dato) {  this->dato = dato;   type = ikkeSatt;
        klokken = vippsNr = 0;   varighet = 0.0F;  }
    NettArrangement(ifstream & inn);                     //  Oppgave 2G
    int  hentID() const  {  return dato;  }
    bool erAvType(const ArrType type) const { return (this->type == type); }
    bool liktArrNavn(const string nvn) const  {  return (arrNavn == nvn);  }
    virtual void lesData();                              //  Oppgave 2E
    virtual void skrivData() const;                      //  Oppgave 2A
    virtual void skrivTilFil(ofstream & ut) const;       //  Oppgave 2F
    virtual NettArrangement* clone(const int date) = 0;
    void endreDato(const int dato) { this->dato = dato; }
};


/**
 *  Musikk (med kun antall personer (i bandet) på scenen.
 */
class Musikk : public NettArrangement {
private:
    int  antPersoner;
public:
    Musikk(const int dato) : NettArrangement(dato)
    {  type = musikk;  antPersoner = 0;  }
    Musikk(ifstream & inn);                              //  Oppgave 2G
    virtual void lesData();                              //  Oppgave 2E
    virtual void skrivData() const;                      //  Oppgave 2A
    virtual void skrivTilFil(ofstream & ut) const;       //  Oppgave 2F
    NettArrangement* clone(const int dato) {
        NettArrangement::clone(dato);
        return new Musikk((*this));
    };
};


/**
 *  Foredrag (med hvilket nummer i en evt serie, og om 'privat'/'offentlig').
 */
class Foredrag : public NettArrangement {
private:
    int      serieNr;
    Kategori kategori;
public:
    Foredrag(const int dato) : NettArrangement(dato)
    {  type = foredrag;   serieNr = 1;   kategori = privat;  }
    Foredrag(ifstream & inn);                         //  Oppgave 2G
    virtual void lesData();                           //  Oppgave 2E
    virtual void skrivData() const;                   //  Oppgave 2A
    virtual void skrivTilFil(ofstream & ut) const;    //  Oppgave 2F
    NettArrangement* clone(const int dato) {
        NettArrangement::clone(dato);
        Foredrag * f = new Foredrag((*this));
        f->serieNr++;
        f->endreDato(dato);
        return f;
    };
};


void lesFraFil();                   //  Oppgave 2G
void nyttArrangement();             //  Oppgave 2E
void skrivAlt();                    //  Oppgave 2A
void skrivForedragsserie();         //  Oppgave 2C
void skrivMeny();
void skrivTidsperiode();            //  Oppgave 2B
void skrivTilFil();                 //  Oppgave 2F
void slettArrangement();            //  Oppgave 2D


map <int, NettArrangement*>  gArrangementer;    ///<  ALLE arrangementene.


/**
 *  Hovedprogrammet:
 */
int main() {
    char valg;

    lesFraFil();                                       //  Oppgave 2G

    skrivMeny();
    valg = lesChar("\n\nKommando");
    while (valg != 'Q') {
        switch (valg) {
            case 'A': skrivAlt();             break;     //  Oppgave 2A
            case 'T': skrivTidsperiode();     break;     //  Oppgave 2B
            case 'F': skrivForedragsserie();  break;     //  Oppgave 2C
            case 'S': slettArrangement();     break;     //  Oppgave 2D
            case 'N': nyttArrangement();      break;     //  Oppgave 2E
            default:  skrivMeny();            break;
        }
        valg = lesChar("\n\nKommando");
    }

    skrivTilFil();                                     //  Oppgave 2F

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
NettArrangement::NettArrangement(ifstream & inn) {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2E - Leser inn ALLE egne data fra tastaturet.
 */
void NettArrangement::lesData() {
    klokken = lesInt("Skriv Klokken ", 0, 2359);
    vippsNr = lesInt("Skriv VipsNr ", 10000, 99999);
    varighet = lesFloat("Skriv varighet ", 0, 10);
    std::cout << "Arr Navn : "; std::getline(std::cin, arrNavn);
    std::cout << "Aktor : "; std::getline(std::cin, aktor);
}


/**
 *  Oppgave 2A - Skriver ALLE egne data ut på skjermen.
 */
void NettArrangement::skrivData() const {
    std::cout << "\nDato: " << dato
         << "\nKlokken: " << klokken
         << "\nVippsNr: " << vippsNr
         << "\nVarighet: " << varighet
         << "\narrNavn: " << arrNavn
         << "\nAktor: " << aktor;
}


/**
 *  Oppgave 2F - Skriver ALLE egne data ut på fil.
 *
 *  @param   ut  -  Filobjektet det skrives ut data til
 */
void NettArrangement::skrivTilFil(ofstream & ut) const {

    //   LAG INNMATEN
}


// ---------------------------------------------------------------------------

/**
 *  Oppgave 2G - Leser inn egne data fra fil.
 *
 *  @param  inn  -  Filobjektet det leses inn data fra
 *  @see    NettArrangement::NettArrangement(...)
 */
Musikk::Musikk(ifstream & inn) : NettArrangement(inn) {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2E - Leser inn ALLE egne data fra tastaturet.
 */
void Musikk::lesData() {
    NettArrangement::lesData();
    antPersoner = lesInt("Skriv antall personer ", 0, 5);
}


/**
 *  Oppgave 2A - Skriver ALLE egne data ut på skjermen.
 */
void Musikk::skrivData() const {
    NettArrangement::skrivData();
    std::cout << "\nArrtype : Musikk\n"
    << "Antall Personer : " << antPersoner << std::endl;

}


/**
 *  Oppgave 2F - Skriver ALLE egne data ut på fil.
 *
 *  @param   ut  -  Filobjektet det skrives ut data til
 */
void Musikk::skrivTilFil(ofstream & ut) const {

    //   LAG INNMATEN
}


// ---------------------------------------------------------------------------

/**
 *  Oppgave 2G - Leser inn egne data fra fil.
 *
 *  @param  inn  -  Filobjektet det leses inn data fra
 *  @see    NettArrangement::NettArrangement(...)
 */
Foredrag::Foredrag(ifstream & inn) : NettArrangement(inn) {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2E - Leser inn ALLE egne data fra tastaturet.
 */
void Foredrag::lesData() {
    NettArrangement::lesData();
    serieNr = lesInt("Hvilket nr i serie ", 1, 100);
    char valg;
    do {
        valg = lesChar("O(ffentlig), P(rivat)");
    } while(valg != 'O' && valg != 'P');

    switch (valg) {
        case 'O': kategori = offentlig; break;
        case 'P': kategori = privat;    break;
    }
}


/**
 *  Oppgave 2A - Skriver ALLE egne data ut på skjermen.
 */
void Foredrag::skrivData() const {
    NettArrangement::skrivData();
    std::cout << "\nArrtype : Foredrag\n"
    << "Serie Nr : " << serieNr << std::endl << "Kategori : ";
    switch (kategori) {
        case 0: std::cout << "Privat\n";    break;
        case 1: std::cout << "Offentlig\n"; break;
    }
}


/**
 *  Oppgave 2F - Skriver ALLE egne data ut på fil.
 *
 *  @param   ut  -  Filobjektet det skrives ut data til
 */
void Foredrag::skrivTilFil(ofstream & ut) const {

    //   LAG INNMATEN
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2G - Leser hele datastrukturen (ulike arrangementer) inn fra fil.
 */
void lesFraFil() {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2E - Legger inn (om mulig) ett nytt arrangement (Musikk/Foredrag).
 */
void nyttArrangement() {
    std::string navn;
    char valg = lesChar("M(usikk), F(oredrag)");


    if (valg != 'M' && valg != 'F') {
        std::cout << "Feil valg : " << valg << std::endl;
        return;
    }

    int dato = lesInt("Skriv Dato ", FDATO, SDATO);

    if (gArrangementer.find(dato) != gArrangementer.end()) {
        std::cout << "Finnes Allerede Arrangemnet paa dato : " << dato << std::endl;
        return;
    }

    switch (valg) {
        case 'M':
            gArrangementer[dato] = new Musikk(dato);
            gArrangementer[dato]->lesData();
            break;

        case 'F':
            valg = lesChar("N(ytt), S(erie)");
            if (valg == 'N') {
                gArrangementer[dato] = new Foredrag(dato);
                gArrangementer[dato]->lesData();
            } else if (valg == 'S') {
                std::cout << "Skriv navn : "; std::getline(std::cin, navn);

                auto it = std::find_if(gArrangementer.rbegin(), gArrangementer.rend(), [&navn](const auto& pair)
                { return (pair.second->erAvType(foredrag) && pair.second->liktArrNavn(navn)); });

                if (it == gArrangementer.rend()) {
                    std::cout << "Finnes ingen Arrangement med arrNavn : " << navn << std::endl;
                    return;
                }

                if (dato < it->second->hentID()) {
                    std::cout << dato << " Er foor : " << it->second->hentID() << std::endl;
                    return;
                }

                gArrangementer[dato] = it->second->clone(dato);
            }
            break;
    }

}


/**
 *  Oppgave 2A - Skriver ALT om ALLE arrangementene ut på skjermen.
 */
void skrivAlt() {
    for (const auto& pair : gArrangementer) {
        std::cout << std::endl;
        pair.second->skrivData();
    }
}


/**
 *  Oppgave 2C - Skriver ALLE foredragene i en NAVNGITT SERIE ut på skjermen.
 */
void skrivForedragsserie() {
    if (gArrangementer.empty()) {
        std::cout << "\nIngen Arrangementer\n";
        return;
    }

    std::string navn;
    std::cout << "Skriv navn : "; std::getline(std::cin, navn);

    std::for_each(gArrangementer.begin(), gArrangementer.end(), [&](const auto& pair)
    { if(pair.second->erAvType(foredrag) && pair.second->liktArrNavn(navn)) pair.second->skrivData(); });
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny() {
    cout << "\nFølgende kommandoer er tilgjengelige:\n"
         << "\n   A  - skriv Alle arrangementer"
         << "\n   T  - skriv alle arrangement i en viss Tidsperiode"
         << "\n   F  - skriv en hel Foredragsserie"
         << "\n   S  - Slett arrangement"
         << "\n   N  - Nytt arrangement"
         << "\n   Q  - Quit / avslutt";
}


/**
 *  Oppgave 2B - Skriver ALLE arrangementene i en TIDSPERIODE ut på skjermen.
 */
void skrivTidsperiode() {
    if (gArrangementer.empty()) {
        std::cout << "\nIngen Arrangementer\n";
        return;
    }

    int antall = 0;

    int start = lesInt("Skriv Fra dato ", FDATO, SDATO);
    int slutt = lesInt("Skriv Til dato ", start, SDATO);

    auto it = gArrangementer.find(slutt); std::advance(it, 1);

    std::for_each(gArrangementer.find(start), it, [&antall](const auto& pair)
    { pair.second->skrivData(); antall++; });

    std::cout << "\nAntall datoer immelom : " << antall << std::endl;
}


/**
 *  Oppgave 2F - Skriver hele datastrukturen (ulike arrangementer) ut til fil.
 */
void skrivTilFil() {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2D - Sletter (om mulig) ett gitt arrangement på en gitt dato.
 */
void slettArrangement() {
    int dato = lesInt("Skriv Dato ", FDATO, SDATO);

    auto it = gArrangementer.find(dato);

    if (it == gArrangementer.end()) {
        std::cout << "Finnes ingen Arrangemnet paa dato : " << dato << std::endl;
        return;
    }

    it->second->skrivData();

    delete it->second;
    gArrangementer.erase(it);
}