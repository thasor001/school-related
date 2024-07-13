//
// Created by Tharald on 2/21/2024.
//

// No need to include things such as <iostream> as they are already inside LesData2.h
#include "LesData2.h"
#include <vector>
#include <string>

/**
 * Customer class
 */
class Customer {
private:
    std::string name;
    ///< Vector with float's pointing to accounts.
    std::vector <float>* accounts;
public:
    Customer(const int n) : accounts(new std::vector <float>){
        // Line above allocates space for an "accounts" vector.
        for (int i = 0; i < n; i++) {
            // Fills vector up with 0.0
            accounts->push_back(0.0);
        }
        std::cout << "\n--Created : " << n << " Accounts--\n";
        Customer::readData();
    }
    ~Customer() {
        std::cout << "\t-Deleted Customer : -" << name
        << "- And " << accounts->size() << " Associated Accounts" << "\n";
        // Clears the account vector.
        accounts->clear();
        // Deletes the accounts' pointer.
        delete accounts;
    }
    // Getname function that compares names (sends in const of original).
    bool getName(const std::string & name) {
        return (this->name == name);
    }

    void readData() {
        std::cout << "\nAccount Owner Name : ";
        std::getline(std::cin, name);
        for (int i = 0; i < accounts->size(); i++) {
            std::cout << "Account Number " << i+1;
            // since we currently are working with a pointer to accounts, we need to go into that pointer,
            // we do that by pointing into what the pointer points to. **
            (*accounts)[i] = lesFloat(" | Write Amount $ in Account ", 1, 1000);
        }
    }
    void writeData() {
        float sum = 0;
        std::cout << "\nAccount Owner : " << name << "\n";
        // to work with the original values inside accounts, we need to de-reference it.
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
int findName(const std::string & name);

///< Vector with Customer class pointers.
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
                    // Since the "Customer" that is inside gCustomers are pointers, we go inside it with "->".
                    customer->writeData();
                }
                break;
            case 'D':
                std::cout << "\nWrite Name : ";
                std::getline(std::cin, name);
                // We don't care about keeping what's inside name after findName function,
                // Therefore we can change its value from Ivalue to Xvalue using std::move(),
                // which should result in efficient transfer with no unnecessary copying.
                // Overkill.
                if ((n = findName(std::move(name))) == -1) {
                    std::cout << "Customer Does Not Exist\n";
                } else {
                    // First we delete the pointer that contains the customer.
                    delete gCustomers[n];
                    // Then we delete the spot that the deallocated customer was at.
                    // .erase function erases the spot and automatically shoves the elements in front,
                    // to the back, .erase takes an iterator "gCustomer.begin()" and then the element to go to "n".
                    gCustomers.erase(gCustomers.begin() + n);
                }
                break;
            default:menu(); std::cout << "Illegal command : " << command << "\n"; break;
        }

        command = lesChar("\nWrite command ");
    }

    // De-allocates all pointers in gCustomers.
    for (auto & val : gCustomers) {
        delete val;
    }
    // Clears all the de allocated pointers and reserved memory in the vector.
    gCustomers.clear();

    return 0;
}

// Same as ever.
int findName(const std::string & name) {
    for (int i = 0; i < gCustomers.size(); i++) {
        if(gCustomers[i]->getName(name)) {
            return i;
        }
    }
    return -1;
}