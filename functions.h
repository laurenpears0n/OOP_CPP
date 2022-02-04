// PHYS 30762 Programming in C++
// Project - Board Game
// Lauren Pearson

// Battleship Board Game
// Functions h File

#include<string>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Declare functions and enum for which board is to be selected
std::pair<int,int> get_position(std::string position);
std::string input_position(std::string name, int length);
std::string input_orientation(std::string name);

#endif