#ifndef CATAN_HPP
#define CATAN_HPP

#include "player.hpp"
#include <vector>
#include <iostream>

namespace ariel {
    class Catan {
    private:
        std::vector<Player> Player_arr;
        int turn ;

    public:
        // Constructor that initializes the players
        Catan(const Player& player1, const Player& player2, const Player& player3);
        
        // Method to display player information
        void displayPlayers() const ;
        void ChooseStartingPlayer();
    };
}

#endif // CATAN_HPP
