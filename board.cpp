// PHYS 30762 Programming in C++
// Project - Board Game
// Lauren Pearson

// Battleship Board Game
// Board cpp File

#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<algorithm>
#include<memory>
#include"board.h"
#include"ship.h"
#include"functions.h"

// Board constructor, making a 'blank' board with a '.' placeholder
board::board()
{
    for (int y{};y<10;y++){ 
        for (int x{};x<10;x++){
            squares[y][x]='.';
            shot_squares[y][x]='.';
            enemy_squares[y][x]='.';
        }
    }
}

// Function to do the initial board set up for the player to place their ships, using other member functions
void board::setup_board()
{
    std::for_each(placed_ships.begin (), placed_ships.end(), [&] (const auto& ship)
    {
        ship->start_position = input_position(ship->return_name(), ship->length());
        ship->orientation=input_orientation(ship->return_name());
        ship->bow_position_x = get_position(ship->start_position).first;
        ship->bow_position_y = get_position(ship->start_position).second;
        allowed_placement(ship);
        add_ship(ship, squares);
        print_board(squares);
    } );
}

// Function to check if the user-inputted postion is valid, returns true when valid
bool board::allowed_placement(std::shared_ptr<ship> sh)
{   
    // Array of characters used to show ship placement
    char ship_index[]{'C','B','D','S','P'};
    // Variables for validiating input
    bool valid = false;
    bool occupied = false;
    while (valid == false) 
    {
        // Variables to define the location of the ship based on the input orientation
        int placement_variable_1; //Defines the maximum position of the end of the ship
        int placement_variable_2; // Defines the limit of the board size to the 10x10 array
        // Define above variables based on location
        if (sh->orientation=="u") {
            placement_variable_1 = sh->bow_position_y-sh->ship_length+1;
            placement_variable_2 = 0;
        } else if (sh->orientation=="d") { 
            placement_variable_1 = -(sh->bow_position_y+sh->ship_length-1);
            placement_variable_2 = -9;
        } else if (sh->orientation=="l") { 
            placement_variable_1 = sh->bow_position_x-sh->ship_length+1;
            placement_variable_2 = 0;
        } else if (sh->orientation=="r") { 
            placement_variable_1 = -(sh->bow_position_x+sh->ship_length-1);
            placement_variable_2 = -9;
        }

        // Reject input if the ship placement will go 'beyond' the board array
        if (placement_variable_1<placement_variable_2) {
            std::cout<<"Placement beyond board limits, please try again \n";
            sh->start_position = input_position(sh->return_name(), sh->ship_length);
            sh->orientation = input_orientation(sh->return_name());
            sh->bow_position_x = get_position(sh->start_position).first;
            sh->bow_position_y = get_position(sh->start_position).second;
            valid = false;
        } else {
            // Loop to check if any of the squares the ship will be placed on are occupied by checking if square contains the first char of the ship name
            for (int counter{};counter<sh->ship_length;counter++) {
                if (sh->orientation=="u") {
                    if (std::find(std::begin(ship_index), std::end(ship_index), squares[sh->bow_position_y-counter][sh->bow_position_x]) != std::end(ship_index)) {
                    occupied = true;
                    }
                } else if (sh->orientation=="d") { 
                    if (std::find(std::begin(ship_index), std::end(ship_index), squares[sh->bow_position_y+counter][sh->bow_position_x]) != std::end(ship_index)) {
                    occupied = true;
                    }
                } else if (sh->orientation=="l") { 
                    if (std::find(std::begin(ship_index), std::end(ship_index), squares[sh->bow_position_y][sh->bow_position_x-counter]) != std::end(ship_index)) {
                    occupied = true;
                    }
                } else if (sh->orientation=="r") { 
                    if (std::find(std::begin(ship_index), std::end(ship_index), squares[sh->bow_position_y][sh->bow_position_x+counter]) != std::end(ship_index)) {
                    occupied = true;
                    }
                }
            }
            // Reject input if squares are already occupied
            if (occupied == true) {
                std::cout<<"Space already occupied, please place elsewhere \n";
                sh->start_position = input_position(sh->return_name(), sh->ship_length);
                sh->orientation = input_orientation(sh->return_name());
                sh->bow_position_x = get_position(sh->start_position).first;
                sh->bow_position_y = get_position(sh->start_position).second;
                occupied = false;
                valid = false; 
            } else {
                // If all criteria met placement is valid
                valid = true;
            }
        }
    }   
    return true;
}

// Function to add ship to board
void board::add_ship(std::shared_ptr<ship> sh, char squares_to_change[10][10])
{
    // Replaces '.' of blank board to first character of ship name to differentiate between ships for each orientation option
    for (int i{}; i<sh->ship_length;i++) {
        if (sh->orientation=="u"){
            squares_to_change[sh->bow_position_y-i][sh->bow_position_x]=sh->return_name().at(0);
        } else if (sh->orientation=="d") { 
            squares_to_change[sh->bow_position_y+i][sh->bow_position_x]=sh->return_name().at(0);
        } else if (sh->orientation=="l") { 
            squares_to_change[sh->bow_position_y][sh->bow_position_x-i]=sh->return_name().at(0);
        } else if (sh->orientation=="r") { 
            squares_to_change[sh->bow_position_y][sh->bow_position_x+i]=sh->return_name().at(0);
        }
    }
}

