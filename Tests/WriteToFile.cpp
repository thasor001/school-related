#include "fstream"
#include "iostream"




int main() {
    std::ofstream out(R"(C:\Users\Tharald\CLionProjects\Cpp\Tests\outFile.dta)", std::ios::out);

    int number = 10;

    out << "Hello World" << std::endl << "This is on line 2 :\n" << "line 3 : number : " << number;

    return 0;
}