// PHYS 30762 Programming in C++
// Project - Board Game
// Lauren Pearson

// Battleship Board Game
// Destroyer Header File

#include<iostream>
#include<string>
#include"ship.h"

#ifndef DESTORYER_H
#define DESTORYER_H

// Derived class for destroyer
class destroyer: public ship
{
public:
    // Constructor, member functions and destructor
    destroyer()
    {
        name="Destroyer";
        ship_length=3;
        hits=0;
    }
    int length() {return ship_length;}
    std::string return_name() {return name;}
    void print_info() {std::cout<<"Destroyer, with length "<<length()<<std::endl;}
    ~destroyer() {}
};

#endif