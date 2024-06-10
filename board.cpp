#include "board.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "Tile.hpp"

namespace ariel {

// Correct data for 19 tiles including proper initialization
std::vector<int> number_roll = {5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 11, 3, 4, 5, 6, 0}; // Adjusted order with Desert (0) in the center
std::vector<std::string> type = {"Wheat", "Wood", "Brick", "Sheep", "Wood", "Brick", "Wheat", "Clay", "Sheep", "Clay", "Wood", "Wheat", "Wood", "Wheat", "Sheep", "Wood", "Clay", "Sheep", "Desert"}; // Adjusted order with Desert at the center
std::vector<int> id = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}; // Adjusted order

board::board() {
    // Ensure the desert tile is at the correct position
    for (int i = 0; i < 19; i++) {
        if(i==9)
        {
                    tails.emplace_back(9, 7,"Desert");

        }
        tails.emplace_back(id[i], number_roll[i], type[i]);
    }

    tails[0].setneighborhood(tails[3],3);
         tails[0].setneighborhood(tails[4],4);
        tails[0].setneighborhood(tails[1], 5);
        tails[1].setneighborhood(tails[0], 2);
        tails[1].setneighborhood(tails[4], 3);
        tails[1].setneighborhood(tails[5], 4);
        tails[1].setneighborhood(tails[2], 5);
        tails[2].setneighborhood(tails[1], 2);
        tails[2].setneighborhood(tails[5], 3);
        tails[2].setneighborhood(tails[6], 4);
        tails[3].setneighborhood(tails[7], 3);
        tails[3].setneighborhood(tails[8], 4);
        tails[3].setneighborhood(tails[4], 5);
        tails[4].setneighborhood(tails[1], 0);
        tails[4].setneighborhood(tails[0], 1);
        tails[4].setneighborhood(tails[3], 2);
        tails[4].setneighborhood(tails[8], 3);
        tails[4].setneighborhood(tails[9], 4);
        tails[4].setneighborhood(tails[5], 5);
        tails[5].setneighborhood(tails[2], 0);
        tails[5].setneighborhood(tails[1], 1);
        tails[5].setneighborhood(tails[4], 2);
        tails[5].setneighborhood(tails[9], 3);
        tails[5].setneighborhood(tails[10], 4);
        tails[5].setneighborhood(tails[6], 5);
        tails[6].setneighborhood(tails[2], 1);
        tails[6].setneighborhood(tails[5], 2);
        tails[6].setneighborhood(tails[10], 3);
        tails[6].setneighborhood(tails[11], 4);
        tails[7].setneighborhood(tails[3], 0);
        tails[7].setneighborhood(tails[12], 4);
        tails[7].setneighborhood(tails[8], 5);
        tails[8].setneighborhood(tails[4], 0);
        tails[8].setneighborhood(tails[3], 1);
        tails[8].setneighborhood(tails[7], 2);
        tails[8].setneighborhood(tails[12], 3);
        tails[8].setneighborhood(tails[13], 4);
        tails[8].setneighborhood(tails[9], 5);
        //desetrt 9
        tails[9].setneighborhood(tails[5],0);
        tails[9].setneighborhood(tails[4],1);
        tails[9].setneighborhood(tails[8],2);
        tails[9].setneighborhood(tails[13],3);
        tails[9].setneighborhood(tails[14],4);
        tails[9].setneighborhood(tails[10],5);
        tails[10].setneighborhood(tails[6],0);
        tails[10].setneighborhood(tails[5],1);
        tails[10].setneighborhood(tails[9],2);
        tails[10].setneighborhood(tails[14],3);
        tails[10].setneighborhood(tails[15],4);
        tails[10].setneighborhood(tails[11],5);
        tails[11].setneighborhood(tails[6],1);
        tails[11].setneighborhood(tails[10],2);
        tails[11].setneighborhood(tails[15],3);
        tails[12].setneighborhood(tails[8],0);
        tails[12].setneighborhood(tails[7],1);
        tails[12].setneighborhood(tails[16],4);
        tails[12].setneighborhood(tails[13],5);
        tails[13].setneighborhood(tails[9],0);
        tails[13].setneighborhood(tails[8],1);
        tails[13].setneighborhood(tails[12],2);
        tails[13].setneighborhood(tails[16],3);
        tails[13].setneighborhood(tails[17],4);
        tails[13].setneighborhood(tails[14],5);
        tails[14].setneighborhood(tails[10],0);
        tails[14].setneighborhood(tails[9],1);
        tails[14].setneighborhood(tails[13],2);
        tails[14].setneighborhood(tails[17],3);
        tails[14].setneighborhood(tails[18],4);
        tails[14].setneighborhood(tails[15],5);
        tails[15].setneighborhood(tails[11],0);
        tails[15].setneighborhood(tails[10],1);
        tails[15].setneighborhood(tails[14],2);
        tails[15].setneighborhood(tails[18],3);
        tails[16].setneighborhood(tails[13],0);
        tails[16].setneighborhood(tails[12],1);
        tails[16].setneighborhood(tails[17],5);
        tails[17].setneighborhood(tails[14],0);
        tails[17].setneighborhood(tails[13],1);
        tails[17].setneighborhood(tails[16],2);
        tails[17].setneighborhood(tails[18],5);
        tails[18].setneighborhood(tails[15],0);
        tails[18].setneighborhood(tails[14],1);
        tails[18].setneighborhood(tails[17],2);
}

