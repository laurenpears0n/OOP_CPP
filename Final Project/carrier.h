// PHYS 30762 Programming in C++
// Project - Board Game
// Lauren Pearson

// Battleship Board Game
// Carrier Header File

#include<iostream>
#include<string>
#include"ship.h"

#ifndef CARRIER_H
#define CARRIER_H

// Derived class for carrier
class carrier: public ship
{
public:
    // Constructor, member functions and destructor
    carrier()
    {
        name="Carrier";
        ship_length=5;
        hits=0;
    }
    int length() {return ship_length;}
    std::string return_name() {return name;}
    void print_info() {std::cout<<"Carrier, with length "<<length()<<std::endl;}
    ~carrier() {}
};

#endif