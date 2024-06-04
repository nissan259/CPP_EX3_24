

#include "player.hpp"
#include <vector>
#include <iostream>
#include "board.hpp"
#include "Tile.hpp"

namespace ariel {
    class Catan {
    private:
        std::vector<Player> Player_arr; // Ensure Player_arr is std::vector
        board game_board;
        int turn;

    public:
        // Constructor that initializes the players
        Catan(const Player& player1, const Player& player2, const Player& player3);
        
        // Method to display player information
        void displayPlayers() const;
        void ChooseStartingPlayer();
    };
}

