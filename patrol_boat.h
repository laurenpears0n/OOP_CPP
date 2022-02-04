// PHYS 30762 Programming in C++
// Project - Board Game
// Lauren Pearson

// Battleship Board Game
// Patrol Boat Header File

#include<iostream>
#include<string>
#include"ship.h"

#ifndef PATROL_BOAT_H
#define PATROL_BOAT_H

// Derived class for patrol boat
class patrol_boat: public ship
{
public:
    // Constructor, member functions and destructor
    patrol_boat()
    {
        name="Patrol Boat";
        ship_length=2;
        hits=0;
    }
    int length() {return ship_length;}
    std::string return_name() {return name;}
    void print_info() {std::cout<<"Patrol Boat, with length "<<length()<<std::endl;}
    ~patrol_boat() {}
};

#endif