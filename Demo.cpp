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

    // Adding resources to players for testing
    p1.add_resources_card(resources_card("Sheep"));
    p1.add_resources_card(resources_card("Clay"));
    p1.add_resources_card(resources_card("Wheat"));

    p2.add_resources_card(resources_card("Wood"));
    p2.add_resources_card(resources_card("Brick"));
    p2.add_resources_card(resources_card("Ore"));

    // Performing a trade between p1 and p2
    p1.trade(p2);

    return 0;
}

