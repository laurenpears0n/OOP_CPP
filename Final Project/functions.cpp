// PHYS 30762 Programming in C++
// Project - Board Game
// Lauren Pearson

// Battleship Board Game
// Functions cpp File

#include<iostream>
#include<string>
#include<algorithm>
#include "board.h"
#include "ship.h"

#ifndef FUNCTIONS_C
#define FUNCTIONS_C

// Function to convert the user input of position of ship to corresponding integer value for array of squares
std::pair<int,int> get_position(std::string position) 
{
    int bow_x, bow_y;
    char x_coord = position[0];
    char letters[10]{'a','b','c','d','e','f','g','h','i','j'};
    // Get x value
    for (int i{}; i<10; i++) {
        if (x_coord == letters[i]) {
            bow_x=i;
        }
    }
    // Get y value
    if (position.length()==2) {
        char y_coord = position[1];
        bow_y=y_coord-49;
    } else if (position.length() == 3) {
        bow_y=9;
    }
    return std::make_pair(bow_x, bow_y);
}

// Function for user input of position of ship, validating input for valid position of ship
std::string input_position(std::string name, int length)
{
    std::string start_position;
    std::cout<<"Enter position of "<<name<<", (length = "<<length<<"), must be letter a-j followed by number 1-10 (e.g. a1): \n";
    std::getline(std::cin, start_position);
    // Arrays of valid inputs for postion
    char letters[10]{'a','b','c','d','e','f','g','h','i','j'};
    char numbers[9]{'1','2','3','4','5','6','7','8','9'};

    bool valid_input=false;
    while (valid_input==false)
    {
        // Reject if input is too long or short
        if (start_position.length()>3||start_position.length()<2)
        {
            std::cout<<"Incorrect input, please re-enter postion of "<<name<<", must be letter (a-j) followed by number (1-10) (e.g. a1): \n";
            std::getline(std::cin, start_position);
            valid_input=false;
        // Reject if first character is not one of the letters a-j
        } else if (std::find(std::begin(letters), std::end(letters), start_position[0]) == std::end(letters)) {
            std::cout<<"Incorrect input, please re-enter postion of "<<name<<", must be letter (a-j) followed by number (1-10) (e.g. a1): \n";
            std::getline(std::cin, start_position);
            valid_input=false;
        } else if(start_position.length()==2) {
            // Reject if only one number inputted after letter if it is not a numebr 0-9
            if (std::find(std::begin(numbers), std::end(numbers), start_position[1]) == std::end(numbers)) {
            std::cout<<"Incorrect input, please re-enter postion of "<<name<<", must be letter (a-j) followed by number (1-10) (e.g. a1): \n";
           std::getline(std::cin, start_position);
            valid_input=false;
            } else {
                valid_input=true;
            }
        } else if (start_position.length()==3) {
            // Reject if 2 digit number inputted if it is not 10
            if (start_position[1] != '1' || start_position[2] != '0') {
                std::cout<<"Incorrect input, please re-enter postion of "<<name<<", must be letter (a-j) followed by number (1-10) (e.g. a1): \n";
                std::getline(std::cin, start_position);
                valid_input=false;
            } else { 
                valid_input=true;
            }
        }
    }   
    return start_position;
}

// Function to validate input of orientation
std::string input_orientation(std::string name)
{
    std::string orientation;
    std::cout<<"Enter direction of end of "<<name<<" (u/d/l/r): \n";
    std::getline(std::cin, orientation);
    char inputs[]={'u','d','l','r'};
    bool valid_input = false;
    while (valid_input==false)
    {
        // Reject if input more than one character
        if (orientation.length()>1)
        {
            std::cout<<"Incorrect input, please re-enter direction (u/d/l/r) (case sensitive): \n";
            std::getline(std::cin, orientation);
            valid_input=false;
        // Reject if not one of u,d,l,r
        } else if (std::find(std::begin(inputs), std::end(inputs), orientation[0]) == std::end(inputs)) {
            std::cout<<"Incorrect input, please re-enter direction (u/d/l/r) (case sensitive): \n";
            std::getline(std::cin, orientation);
            valid_input=false;
        } else {valid_input=true;}
    }
    return orientation;
}

#endif