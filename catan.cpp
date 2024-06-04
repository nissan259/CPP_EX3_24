#include "catan.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <vector> // Include vector header
#include <array>  // Include array header

namespace ariel {
// Constructor implementation
Catan::Catan(const Player& player1, const Player& player2, const Player& player3)
    : Player_arr{player1, player2, player3}, turn(0) 
       {}

// Method to display player information
void Catan::displayPlayers() const {
    std::cout << "Player 1: " << Player_arr[0].getName() << ", Score: " << Player_arr[0].getScore() << std::endl;
    std::cout << "Player 2: " << Player_arr[1].getName() << ", Score: " << Player_arr[1].getScore() << std::endl;
    std::cout << "Player 3: " << Player_arr[2].getName() << ", Score: " << Player_arr[2].getScore() << std::endl;
}

// Method to choose the starting player
void Catan::ChooseStartingPlayer() {
    if (turn == 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 6);
        std::vector<std::pair<int, int>> throws;

        for (size_t i = 0; i < Player_arr.size(); ++i) {
            int throw1 = dist(gen);
            int throw2 = dist(gen);
            int totalThrow = throw1 + throw2;
            throws.emplace_back(totalThrow, i);
        }

        // Custom comparator function
        auto compareThrows = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.first > b.first;
        };

        std::sort(throws.begin(), throws.end(), compareThrows);

        std::vector<Player> sortedPlayers;
        for (const auto& t : throws) {
            sortedPlayers.push_back(Player_arr[t.second]);
        }

        Player_arr = sortedPlayers; // Assign sorted players back to Player_arr
        std::cout << "Players sorted by their throws:\n";
        displayPlayers();
    } else {
        std::cout << "The starting player has already been chosen.\n";
    }
}
}
