#include "Opplegg.h"

extern Byer gByerBase;                  ///< Extern-et Byer objekt.
extern Turoperatorer gOprasjonsBase;    ///< Extern-et Turoperatorer objekt.

/**
 * Funksjon som lager ett nytt opplegg for en turoperator.
 *
 * @See lesInt()
 * @See Entydig()
 * @See Byer::getMap()
 * @See Byer::skrivAlle()
 * @See By::skrivAlt()
 * @See Attraksjon::getList()
 * @See Attraksjon::writeID()
 * @See egenLesChar()
 *
 *
 * @param Operator Navn paa Tur Opperatoren.
 * @param opplegg Antall opplegg til Opperatoren.
 */
void Opplegg::nyttOpplegg(const std::string & Operator, int & opplegg) {

    std::list <Attraksjon*> at;
    std::string navn, beskrivelse;
    int nr, antDager;
    int dag = 1;
    char valg;

    std::cout << "Skriv Beskrivelse av Opplegg : ";
    std::getline(std::cin, beskrivelse);

    antDager = lesInt("Hvor lenge varer Opplegget ", 1, maxDager);
    std::cout << std::endl;

    do {
        valg = '-';
        // Skriv by navn til det er entydig.
        while (!Entydig("By til dag : " + std::to_string(dag), navn,
                        gByerBase.getMap().begin(), gByerBase.getMap().end()))
            gByerBase.skrivAlle();

        // Skriv alt til den entydige byen.
        auto it = gByerBase.getMap().find(navn);
        std::cout << "\nNavn : " + navn;
        it->second->skrivAlt();

        std::cout << "\n0 = Avslutt\n";
        std::cout << "\nDag Nr : " + std::to_string(dag) + "\n\n";

        do {
            // Hent aktuelle Attraksjon.
            nr = lesInt("Legg til attraksjon nr", 0, it->second->getList().size());
            auto iter = it->second->getList().begin();
            std::advance(iter, nr-1);

            if (std::find(at.begin(), at.end(), (*iter)) == at.end() && nr != 0) {
                at.push_back((*iter));
                std::cout << "\nLa til : " + (*iter)->writeID() + "\n\n";
            }

            // Hvis Attraksjon allerede lagt inn i dag og by, ikke legg til attraksjon.
            else if (std::find(at.begin(), at.end(), (*iter)) != at.end() && nr != 0)
                std::cout << "\n" << (*iter)->writeID()
                          << " Finnes allerede i Listen\n\n";
            else {
                if (dag < antDager)
                    valg = egenLesChar("S(amme dag), N(este dag), Q(uit)", "SN");
                else
                    valg = egenLesChar("S(amme dag), Q(uit)", "S");

                Dager.push_back({{dag, navn}, at});
                at.clear();
                if (valg == 'N')
                    dag++;
            }
        } while(valg == '-');
    } while(valg != 'Q');

    // Cout info.
    std::cout << "\n" << beskrivelse << std::endl;
    int temp = -1;
    for (const auto & val : Dager) {
        if (temp != val.first.first) {
            std::cout << "\n\tDag Nr : " << val.first.first << "\n";
            temp = val.first.first;
        }
        std::cout << "\t" << val.first.second << "\n";
        for (const auto & atr : val.second)
            std::cout << "\t\t" << atr->writeID() << std::endl;
    }
    valg = egenLesChar("Lagre paa fil", "JN");

    // Skriv til fil.
    if (valg == 'J') {
        std::string buffer = std::to_string(opplegg + 1);
        while (buffer.size() < 3)
            buffer.insert(0, "0");

        std::string file = Operator+"-"+buffer+'-'
                +std::to_string(Dager[Dager.size()-1].first.first)+"dg";
        std::ofstream ut(file + ".dta");

        if (!ut) {
            std::cout << "\n--Kunne ikke aapne : " + file << "--\n";
            return;
        }
        std::cout << "\n--" << file + " Aapnet--\n";

        ut << beskrivelse << std::endl;
        temp = -1;
        for (const auto & val : Dager) {
            if (temp != val.first.first) {
                ut << "\tDag Nr : " << val.first.first << "\n";
                temp = val.first.first;
            }
            ut << "\t" << val.first.second << "\n";
            for (const auto & atr : val.second)
                ut << "\t\t" << atr->writeID() << std::endl;
        }

        ut.close();
        std::cout << "\n--" << file + " Lukket--\n";
        // Ant opplegg ++
        opplegg++;
    }
    // Clear vector.
    Dager.clear();
}