// PHYS 30762 Programming in C++
// Project - Board Game
// Lauren Pearson

// Battleship Board Game
// Ship Header File

#include<string>

#ifndef SHIP_H
#define SHIP_H

// Abstract base class for ships
class ship
{
public: 
    std::string name;
    int ship_length;
    int bow_position_x, bow_position_y;
    std::string start_position;
    std::string orientation;
    int hits;

    virtual int length()=0;
    virtual std::string return_name()=0;
    virtual void print_info()=0;
    ~ship() {}
};

#endif