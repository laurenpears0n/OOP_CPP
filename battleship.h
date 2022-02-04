// PHYS 30762 Programming in C++
// Project - Board Game
// Lauren Pearson

// Battleship Board Game
// Battleship Header File

#include<iostream>
#include<string>
#include"ship.h"

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

// Derived class for battleship
class battleship: public ship
{
public:
    // Constructor, member functions and destructor
    battleship() 
    {
        name="Battleship";
        ship_length=4; 
        hits=0;
    }
    int length() {return ship_length;}
    std::string return_name() {return name;}
    void print_info() {std::cout<<"Battleship, with length "<<length()<<std::endl;}
    ~battleship() {}
};

#endif