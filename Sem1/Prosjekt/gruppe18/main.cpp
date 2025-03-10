/**
 * Hovedprogrammet for prosjektet
 *
 * @File main.cpp
 * @Author Gruppe18
 */

#include "Byer.h"
#include "funksjoner.h"
#include "Turoperatorer.h"

Byer gByerBase;                 ///< Globale konteiner objekt for by-er.
Turoperatorer gOprasjonsBase;   ///< Globale konteiner objekt for turoperator-er.

/**
 * @See egenLesChar()
 */
int main() {
    skrivMeny();

    char valg;

    do {
        valg = egenLesChar("Skriv char her", "TBA");

        switch (valg) {
            case 'T': gOprasjonsBase.handlinger();        break;
            case 'B': case 'A': gByerBase.handling(valg); break;
        }
    } while(valg != 'Q');

    std::cout << "\nSkriver til Byer.dta2\n";
    gByerBase.skrivTilFil();

    std::cout << "\nSkriver til fil : Turoperatorer.dta2";
    gOprasjonsBase.skrivTilFil();

    std::cout << "\n--Program Ended--\n";
    std::cin.get();
    return 0;
}