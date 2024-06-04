#include <iostream>
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"

using namespace std;
using namespace ariel;

int main() {
    Player p1("Amit");
    std::cout << p1.getName() << std::endl; // should print Amit
    Player p2("Yossi");
    std::cout << p2.getName() << std::endl; // should print Yossi
    Player p3("Dana");
    std::cout << p3.getName() << std::endl; // should print Dana

    Catan catan(p1, p2, p3);
    std::cout << "orel" << std::endl; // should print orel

    // Starting of the game. Every player places two settlements and two roads.
    catan.ChooseStartingPlayer();

    board b;  // Correct initialization of the board object
    // should print the name of the starting player, assume it is Amit.
    b.print_board(); // Call the print_board method on the board object
    return 0;
}
