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
    Player p1("Orel");
    std::cout << p1.getName() << std::endl; // should print Orel
    Player p2("Nir");
    std::cout << p2.getName() << std::endl; // should print Nir
    Player p3("Amit");
    std::cout << p3.getName() << std::endl; // should print Amit
    board b;
    b.print_board();
    resources_card r1("Wood");
    resources_card r2("Brick");
    resources_card r3("Sheep");
    resources_card r4("Wheat");
    resources_card r5("Clay");
    resources_card r6("Wood");
    resources_card r7("Brick");
    resources_card r8("Sheep");
    resources_card r9("Wheat");
    resources_card r10("Clay");
    resources_card r11("Wood");
    resources_card r12("Brick");
    resources_card r13("Sheep");
    resources_card r14("Wheat");
    resources_card r15("Clay");
    
    // Adding resources to players
    p1.add_resources_card(r1);
    p1.add_resources_card(r2);
    p1.add_resources_card(r3);
    p1.add_resources_card(r4);
    p1.add_resources_card(r5);
    
    p2.add_resources_card(r6);
    p2.add_resources_card(r7);
    p2.add_resources_card(r8);
    p2.add_resources_card(r9);
    p2.add_resources_card(r10);
    
    p3.add_resources_card(r11);
    p3.add_resources_card(r12);
    p3.add_resources_card(r13);
    p3.add_resources_card(r14);
    p3.add_resources_card(r15);
    
    p1.display_resources();
    p2.display_resources();
    p3.display_resources();
    
    std::cout << "Enter the tile and edge you want to set your first road:" << std::endl;
    int tile, edge;
    cin >> tile >> edge;
    std::cout<<p1.getid()<<"id"<<std::endl;
    p1.buy_road(tile, edge, b, 0);
    b.getTile(tile).display();
    p1.display_roads();
    
    p1.end_turn();
    
    return 0;
}
