//
// Created by Tharald on 2/21/2024.
//
#include "LesData2.h"
#include <vector>
#include <string>

class Customer {
private:
    std::string name;
    std::vector <float>* accounts;
public:
    Customer(const int n) : accounts(new std::vector <float>()){
        for (int i = 0; i < n; i++) {
            accounts->push_back(0.0);
        }
        std::cout << "--Created : " << n << " Accounts--\n";
        Customer::readData();
    }
    ~Customer() {
        std::cout << "\t-Deleted Customer : -" << name
        << "- And " << accounts->size() << " Associated Accounts" << "\n";
        accounts->clear();
    }
    bool getName(std::string name) {
        return (this->name == name);
    }

    void readData() {
        std::cout << "\nAccount Owner Name : ";
        std::getline(std::cin, name);
        for (int i = 0; i < accounts->size(); i++) {
            std::cout << "Account Number : " << i+1;
            (*accounts)[i] = lesFloat("Write Amount $ in Account ", 1, 1000);
        }
    }
    void writeData() {
        float sum = 0;
        std::cout << "\nAccount Owner : " << name << "\n";
        for (auto & val : *accounts) {
            sum += val;
        }
        std::cout << "Amount of Accounts : " << accounts->size()
        << " | Sum of All Accounts : " << sum << " |\n";
    }
};

void menu() {
    std::cout << "\nN - New Customer"
    << "\tW - Write all customers"
    << "\tD - Delete customer by name\n\n";
}
int findName(std::string name);

std::vector <Customer*> gCustomers;

int main() {
    Customer * newCustomer;
    int n;
    std::string name;

    menu();

    char command = lesChar("Write command ");
    while (command != 'Q') {
        switch (command) {
            case 'N':
                n = lesInt("Write amount of accounts : ", 1, 20);
                newCustomer = new Customer(n);
                gCustomers.push_back(newCustomer);
                break;
            case 'W':
                for (auto & customer : gCustomers) {
                    customer->writeData();
                }
                break;
            case 'D':
                std::cout << "\nWrite Name : ";
                std::getline(std::cin, name);
                if ((n = findName(name)) == -1) {
                    std::cout << "Customer Does Not Exist\n";
                    break;
                }
                delete gCustomers[n];
                break;
            default:menu(); std::cout << "Illegal command : " << command << "\n"; break;
        }

        command = lesChar("Write command ");
    }

    for (auto & val : gCustomers) {
        delete val;
    }
    gCustomers.clear();

    return 0;
}

int findName(std::string name) {
    for (int i = 0; i < gCustomers.size(); i++) {
        if(gCustomers[i]->getName(name)) {
            return i;
        }
    }
    return -1;
}