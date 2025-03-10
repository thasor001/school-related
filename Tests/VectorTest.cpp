//
// Created by Tharald on 01/03/2024.
//

#include <vector>
#include <iostream>

std::vector<int> numbers;


int main() {
    for (int i = 0; i < 10; i++) {
        numbers.push_back(i);
    }
    std::cout << numbers.capacity() << std::endl;
    numbers.resize(8);
    std::cout << numbers.capacity() << std::endl;

    for (auto & val : numbers) {
        std::cout << val << std::endl;
    }

    return 0;
}
