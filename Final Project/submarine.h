// PHYS 30762 Programming in C++
// Project - Board Game
// Lauren Pearson

// Battleship Board Game
// Submarine Header File

#include<iostream>
#include<string>
#include"ship.h"

#ifndef SUBMARINE_H
#define SUMBARINE_H

// Derived class for submarine
class submarine: public ship
{
public:
    // Constructor, member functions and destructor
    submarine()
    {
        name="Submarine";
        ship_length=3;
        hits=0;
    }
    int length() {return ship_length;}
    std::string return_name() {return name;}
    void print_info() {std::cout<<"Submarine, with length "<<length()<<std::endl;}
    ~submarine() {}
};


#endif