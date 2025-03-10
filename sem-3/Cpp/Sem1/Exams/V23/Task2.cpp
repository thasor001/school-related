/**
 *   Skjelett for eksamen i OOProg (i C++), mai 2023, oppgave 2.
 *
 *   Programmet holder orden på en persons lunsj- og middagsbesøk på
 *   ulike spisesteder/kafeer/restauranter.
 *
 *   Programmet:
 *      - inneholder EN <list> med pekere til 'Spisesteder'-objekter.
 *      - skriver ut ALLE spisesteder, eller ALT om ETT spiested
 *      - legger inn et nytt spisested eller måltid
 *      - skriver alle måltider spist på en gitt dato
 *      - frigir alt allokert minne
 *      - leser (og skriver) HELE datastrukturen fra fil
 *
 *   @file     EX_V23_2.TPL
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <iomanip>                 //  setw
#include <string>
#include <list>
#include <map>
#include <algorithm>               //  find_if, for_each
#include "../LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


class Maaltid;                     //  Pre-deklarasjon.


/**
 *  Spisested (navn, adresse, telefon og ALLE måltidene spist der).
 */
class Spisested {
private:
    string navn,                     //  UNIKT navn - sortert på dette.
    adresse,
            tlf;                      //  'tlf' er string, da også KAN
    //    inneholde '+', landskode og blanke.
    map <int, Maaltid*> maaltidene;  //  'int' er dato på formatet: MMDD
    //    og er UNIKT for hvert spisested.
public:
    Spisested(const string nvn)  {  navn = nvn;  }      //       (Ferdiglaget)
    Spisested(ifstream & inn);                          //  Oppgave 2I
    ~Spisested();                                       //  Oppgave 2H
    Maaltid* finnMaaltidPaaDato(const int dato) const;  //  Oppgave 2E
    string hentID() const  { return navn; }             //       (Ferdiglaget)
    void lesData();                                     //  Oppgave 2D
    void nyttMaaltid();                                 //  Oppgave 2F
    void skrivAlleData()  const;                        //  Oppgave 2C
    void skrivHovedData() const;                        //  Oppgave 2A
};


/**
 *  Baseklassen Maaltid (kun med navnet på måltidets hovedrett).
 */
class Maaltid  {
protected:
    string hovedrett;         //  Tekst (lunsj/middag) eller blank (middag).

public:
    Maaltid()  {  }
    Maaltid(ifstream & inn);                            //  Oppgave 2I
    virtual ~Maaltid()  {  }
    virtual void lesData() = 0;             //  = 0 betyr 'pure virtual',
    virtual void skrivData() const = 0;     //    dvs. subklasser MÅ lage dem.
};


/**
 *  Avledet klasse Lunsj (kun med om har drukket kaffe eller ei til lunsj).
 */
class Lunsj : public Maaltid  {
private:
    bool kaffe;               //  Drikker evt. KUN vann i tillegg (til lunsj).

public:
    Lunsj()  {  }
    Lunsj(ifstream & inn);                              //  Oppgave 2I
    virtual ~Lunsj()  {  }
    virtual void lesData();                             //  Oppgave 2F
    virtual void skrivData() const;                     //  Oppgave 2C
};


/**
 *  Avledet klasse Middag (med evt navn på forrett, dessert og/eller drikken).
 */
class Middag: public Maaltid  {
private:
    string forrett,           //  Tekst eller blank.
    dessert,           //  Tekst eller blank.
    drikke;            //  Tekst eller blank.

public:
    Middag()  {  }
    Middag(ifstream & inn);                             //  Oppgave 2I
    virtual ~Middag()  {  }
    virtual void lesData();                             //  Oppgave 2F
    virtual void skrivData() const;                     //  Oppgave 2C
};


Spisested* finnSpisested(const string navn);  //  Oppgave 2B
void frigiAllokertMinne();                    //  Oppgave 2H
void lesFraFil();                             //  Oppgave 2I
void nyttMaaltid();                           //  Oppgave 2F
void nyttSpisested();                         //  Oppgave 2D
void skrivAlleSpisesteder();                  //  Oppgave 2A
void skrivEttSpisested();                     //  Oppgave 2C
void skrivMeny();
void spistEnGittDato();                       //  Oppgave 2G


list <Spisested*> gSpisestedene;              ///<  ALLE aktuelle spisesteder.


/**
 *  Hovedprogrammet:
 */
