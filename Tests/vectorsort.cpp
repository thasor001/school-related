#include "vector"
#include "iostream"

int main() {
    std::vector <int> hello {1, 5, 67, 2, 3, 5, 8, 9, 100, 10};

    for (auto const val : hello) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    
    for (auto const val : hello) {
        std::cout << val << " ";
    }

    std::cin.get();
    return 0;
}