// PHYS 30762 Programming in C++
// Project - Board Game
// Lauren Pearson

// Battleship Board Game
// Board Header File

#include<string>
#include<vector>
#include<memory>
#include"ship.h"
#include"functions.h"

#ifndef BOARD_H
#define BOARD_H

// Class for board
class board
{
public:
    std::vector<std::shared_ptr<ship>> placed_ships;
    std::vector<std::shared_ptr<ship>> enemy_ships;
    char squares[10][10]; // Array of squares to place ships on
    char shot_squares[10][10]; // Array of squares to track hits and misses of enemy ships
    char enemy_squares[10][10]; // 'Invisible' array of squares to compare shot targets to enemy ship positions
    std::string target_square;
    int sunk_counter;

    // Declare functions
    board();
    void setup_board();
    bool allowed_placement(std::shared_ptr<ship> sh);
    void add_ship(std::shared_ptr<ship> sh, char squares_to_change[10][10]);
    void print_board(char squares_to_print[10][10]);
    void clear_board(char squares_to_clear[10][10]);
    void add_enemy_ships();
    std::string validate_target();
    bool hit_or_miss();
    void add_hit_miss(bool hitmiss);
    ~board();
};

#endif