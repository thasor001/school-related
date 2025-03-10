//
// Created by Tharald on 08/03/2024.
//


#include "iostream"
#include "vector"
#include "stack"
#include "queue"
#include "string"
#include "map"
#include "list"
#include "algorithm"

std::list <int> myList;
std::map <std::string, int> myMap;

int main(){

    for (int i = 0; i < 11; i++) {
        myList.push_back(i*i);
    }

    auto it = std::find(myList.begin(), myList.end(), 100);
    if (*it == 100) {
        myList.erase(it);
    }

    for (auto & val : myList) {
        std::cout << val << std::endl;
    }

    int x = 0;
    std::for_each(myList.begin(), myList.end(),
                  [&x] (const auto & val)
                  {std::cout << ++x  << " Element : " << val << std::endl;});

    for (int i = 0; i < 20; i++) {
        myMap[std::to_string(i*i/3)] = i*2+7;
    }

    std::cout << "-------------------------" << std::endl;
    for (const auto & pair : myMap) {
        std::cout << "Key : " << pair.first << " Value : " << pair.second << std::endl;
    }

    std::cout << "-------------------------" << std::endl;
    x = 0;
    std::for_each(myMap.begin(), myMap.end(),
                  [&x](auto & pair){std::cout << "Key Number : "
                  << ++x << " Value : " << ++pair.second << std::endl;});

    // auto & val == rvalue
    // so when you send in a variable that is not a rvalue aka variables
    // you need to make val -> const : const auto & val.
    auto a = [] (const auto & val)->int {return val * 2;};
    std::cout << std::endl << a('A') << std::endl;

    // auto & val = rvalue, therefore I can send in a variable.
    auto b = [] (auto & val) {return 1;};
    std::cout << std::endl << b(x) << std::endl;

    return 0;
}
