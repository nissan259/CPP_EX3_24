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

void print_menu();
void initialize_game(Player &p1, Player &p2, Player &p3, board &b);

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

     initialize_game(p1, p2, p3, b);

    int turn = 0;
    Player *now_player = nullptr;

    while (p1.getScore() <= 10 && p2.getScore() <= 10 && p3.getScore() <= 10) {
        if (turn % 3 == 0) {
            now_player = &p1;
        } else if (turn % 3 == 1) {
            now_player = &p2;
        } else {
            now_player = &p3;
        }

        now_player->roll_number(b, p1, p2);
        now_player->display_resources();

        bool end_turn = false;
        while (!end_turn) {
            print_menu();
            int press;
            std::cin >> press;

            switch (press) {
            case 1:
                // print board
                b.print_board();
                break;
            case 2:
                // display the roads
                p1.display_roads();
                break;
            case 3:
                // display settlements
                p1.display_settlements();
                break;
            case 4:
                // display cities
                now_player->display_cities();
                break;
            case 5:
                // buy road
                {
                    int tile, edge;
                    std::cout << "Enter tile and edge for the road: ";
                    std::cin >> tile >> edge;
                    if (now_player->buy_road(tile, edge, b, turn)) {
                        std::cout << "Road built successfully." << std::endl;
                    } else {
                        std::cout << "Failed to build road." << std::endl;
                    }
                }
                break;
            case 6:
                // buy settlement
                {
                    int tile, vertex;
                    std::cout << "Enter tile and vertex for the settlement: ";
                    std::cin >> tile >> vertex;
                    if (now_player->buy_stelment(tile, vertex, b, turn)) {
                        std::cout << "Settlement built successfully." << std::endl;
                    } else {
                        std::cout << "Failed to build settlement." << std::endl;
                    }
                }
                break;
            case 7:
                // buy city
                {
                    int tile, vertex;
                    std::cout << "Enter tile and vertex for the city: ";
                    std::cin >> tile >> vertex;
                    if (now_player->buy_city(tile, vertex, b, turn)) {
                        std::cout << "City built successfully." << std::endl;
                    } else {
                        std::cout << "Failed to build city." << std::endl;
                    }
                }
                break;
            case 8:
                // buy card
                now_player->buy_card();
                break;
            case 9:
                // use card
                {
                    std::string card_type;
                    std::cout << "Enter card type to use: ";
                    std::cin >> card_type;
                    development_card *card = now_player->createDevelopmentCard(card_type);
                    if (card) {
                        now_player->use(card, p1, p2, b);
                        delete card;
                    } else {
                        std::cout << "Invalid card type." << std::endl;
                    }
                }
                break;
            case 10:
                // trade
                {
                    int player_id;
                    std::cout << "Enter player ID to trade with (1: Orel, 2: Nir, 3: Amit): ";
                    std::cin >> player_id;
                    Player *other_player = nullptr;
                    if (player_id == 1) other_player = &p1;
                    else if (player_id == 2) other_player = &p2;
                    else if (player_id == 3) other_player = &p3;

                    if (other_player && other_player != now_player) {
                        now_player->trade(*other_player);
                    } else {
                        std::cout << "Invalid player selected." << std::endl;
                    }
                }
                break;
            case 11:
                // show resources
                now_player->display_resources();
                break;
            case 12:
            // show development cards
               now_player->display_development_cards();
                break;
            case 13:
                // end turn
               now_player->end_turn();
                 end_turn = true;
                turn++;
                break;
            default:
                std::cout << "Invalid option" << std::endl;
                break;
            }
        }
        turn++;
    }

    return 0;
}

void print_menu() {
    std::cout << "1. Show Board" << std::endl;
    std::cout << "2. Show Roads" << std::endl;
    std::cout << "3. Show Settlements" << std::endl;
    std::cout << "4. Show Cities" << std::endl;
    std::cout << "5. Build Road" << std::endl;
    std::cout << "6. Build Settlement" << std::endl;
    std::cout << "7. Build City" << std::endl;
    std::cout << "8. Buy Development Card" << std::endl;
    std::cout << "9. Use Development Card" << std::endl;
    std::cout << "10. Trade" << std::endl;
    std::cout << "11. Show Resources" << std::endl;
    std::cout << "12. Show Development Cards" << std::endl;
    std::cout << "13. End Turn" << std::endl;
}

void initialize_game(Player &p1, Player &p2, Player &p3, board &b) {
    int tile, edge, vertex;
    int counter_roads = 0;
    int counter_settlement = 0;

    // Initialize for Player 1
    while (counter_roads < 2 || counter_settlement < 2) {
        if (counter_roads < 2) {
            std::cout << "Player 1: Enter the tile and edge you want to set your road:" << std::endl;
            std::cin >> tile >> edge;
            try {
                if (b.getTile(tile).set_first_round_edge(p1, edge)) {
                    counter_roads++;
                }
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range exception while Player 1 buys road: " << e.what() << std::endl;
            }
        }
        if (counter_settlement < 2) {
            std::cout << "Player 1: Enter the tile and vertex you want to set your settlement:" << std::endl;
            std::cin >> tile >> vertex;
            try {
                int pp= p1.getid();
                if (b.getTile(tile).set_first_round_vertex(p1, vertex)){
                    counter_settlement++;
                }
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range exception while Player 1 buys city: " << e.what() << std::endl;
            }
        }
    }

    // Reset counters for Player 2
    counter_roads = 0;
    counter_settlement = 0;

    // Initialize for Player 2
    while (counter_roads < 2 || counter_settlement < 2) {
        if (counter_roads < 2) {
            std::cout << "Player 2: Enter the tile and edge you want to set your road:" << std::endl;
            std::cin >> tile >> edge;
            try {
                if (b.getTile(tile).set_first_round_edge(p2, edge)){
                    counter_roads++;
                }
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range exception while Player 2 buys road: " << e.what() << std::endl;
            }
        }
        if (counter_settlement < 2) {
            std::cout << "Player 2: Enter the tile and vertex you want to set your settlement:" << std::endl;
            std::cin >> tile >> vertex;
            try {
                int pp= p2.getid();
                 if (b.getTile(tile).set_first_round_vertex(p2, vertex)) {
                    counter_settlement++;
                }
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range exception while Player 2 buys city: " << e.what() << std::endl;
            }
        }
    }

    // Reset counters for Player 3
    counter_roads = 0;
    counter_settlement = 0;

    // Initialize for Player 3
    while (counter_roads < 2 || counter_settlement < 2) {
        if (counter_roads < 2) {
            std::cout << "Player 3: Enter the tile and edge you want to set your road:" << std::endl;
            std::cin >> tile >> edge;
            try {
                if (b.getTile(tile).set_first_round_edge(p3, edge)){
                    counter_roads++;
                }
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range exception while Player 3 buys road: " << e.what() << std::endl;
            }
        }
        if (counter_settlement < 2) {
            std::cout << "Player 3: Enter the tile and vertex you want to set your settlement:" << std::endl;
            std::cin >> tile >> vertex;
            try {
                int pp= p3.getid();
                if (b.getTile(tile).set_first_round_vertex(p3,vertex)){
                    counter_settlement++;
                }
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range exception while Player 3 buys city: " << e.what() << std::endl;
            }
        }
    }
}
