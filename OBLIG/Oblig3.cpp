//
// Created by Tharald on 05/03/2024.
//
/**
 *   Skjelett for obligatorisk oppgave nr 3 i PROG1003 - OOP.
 *
 *   Programmet inneholder en oversikt over studenter og ansatt på en skole.
 *   Disse er identifisert via sitt UNIKE student-/ansattnummer,
 *   og alle ligger lagret i EN <map>. Brukeren/programmet kan:
 *       - se ALLE personene som er lagret i datastrukturen (map'en)
 *       - legge inn en ny student/ansatt
 *       - endre data om en gitt student/ansatt
 *       - HELE datastrukturen leses fra/skrives til fil
 *
 *   @file    OBLIG3.TPL
 *   @author  Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <string>
#include <map>
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data


/**
 *  Person (med navn).
 */
class Person {
private:
    std::string navn;
public:
    Person()  {  navn = "";  }
    Person(std::ifstream & inn);
    virtual void endreData() = 0;
    virtual void lesData();
    virtual void skrivData() const;
    virtual void skrivTilFil(std::ofstream & ut) const;
};


/**
 *  Student (med studieprogram/klasse og antall studiepoeng).
 */
class Student : public Person {
private:
    std::string studieprogram;
    float  stp;
public:
    Student()  {  studieprogram = "";  stp = 0.0F;  }
    Student(std::ifstream & inn);
    virtual void endreData();
    virtual void lesData();
    virtual void skrivData() const;
    virtual void skrivTilFil(std::ofstream & ut) const;
};


/**
 *  Ansatt (med rom-/kontornummer og årslønn).
 */
class Ansatt : public Person {
private:
    std::string rom;
    int    lonn;
public:
    Ansatt()  {  rom = "";  lonn = 0;  }
    Ansatt(std::ifstream & inn);
    virtual void endreData();
    virtual void lesData();
    virtual void skrivData() const;
    virtual void skrivTilFil(std::ofstream & ut) const;
};


void endreEnPerson();
void lesFraFil();
void nyPerson();
void skrivAllePersoner();
void skrivMeny();
void skrivTilFil();


std::map <int, Person*> gPersoner;      ///<  Datastrukturen med alle personene.


/**
 *  Hovedprogrammet:
 */