Tile& board::getTile(int id) {
    std::cout << "Accessing tile with id: " << id << std::endl;
    int num =tails.size();
    if (id < 0 || id >= num) {
        throw std::out_of_range("Tile id is out of range: " + std::to_string(id));
    }
    return tails[id];
}


void board::print_board() {
    std::vector<std::string> board_representation(7, std::string(35, ' '));

    auto format_tile = [](const std::string& type, int roll) {
        return type + " " + (roll == 0 ? "  " : (roll < 10 ? " " + std::to_string(roll) : std::to_string(roll)));
    };

    board_representation[0] = "       sea   sea   sea   sea   sea       ";
    board_representation[1] = "    sea " + format_tile(tails[0].gettype(), tails[0].getvalue_roll()) + " " + format_tile(tails[1].gettype(), tails[1].getvalue_roll()) + " " + format_tile(tails[2].gettype(), tails[2].getvalue_roll()) + " sea ";
    board_representation[2] = "  sea " + format_tile(tails[3].gettype(), tails[3].getvalue_roll()) + " " + format_tile(tails[4].gettype(), tails[4].getvalue_roll()) + " " + format_tile(tails[5].gettype(), tails[5].getvalue_roll()) + " " + format_tile(tails[6].gettype(), tails[6].getvalue_roll()) + " sea";
    board_representation[3] = "sea " + format_tile(tails[7].gettype(), tails[7].getvalue_roll()) + " " + format_tile(tails[8].gettype(), tails[8].getvalue_roll()) + " " + format_tile(tails[9].gettype(), tails[9].getvalue_roll()) + " " + format_tile(tails[18].gettype(), tails[18].getvalue_roll()) + " " + format_tile(tails[10].gettype(), tails[10].getvalue_roll()) + " sea";
    board_representation[4] = "  sea " + format_tile(tails[11].gettype(), tails[11].getvalue_roll()) + " " + format_tile(tails[12].gettype(), tails[12].getvalue_roll()) + " " + format_tile(tails[13].gettype(), tails[13].getvalue_roll()) + " " + format_tile(tails[14].gettype(), tails[14].getvalue_roll()) + " sea";
    board_representation[5] = "    sea " + format_tile(tails[15].gettype(), tails[15].getvalue_roll()) + " " + format_tile(tails[16].gettype(), tails[16].getvalue_roll()) + " " + format_tile(tails[17].gettype(), tails[17].getvalue_roll()) + " sea ";
    board_representation[6] = "       sea   sea   sea   sea   sea       ";

    std::cout << "************ CATAN BOARD ************\n";
    for (const auto& line : board_representation) {
        std::cout << line << std::endl;
    }
    std::cout << "*************************************\n";
}

} // namespace ariel
