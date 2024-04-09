#include "Opplegg.h"
namespace sm = system_messages;

extern Byer gByerBase;
extern Turoperatorer gOprasjonsBase;

void Opplegg::nyttOpplegg(const std::string & Operator, int & opplegg) {

    std::list <Attraksjon*> at;
    std::string navn;
    std::string beskrivelse;
    std::string SNQ = "SNQ";
    int nr;
    int dag = 1;
    int antDager;
    char valg;

    std::cout << "Skriv Beskrivelse av Opplegg : ";
    std::getline(std::cin, beskrivelse);

    antDager = lesInt("Hvor lenge varer Opplegget ", 1, 30);
    std::cout << std::endl;

    do {
        valg = '-';
        while (!Entydig("By til dag : " + std::to_string(dag), navn,
                        gByerBase.getMap().begin(), gByerBase.getMap().end())) {
            gByerBase.skrivAlle();
        }

        auto it = gByerBase.getMap().find(navn);
        sm::sys_info("\nNavn : " + navn);
        it->second->skrivAlt();

        sm::sys_info("\n0 = Avslutt\n");
        sm::sys_info("\nDag Nr : " + std::to_string(dag) + "\n\n");

        do {
            nr = lesInt("Legg til attraksjon nr", 0, it->second->getList().size());
            auto iter = it->second->getList().begin();

            std::advance(iter, nr-1);
            if (std::find(at.begin(), at.end(), (*iter)) == at.end() && nr != 0) {
                at.push_back((*iter));
                sm::sys_info("\nLa til : " + (*iter)->writeID() + "\n\n");
            }

            else if (std::find(at.begin(), at.end(), (*iter)) != at.end() && nr != 0) {
                std::cout << "\n" << (*iter)->writeID()
                          << " Finnes allerede i Listen\n\n";
            }
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
        } while(SNQ.find(valg) == std::string::npos);
    } while(valg != 'Q');

    std::cout << "\n" << beskrivelse << std::endl;
    int temp = -1;
    for (auto & val : Dager) {
        if (temp != val.first.first) {
            std::cout << "\n\tDag Nr : " << val.first.first << "\n";
            temp = val.first.first;
        }
        std::cout << "\t" << val.first.second << "\n";
        for (auto & atr : val.second) {
            std::cout << "\t\t" << atr->writeID() << std::endl;
        }
    }
    valg = egenLesChar("Lagre paa fil", "JN");

    if (valg == 'J') {
        opplegg++;
        std::string buffer = std::to_string(opplegg);
        while (buffer.size() < 3)
            buffer.insert(0, "0");

        std::string file = Operator+"-"+buffer+'-'+std::to_string(antDager)+"dg";
        std::ofstream ut(file + ".dta");

        if (!ut) {
            sm::sys_error("Kunne ikke aapne : " + file);
            return;
        }
        sm::sys_print(file + " Aapnet");

        ut << beskrivelse << std::endl;

        for (auto & val : Dager) {
            ut << "\tDag Nr : " << val.first.first
               << "\t" << val.first.second << "\n";
            for (auto & atr : val.second) {
                ut << "\t\t" << atr->writeID() << std::endl;
            }
        }

        ut.close();
        sm::sys_print(file + " Lukket");
    }
    Dager.clear();
}