int main() {
    char valg;

    lesFraFil();                                     //  Oppgave 2I

    skrivMeny();
    valg = lesChar("\nKommando");

    while (valg != 'Q') {
        switch (valg) {
            case 'A': skrivAlleSpisesteder();   break;  //  Oppgave 2A
            case 'E': skrivEttSpisested();      break;  //  Oppgave 2C
            case 'S': nyttSpisested();          break;  //  Oppgave 2D
            case 'M': nyttMaaltid();            break;  //  Oppgave 2F
            case 'D': spistEnGittDato();        break;  //  Oppgave 2G
            default:  skrivMeny();              break;
        }
        valg = lesChar("\nKommando");
    }

    frigiAllokertMinne();                            //  Oppgave 2H

    cout << "\n\n";
    return 0;
}


/**
 *  Oppgave 2I - Leser inn fra fil ALT om ETT spisested.
 *
 *  @param    inn  -  Filen det leses inn fra
 */
Spisested::Spisested(ifstream & inn)  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2H - Sletter/fjerner ALLE data inni ETT spisested.
 */
Spisested::~Spisested()  {
    for (auto & val : maaltidene) {
        delete val.second;
    }
    maaltidene.clear();
}


/**
 *  Oppgave 2E - Finner og returnerer (om mulig) 'Maaltid' på en gitt dato.
 *
 *  @param    dato  -  Datoen det ønskes å finne et måltid på
 *  @return   Måltidet på gitt dato, evt. nullptr (om ingen dato-match)
 */
Maaltid* Spisested::finnMaaltidPaaDato(const int dato) const  {
    auto it = std::find_if(maaltidene.begin(), maaltidene.end(), [&dato]
    (const auto & pair){return pair.first == dato;});

    if (it == maaltidene.end())
        return nullptr;
    return it->second;
}


/**
 *  Oppgave 2D - Leser inn spisestedets resterende enkelt-datamedlemmer.
 */
void Spisested::lesData()  {
    std::cout << "Skriv adresse : ";
    std::getline(std::cin, adresse);
    tlf = lesInt("Skriv tlf", 10000000, 9999999);
}


/**
 *  Oppgave 2F - Legger inn (om mulig) nytt måltid på en ny dato.
 */
void Spisested::nyttMaaltid()  {

    int date = lesInt("Skriv dato", 0, 9999);
    auto ptr = finnMaaltidPaaDato(date);
    if (ptr != nullptr) {
        std::cout << "Finnes allerede" << std::endl;
        return;
    }
    char valg = lesChar("L(unsj), M(iddag)");
    switch (valg) {
        case 'L': maaltidene[date] = new Lunsj;  break;
        case 'M': maaltidene[date] = new Middag; break;
        default: std::cout << "Feil Type\n";    return;
    }

    maaltidene[date]->lesData();
}


/**
 *  Oppgave 2C - Skriver ut på skjermen ALLE data om ETT spisested.
 */
void Spisested::skrivAlleData() const  {
    Spisested::skrivHovedData();

    std::for_each(maaltidene.begin(), maaltidene.end(), [](const auto & pair)
    {pair.second->skrivData();});
}


/**
 *  Oppgave 2A - Skriver ut på skjermen enkelt-datamedlemmene.
 */
void Spisested::skrivHovedData() const  {
    std::cout << "\nNavn : " << navn
    << " Adresse : " << adresse <<
    " TLF : " << tlf << std::endl
    << " Antall maaltid : " << maaltidene.size()
    << std::endl;
}


/**
 *  Oppgave 2I - Leser inn 'Maaltid'ets eneste datamedlem.
 *
 *  @param    inn  -  Filen det leses inn fra
 */
Maaltid::Maaltid(ifstream & inn)  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2I - Leser inn fra fil 'Lunsj' sitt eneste datamedlem.
 *
 *  @param    inn  -  Filen det leses inn fra
 */
Lunsj::Lunsj(ifstream & inn) : Maaltid(inn)  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2F - Leser inn (hoved)retten under lunsjen.
 */
void Lunsj::lesData()  {
    kaffe = lesInt("Er det kaffe til ", 0, 1);
}


/**
 *  Oppgave 2C - Skriver ut på skjermen ALLE datamedlemmene.
 */
void Lunsj::skrivData() const  {
    std::cout << (kaffe ? "Det er kaffe\n" : "Ingen kaffe\n");
}


/**
 *  Oppgave 2I - Leser inn fra fil 'Middag' sine tre datamedlem.
 *
 *  @param    inn  -  Filen det leses inn fra
 */
Middag::Middag(ifstream & inn) : Maaltid(inn)  {

}


/**
 *  Oppgave 2F - Leser inn evt rettene og drikken under middagen.
 */
void Middag::lesData()  {
        std::cout << "Forret : ";
        std::getline(std::cin, forrett);
        std::cout << "Desert : ";
        std::getline(std::cin, dessert);
        std::cout << "Drikke : ";
        std::getline(std::cin, drikke);
}


