//
// Created by Tharald on 09/04/2024.
//

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

std::vector <int> gVec;

template <typename P1, typename P2, typename PRED>
void for_each_if (P1 p_start, P2 p_end, PRED pred) {
    for (; p_start != p_end; p_start++)
        if (pred(*p_start)) {

        }
}

template <template <typename> class container, typename T, typename  P1, typename P2, typename PRED>
container <T> for_index (P1 p_start, P2 p_end, PRED pred) {
    container <T> indecies;
    for (auto it = p_start; it != p_end; it++)
        if (pred(*it)) {
            indecies.push_back(std::distance(p_start, it));
        }
    return indecies;
}


int main() {
    gVec = {10, 2, 4, 5, 7, 1, 6, 57};

    auto predicate = [](const auto x) {return x > 9;};

    auto newVec = for_index<std::vector, int>(gVec.begin(), gVec.end(), predicate);

    std::for_each(newVec.begin(), newVec.end(), [](const auto x){std::cout << x << " ";});


    std::cin.get();
    return 0;
}