// Function to print desired board in useful output 
void board::print_board(char squares_to_print[10][10])
{
    std::cout<<"     a b c d e f g h i j \n";
    std::cout<<"    --------------------- \n";
    for (int y{};y<10;y++){ 
        std::cout<<std::setw(2)<<y+1<<" | ";
        for (int x{};x<10;x++) {
            std::cout<<squares_to_print[y][x]<<" ";
            }
        std::cout<<"| \n";
    }
    std::cout<<"    --------------------- \n";
}

// Function to remove all ships from board to make it blank
void board::clear_board(char squares_to_clear[10][10])
{
    for (int y{};y<10;y++){ 
        for (int x{};x<10;x++){
            squares_to_clear[y][x]='.';
        }
    }
}

// Function ot add enemy ships to invisible enemy board
void board::add_enemy_ships()
{
    std::for_each(enemy_ships.begin (), enemy_ships.end(), [&] (const auto& sh) 
    {
        add_ship(sh, enemy_squares);
    } );
}

// Function to validate user input of target square on enemy ships, returns valid target square
std::string board::validate_target()
{
    // Variables for validating inputs
    char letters[]{'a','b','c','d','e','f','g','h','i','j'};
    char numbers[]{'1','2','3','4','5','6','7','8','9'};
    bool valid=false;
    int target_x, target_y;
    target_x = get_position(target_square).first;
    target_y = get_position(target_square).second;
    while (valid==false)
    {
        // Reject input if input is too long or short
        if (target_square.length()>3||target_square.length()<2) {
            std::cout<<"Incorrect input, please re-enter target square, must be letter (a-j) followed by number (1-10) (e.g. a1): \n";
            std::getline(std::cin, target_square);
            target_x = get_position(target_square).first;
            target_y = get_position(target_square).second;
            valid=false;
        // Reject input if first character of input is not one of the letters from a-j
        } else if (std::find(std::begin(letters), std::end(letters), target_square[0]) == std::end(letters)) {
            std::cout<<"Incorrect input, please re-enter target square, must be letter (a-j) followed by number (1-10) (e.g. a1): \n";
            std::getline(std::cin, target_square);
            target_x = get_position(target_square).first;
            target_y = get_position(target_square).second;
            valid=false;
        // Reject input if target square has already been selected based on the character of the array element
        } else if (shot_squares[target_y][target_x]=='X' || shot_squares[target_y][target_x]=='o') {
            std::cout<<"Target square previously selected, please re-enter target: .\n";
            std::getline(std::cin, target_square);
            target_x = get_position(target_square).first;
            target_y = get_position(target_square).second;
            valid = false;
        // Validate numerical part of input based on if below 10 or not
        } else if(target_square.length()==2) {
            // Reject input if the second character of input is not one of the numbers 1-9
            if (std::find(std::begin(numbers), std::end(numbers), target_square[1]) == std::end(numbers)) {
            std::cout<<"Incorrect input, please re-enter target square, must be letter (a-j) followed by number (1-10) (e.g. a1): \n";
            std::getline(std::cin, target_square);
            target_x = get_position(target_square).first;
            target_y = get_position(target_square).second;
            valid=false;
            } else {valid=true;}
        } else if (target_square.length()==3) {
            // Reject input if the second and third characters don't equate to 10
            if (target_square[1] != '1' || target_square[2] != '0') {
                std::cout<<"Incorrect input, please re-enter target square, must be letter (a-j) followed by number (1-10) (e.g. a1): \n";
                std::getline(std::cin, target_square);
                target_x = get_position(target_square).first;
                target_y = get_position(target_square).second;
                valid=false;
            } else{valid=true;}
        }
    }
    return target_square;
}

// Function to check if the target square is a hit or miss, returns true for hit or false for miss
bool board::hit_or_miss()
{
    int target_x, target_y;
    target_x = get_position(target_square).first;
    target_y = get_position(target_square).second;
    char ship_index[]{'C','B','D','S','P'};
    if (std::find(std::begin(ship_index), std::end(ship_index), enemy_squares[target_y][target_x]) != std::end(ship_index)) {
        std::cout<<"Successful hit! \n";   
        return true;
    } else {
        std::cout<<"Miss! \n";
        return false;
    }
}

// Function to add hit or miss to the hit board
void board::add_hit_miss(bool hitmiss)
{
    int target_x, target_y;
    target_x = get_position(target_square).first;
    target_y = get_position(target_square).second;
    char symbol;
    if (hitmiss==true) {
        symbol = 'X';
        bool hit_ship = false;
        int number_ship;
        while (hit_ship==false) 
        {
            for (int i{}; i<enemy_ships.size(); i++) {
                if (enemy_squares[target_y][target_x]==enemy_ships[i]->return_name().at(0)) {
                    hit_ship = true;
                // Show which ship has been hit in vector of ships
                    if (hit_ship == true) {
                        number_ship=i;
                    }
                }
            }
        }
        // Add hit to correct ship
        enemy_ships[number_ship]->hits += 1;
        shot_squares[target_y][target_x]=symbol;
    } else if (hitmiss == false) {
        symbol = 'o';
        shot_squares[target_y][target_x]=symbol;
    }
}

// Board destructor
board::~board() {}