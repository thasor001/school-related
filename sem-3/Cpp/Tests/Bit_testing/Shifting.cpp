#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

void printBinary(const int & num) {
    for (int i = 31; i >= 0; --i) {
        std::cout << ((num >> i) & 1);
        if (i % 8 == 0) std::cout << ' ';
    }
    std::cout << std::endl;
}


int main() {
    std::vector <int> numbers {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000000; i++)
        std::for_each(numbers.begin(), numbers.end(), [](int & n)
        {if (!(n & 1)) n++;});

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    std::for_each(numbers.begin(), numbers.end(), [](int & n)
    {if ((n & 1)) std::cout << n << " is Odd.\n";});


    std::for_each(numbers.begin(), numbers.end(), [](int & n)
    {if (n%2 == 0) n++;});

    int tall = 1;
    std::cout << tall << std::endl;

    std::cout << tall << std::endl;

    printBinary(tall);

    tall = ~tall + 1;

    printBinary(tall);

    std::cout << tall << std::endl;

    tall = ~tall + 1;

    std::cout << tall << std::endl;

    tall = 400;
    std::cout << "\ntall: \t" << tall << std::endl;
    printBinary(tall);

    std::cin.get();
    return 0;
}