//
// Created by thara on 3/28/2024.
//

#ifndef CPP_ENUM_H
#define CPP_ENUM_H

// Bruker unsigned char siden det ikke er en trang for 32 bit integers
// Naar vi bare skal bruker 0, 1, 2.
// Unsigned char = 8 bit integer.
enum Ktype : unsigned char {
    katedral, kirke, kapell
};



#endif //CPP_ENUM_H
