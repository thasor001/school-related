//
// Created by Tharald on 24/02/2024.
//

#include "Task16.h"
#include "vector"

std::vector <Publications*> gPub;

int main() {
    std::ifstream in("C:\\Users\\Tharald\\CLionProjects\\Cpp\\WeekTasks\\Task16.dta");
    char pub;
    if (!in) {
        std::cout << "Could not open file" << std::endl;
        return -1;
    }

    while (!in.eof()) {
        in >> pub;
        switch (pub) {
            case 'B':
                gPub.push_back(new Bok(in));
                break;
            case 'M':
                gPub.push_back(new Magazine(in));
                break;
            default:
                std::cout << "File Structure is wrong" << std::endl;
                return -1;
        }
    }

    std::ofstream out("C:\\Users\\Tharald\\CLionProjects\\Cpp\\WeekTasks\\Task16.dt2");
    for (auto & val : gPub) {
        val->writeToFile(out);
        delete val;
    }
    gPub.clear();

    in.close();
    out.close();
    return 0;
}