int main(void)  {
    char kommando;

    lesFraFil();

    skrivMeny();
    std::cout << std::endl;
    kommando = lesChar("Kommando");

    while (kommando != 'Q') {
        switch (kommando) {
            case 'N':  nyPerson();               break;
            case 'A':  skrivAllePersoner();      break;
            case 'E':  endreEnPerson();          break;
            default:   skrivMeny();              break;
        }
        kommando = lesChar("Kommando");
    }

    skrivTilFil();

    return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Leser navnet fra fil.
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Person::Person(std::ifstream & inn) {
    inn.ignore();
    std::getline(inn, navn);
}


/**
 *  Leser navnet fra brukeren/tastaturet.
 */
void Person::lesData() {
    std::cout << "Write Name : ";
    std::getline(std::cin, navn);
}


/**
 *  Skriver ut navnet til/på skjermen.
 */
void Person::skrivData() const {
    std::cout << "Name: " << navn << ", ";
}


/**
 *  Skriver ut navnet til fil.
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 */
void Person::skrivTilFil(std::ofstream & ut) const {
    ut << navn << std::endl;
}


// ---------------------------------------------------------------------------

/**
 *  Leser studiepoeng og studieprogram/klasse fra fil.
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Student::Student(std::ifstream & inn) : Person(inn) {
    inn >> stp;
    inn.ignore();
    std::getline(inn, studieprogram);
}


/**
 *  Tilbyr brukren å endre på alle egne data.
 *
 *  @see  skrivData()
 */
void Student::endreData() {
    std::cout << "Write Study program : ";
    std::getline(std::cin, studieprogram);
    stp = lesFloat("Write Study points ", 0, 300);
}


/**
 *  Leser baseklassens data, studieproram/klasse og studiepoeng fra brukeren.
 *
 *  @see   Person::lesData()
 */
void Student::lesData() {
    Person::lesData();
    std::cout << "Write Study program : ";
    std::getline(std::cin, studieprogram);
    stp = lesFloat("Write Study points ", 0, 300);
}


/**
 *  Skriver baseklassens data, studieproram/klasse og studiepoeng til skjerm.
 *
 *  @see  Person::skrivData()
 */
void Student::skrivData() const {
    Person::skrivData();
    std::cout << "stp: " << stp
    << ", Study program: " << studieprogram << std::endl;
}


/**
 *  Skriver 'S', baseklassens data, studiepoeng og studieprogram til fil.
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 *  @see     Person::skrivTilTil(...)
 */
void Student::skrivTilFil(std::ofstream & ut) const {
    Person::skrivTilFil(ut);
    ut << stp << " " << studieprogram << std::endl;
}


// ---------------------------------------------------------------------------

/**
 *  Leser årslønn og rom/kontor fra fil.
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Ansatt::Ansatt(std::ifstream & inn) : Person(inn) {
    inn >> lonn;
    inn.ignore();
    std::getline(inn, rom);
}


/**
 *  Tilbyr brukren å endre på alle egne data.
 *
 *  @see  skrivData()
 */
void Ansatt::endreData() {
    lonn = lesInt("Write lonn", 0, 999999999);
    std::cout << "Write room : ";
    std::getline(std::cin, rom);
}


/**
 *  Leser baseklassens data, rom/kontor og årslønn fra brukeren.
 *
 *  @see   Person::lesData()
 */
void Ansatt::lesData() {
    Person::lesData();
    lonn = lesInt("Write lonn", 0, 999999999);
    std::cout << "Write room : ";
    std::getline(std::cin, rom);
}


/**
 *  Skriver baseklassens data, rom/kontor og årslønn til/på skjermen.
 *
 *  @see  Person::skrivData()
 */
void Ansatt::skrivData() const {
    Person::skrivData();
    std::cout << "Salary: " << lonn
    << ", room: " << rom << std::endl;
}


/**
 *  Skriver 'A', baseklassens data, årslønn og rom/kontor.
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 *  @see     Person::skrivTilTil(...)
 */
void Ansatt::skrivTilFil(std::ofstream & ut) const {
    Person::skrivTilFil(ut);
    ut << lonn << " " << rom << std::endl;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Lar brukeren (om mulig) endre dataene for et avledet objekt (subklasse).
 *
 *  @see   virtual Person::endreData()
 */
void endreEnPerson() {
    int nr = lesInt("Write Number ", 1, 100000);
    for (auto & it : gPersoner) {
        if (it.first == nr) {
            it.second->endreData();
            break;
        }
        std::cout << "Person does not exist." << std::endl;
        return;
    }
}


/**
 *  Leser ALLE personer inn fra fil, og legger de inn i 'gPersoner'.
 */
void lesFraFil() {
    std::ifstream file("OBLIG3.dta");
    int nr;
    char type;

    if (!file) {
        std::cout << "Could not find file" << std::endl;
        return;
    }

    while (file >> nr >> type) {
        switch (type) {
            case 'A':
                gPersoner[nr] = new Ansatt(file);
                break;
            case 'S':
                gPersoner[nr] = new Student(file);
                break;
            default: std::cout << "Wrong file structure" << std::endl; return;
        }

    }
    std::cout << "All lines read." << std::endl;
    file.close();
}


/**
 *  Legger inn (om mulig) en ny person.
 *
 *  @see   virtual Person::lesData()
 */
void nyPerson() {
    Person * newPes;
    char type = lesChar("Write Type (A/S)");
    int nr;
    
    std::cout << std::endl;
    switch (type) {
        case 'A':
            nr = lesInt("Write Number ", 1, 1000);
            for (auto & it : gPersoner) {
                if (it.first == nr) {
                    std::cout << "Ansatt exists." << std::endl;
                    return;
                }
            }
            newPes = new Ansatt;
            newPes->lesData();
            gPersoner[nr] = newPes;
            break;
        case 'S':
            nr = lesInt("Write Number ", 1001, 100000);
            for (auto & it : gPersoner) {
                if (it.first == nr) {
                    std::cout << "Ansatt exists." << std::endl;
                    return;
                }
            }
            newPes = new Student;
            newPes->lesData();
            gPersoner[nr] = newPes;
            break;
        default: std::cout << "Wrong Input" << std::endl; return;
    }

}


/**
 *  Skriver alle dataene om alle personene ut på skjermen.
 *
 *  @see   virtual Person::skrivData()
 */
void skrivAllePersoner() {
    for (auto & it : gPersoner) {
        it.second->skrivData();
    }
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny() {
    std::cout << "\nFølgende kommandoer er tilgjengelig:\n"
         << "\tN - Ny person (student eller ansatt)\n"
         << "\tA - skriv Alle personer\n"
         << "\tE - Endre EN gitt person\n"
         << "\tQ - Quit / avslutt\n\n";
}


/**
 *  Skriver hele datastrukturen til fil.
 *
 *  @see   virtual Person::skrivTilFil(...)
 */
void skrivTilFil() {
    std::ofstream file("OBLIG3.dta");

    for (auto & it : gPersoner) {
        file << it.first << " ";
        if (it.first < 1001) {
            file << "A ";
        } else {
            file << "S ";
        }
        it.second->skrivTilFil(file);
    }

    file.close();
}