//
// Created by Tharald on 25/01/2024.
//

#import <iomanip>
#import <string>
#import "LesData2.h"
using namespace std;

int main() {
    string str1 = "Bendik i hate you";
    string str2 = str1;
    string str3(100, '!');
    cout << str1 << "\n" << str2 << "\n" << str3 << "\n";

    if (str1 == str2) {
        cout << "Strings the same :)! \n";
    } else {
        cout << "Strings are not the same \n";
    }

    str2 = "aaaa";
    str1 ="bbb";

    if (str2 > str1) {
        cout << str2 << " biggest " << "\n";
    } else {
        cout << str1 << " biggest " << "\n";
    }

    cout << "\nWrite string";
    getline(cin, str3);
    cout << str3 << "\n";

    str3 = str1 + ", Hello world :) " + str2 + ", OMG!!";
    cout << str3 << "\n";


    string s;


    return 0;
}
