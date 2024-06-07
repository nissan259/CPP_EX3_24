#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include "Tile.hpp"


namespace ariel {
class Tile; // Forward declaration of Tile class
class board {
public:
    board();
    void print_board();
    Tile& getTile(int id);

private:
    std::vector<Tile> tails;

    template <typename T>
    void shuffle_vector(std::vector<T>& vec) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rng(seed);
        std::shuffle(vec.begin(), vec.end(), rng);
    }
};

} // namespace ariel

#endif // BOARD_HPP