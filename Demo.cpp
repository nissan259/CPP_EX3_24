#include <iostream>
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"
#include "resources_card.hpp"
#include "year_of_happy.hpp"
#include "road_build.hpp"
#include "monopoly.hpp"
#include "knights.hpp"
#include "victory.hpp"

using namespace std;
using namespace ariel;

int main() {
    Player p1("Amit");
    std::cout << p1.getName() << std::endl; // should print Amit
    Player p2("Yossi");
    std::cout << p2.getName() << std::endl; // should print Yossi
    Player p3("Dana");
    std::cout << p3.getName() << std::endl; // should print Dana

    // Correct initialization of the board object
    board b;
    b.print_board(); // Call the print_board method on the board object

    // Adding resources to players for testing
    p1.add_resources_card(resources_card("Sheep"));
    p1.add_resources_card(resources_card("Clay"));
    p1.add_resources_card(resources_card("Wheat"));

    // Testing buy function
    p1.buy();

    // Displaying the cards in player's hand
    for (auto card : p1.getDevelopment_cards()) {
        card->display();
    p1.use(card, p2, p3, b);
std::cout << "Player 1 score: " << p1.getScore() << std::endl;
    }
    return 0;
}
