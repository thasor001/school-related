#include "Byer.h"
#include <iostream>
#include "Opplegg.h"
#include "funksjoner.h"
#include "Turoperatorer.h"
namespace sm = system_messages;

Byer gByerBase;
Turoperatorer gOprasjonsBase;
Opplegg gOppleggsBase;

int main() {

    skrivMeny();

    char valg;

    do {
        valg = egenLesChar("Skriv char her", "TBA");

        switch (valg) {
            case 'T': gOprasjonsBase.handlinger();            break;
                case 'B': case 'A': gByerBase.handling(valg); break;
            default:
                if (valg != 'Q')
                    sm::sys_error("Wrong command : ");
                break;
        }
    } while(valg != 'Q');

    sm::sys_info("\nSkriver til Byer.dta2\n");
    gByerBase.skrivTilFil();

    sm::sys_info("\nSkriver til fil : Turoperatorer.dta2");
    gOprasjonsBase.skrivTilFil();

    sm::sys_print("Program Ended");
    std::cin.get();
    return 0;
}

