#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
namespace ariel
{

class Player {
private:
    std::string name;
    int score;

public:
    // Constructor
    Player(const std::string& playerName) : name(playerName), score(0) {}

    // Getters
    std::string getName() const {
        return name;
    }

    int getScore() const {
        return score;
    }
};
}
#endif // PLAYER_HPP