/**
 *  Oppgave 2C - Skriver ut på skjermen ALLE datamedlemmene.
 */
void Middag::skrivData() const  {
    std::cout << "Forret : " << forrett <<
              " Desert : " << dessert << " Drikke : "
              << drikke << std::endl;
}


/**
 *  Oppgave 2B- Finner og returnerer (om mulig) peker til et gitt spisested.
 *
 *  @param    navn  -  Navnet på det søkte spisestedet
 *  @return   Peker til aktuelt navngitt spisested eller nullptr
 */
Spisested* finnSpisested(const string navn)  {

    auto it = std::find_if(gSpisestedene.begin(), gSpisestedene.end(), [&navn]
            (const auto & obj){return obj->hentID() == navn;});

    if (it == gSpisestedene.end())
        return nullptr;

    return (*it);
}


/**
 *  Oppgave 2H - Frigir/sletter ALT allokert minne/memory.
 */
void frigiAllokertMinne()  {
    for (auto & val : gSpisestedene) {
        delete val;
    }
    gSpisestedene.clear();
}



/**
 *  Oppgave 2I - Leser ALLE spisestedene med måltider inn fra fil.
 */
void lesFraFil()  {
    std::ifstream inn("SPISESTEDER.dta");



}


/**
 *  Oppgave 2F - Legger inn (om mulig) ett nytt måltid på et spisested.
 */
void nyttMaaltid()  {

    if (gSpisestedene.empty()) {
        std::cout << "Ingen spisesteder" << std::endl;
        return;
    }

    std::string navn;
    std::cout << "Skriv navn : ";
    std::getline(std::cin, navn);
    auto ptr = finnSpisested(navn);
    if (ptr == nullptr) {
        std::cout << "Spise Sted finnes ikke" << std::endl;
        return;
    }
    ptr->nyttMaaltid();
}


/**
 *  Oppgave 2D - Legger inn (om mulig) ett nytt spisested.
 */
void nyttSpisested()  {
    std::string navn;
    std::cout << "Skriv navn : ";
    std::getline(std::cin, navn);
    auto ptr = finnSpisested(navn);
    if (ptr != nullptr) {
        std::cout << "Finnes allerede" << std::endl;
        return;
    }

    Spisested *nySpis = new Spisested(navn);

    nySpis->lesData();

    gSpisestedene.push_back(nySpis);
    gSpisestedene.sort([](const Spisested*p1, const Spisested*p2)
                       {return p1 < p2;});
}


/**
 *  Oppgave 2A - Skriver ut på skjermen HOVEDdataene om ALLE spisesteder.
 */
void skrivAlleSpisesteder()  {
    if (gSpisestedene.empty()) {
        std::cout << "Ingen Spisesteder" << std::endl;
        return;
    }
    for (const auto & val : gSpisestedene)
        val->skrivHovedData();
}


/**
 *  Oppgave 2C - Skriver ut på skjermen ALLE data om ETT gitt spisested.
 */
void skrivEttSpisested()  {
    if (gSpisestedene.empty()) {
        std::cout << "Finnes ingen spisesteder" << std::endl;
        return;
    }
    std::string navn;
    std::cout << "Skriv navn : ";
    std::getline(std::cin, navn);

    auto ptr = finnSpisested(navn);
    if (ptr == nullptr) {
        std::cout << "Dette finnes ikke" << std::endl;
        return;
    }

    ptr->skrivAlleData();
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny()  {
    cout << "\nFølgende kommandoer er tilgjengelige:\n"
         << "   A  - skriv Alle spisesteder\n"
         << "   E  - skriv Ett spisested\n"
         << "   S  - nytt Spisested\n"
         << "   M  - nytt Maaltid\n"
         << "   D  - steder spist paa en gitt Dato\n"
         << "   Q  - Quit / avslutt\n";
}


/**
 *  Oppgave 2G - Skriver ut på skjermen (om mulig) alle måltider spist en
 *               gitt dato, og på hvilket spisested dette har forekommet.
 */
void spistEnGittDato()  {
    std::list <Maaltid*> dummy;

    int dato = lesInt("Skriv dato ", 0, 9999);

    Maaltid *ph = nullptr;

    for (const auto & val : gSpisestedene) {
        if ((ph = val->finnMaaltidPaaDato(dato)) != nullptr) {
            dummy.push_back(ph);
            val->skrivHovedData();
            ph->skrivData();
        }
    }

    if (dummy.empty())
        std::cout << "Ingen maaltider finnes i denne datoen" << std::endl;

    dummy.clear();
}
