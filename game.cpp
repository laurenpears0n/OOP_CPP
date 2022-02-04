// PHYS 30762 Programming in C++
// Project - Board Game
// Lauren Pearson

// Battleship Board Game
// Main Game cpp

#include<iostream> 
#include<string>
#include<vector>
#include<algorithm>
#include<memory>
#include"ship.h"
#include"carrier.h"
#include"battleship.h"
#include"destroyer.h"
#include"submarine.h"
#include"patrol_boat.h"
#include"functions.h"
#include"board.h"

int main ()
{   
    bool repeat=true;
    while (repeat==true) 
    {
        // Create vector of smart pointers to board, adding one each for Player 1 and 2
        std::vector<std::unique_ptr<board>> player_boards;
        player_boards.push_back(std::make_unique<board>());
        player_boards.push_back(std::make_unique<board>());
        
        // Create vector of smart pointers to ships, adding one of each ship for each player
        std::vector<std::shared_ptr<ship>> ships_1;
        ships_1.push_back(std::make_shared<carrier>());
        ships_1.push_back(std::make_shared<battleship>());
        ships_1.push_back(std::make_shared<destroyer>());
        ships_1.push_back(std::make_shared<submarine>());
        ships_1.push_back(std::make_shared<patrol_boat>());

        std::vector<std::shared_ptr<ship>> ships_2;
        ships_2.push_back(std::make_shared<carrier>());
        ships_2.push_back(std::make_shared<battleship>());
        ships_2.push_back(std::make_shared<destroyer>());
        ships_2.push_back(std::make_shared<submarine>());
        ships_2.push_back(std::make_shared<patrol_boat>());

        // Declaring which set of ships is for each player to place on their board
        player_boards[0]->placed_ships=ships_1;
        player_boards[1]->placed_ships=ships_2;

        // Defining variables to validate user inputs
        std::string decision;
        bool valid_input;

        std::cout<<"Welcome to Battleship! \nEach player will place their ships on a board like this: \n";
        player_boards[0]->print_board(player_boards[0]->squares);
        std::cout<<"The ships to place are as follows: \n";
        std::for_each(ships_1.begin(), ships_1.end(), [&] (const auto& ship) {ship->print_info(); });
        std::cout<<"Player 1 will start, then player 2 (dont peek at the other \n players board please!). \n";
        std::cout<<"You will then choose a square on the board to fire your \n shot at and try to sink all your opponents ships. \nGood luck! \n\n\n";

        // Loop for each player to place ships on their board
        for (int i{}; i<2; i++)
        {   
            player_boards[i]->print_board(player_boards[i]->squares);
            std::cout<<"Player "<<i+1<< ", place ships \n";
            player_boards[i]->setup_board();
            // Offer player option to replace their ships on their board as many times as they would like, validating their inputs
            bool final_decision=false;
            while (final_decision==false)
            {
                std::cout<<"Would you like to replace your ships? Enter y/n: \n";
                std::getline(std::cin, decision);
                    valid_input=false;
                    while (valid_input==false)
                    {
                    if (decision == "y") {
                        player_boards[i]->clear_board(player_boards[i]->squares);
                        player_boards[i]->setup_board();
                        valid_input=true;
                        final_decision=false;
                    } else if (decision=="n") {
                        std::cout<<"Ok! \n";
                        valid_input=true;
                        final_decision=true;
                    } else {
                        std::cout<<"Invalid input, please input y/n (case sensitive): \n";
                        std::getline(std::cin, decision);
                        valid_input=false;
                        final_decision=false;
                    } 
                }
            }
        }

        // Declare enemy ships for each player's board as their oponents ships and add it to their invisible enemey squares;
        player_boards[0]->enemy_ships=ships_2;
        player_boards[1]->enemy_ships=ships_1;
        player_boards[0]->add_enemy_ships();
        player_boards[1]->add_enemy_ships();

        // Define variable for gameplay, setting the counter for sunk ships to zero to begin
        int other_player;
        std::string target;
        bool win = false;
        player_boards[0]->sunk_counter=0;
        player_boards[1]->sunk_counter=0;

        // Create vector of vectors of strings to store the target square each player picks and if it is a hit or miss.
        std::vector<std::vector<std::string>> player_moves;
        std::vector<std::string> player_1_moves;
        std::vector<std::string> player_2_moves;
        std::vector<std::string> player_1_hitsormiss;
        std::vector<std::string> player_2_hitsormiss;
        player_moves.push_back(player_1_moves);
        player_moves.push_back(player_2_moves); 
        player_moves.push_back(player_1_hitsormiss);
        player_moves.push_back(player_2_hitsormiss); 

        // Loop for actual gameplay, repeats each player picking a target square until all their opponents ships are sunk
        while (win==false) 
        {
            for (int i{}; i<2; i++) 
            {
                // Declaring the other player based on who is picking their target
                if (i==0) {   
                    other_player=1;
                } else if (i==1) {
                    other_player=0;
                }
                // User input of target square and validating the input, also adding the target square to the moves log
                std::cout<<"Player "<<i+1<< ", input target square: \n";
                std::getline(std::cin, target);
                player_boards[i]->target_square = target;
                target = player_boards[i]->validate_target();
                player_moves[i].push_back(target);
                // Check if the move was a hit or miss and adding it to the players hit board and moves log accordingly
                bool hitmiss= player_boards[i]->hit_or_miss();
                if (hitmiss == true) {
                    player_moves[i+2].push_back(": Hit");
                } else {
                    player_moves[i+2].push_back(": Miss");
                }
                player_boards[i]->add_hit_miss(hitmiss);
                player_boards[i]->print_board(player_boards[i]->shot_squares);

                // Loop to check if a ship has been sunk and if so, erases it from the ship vector of the opponents ships
                for (int j{}; j<player_boards[i]->enemy_ships.size(); j++) 
                {
                    if (player_boards[i]->enemy_ships[j]->hits== player_boards[i]->enemy_ships[j]->length()) {
                        std::cout<<"Sunk "<<player_boards[i]->enemy_ships[j]->return_name()<<"! \n";
                        player_boards[other_player]->sunk_counter++;
                        player_boards[i]->enemy_ships.erase(player_boards[i]->enemy_ships.begin()+j);
                    }
                }
                // End the game if all enemys ships are sunk
                if (player_boards[other_player]->sunk_counter==5) {
                    std::cout<<"All ships sunk! \n";
                    std::cout<<"Player "<<i+1<<" wins! \n";
                    win=true;
                    i=2;
                } else {
                    win=false;
                }
            }
        }

        // Loop to ask if each player wants to see a record of their moves, validating the input
        for (int i{}; i<2; i++)
        {
            std::cout<<"Player "<<i+1<<", would you like to see your moves? Enter y/n: \n";
            std::getline(std::cin, decision);
            valid_input=false;
            while (valid_input==false)
            {
                if (decision == "y") {
                    for (int j{}; j<player_moves[i].size(); j++) {
                        std::cout<<player_moves[i][j];
                        std::cout<<player_moves[i+2][j]<<std::endl;
                        valid_input=true;
                    }
                    std::cout<<"Thanks for playing! \n";
                } else if (decision=="n") {
                    std::cout<<"Ok, thanks for playing! \n";
                    valid_input=true;
                } else {
                    std::cout<<"Invalid input, please input y/n (case sensitive): \n";
                    std::getline(std::cin, decision);
                    valid_input=false;
                }   
            }
        }

        // Free memory of vectors used
        ships_1.clear();
        ships_2.clear();
        player_moves.clear();
        player_1_moves.clear();
        player_2_moves.clear();
        player_1_hitsormiss.clear();
        player_2_hitsormiss.clear();

        
        std::cout<<"Would you like to play again? Enter y/n: \n";
        std::getline(std::cin, decision);
        valid_input=false;
        while (valid_input==false)
        {
            if (decision == "n") {
                std::cout<<"Ok, goodbye!\n";
                valid_input=true;
                repeat=false;
            } else if (decision=="y") {
                valid_input=true;
                repeat=true;
            } else {
                std::cout<<"Invalid input, please input y/n (case sensitive): \n";
                std::getline(std::cin, decision);
                valid_input=false;
            }   
        }
    }

    return 0;
}