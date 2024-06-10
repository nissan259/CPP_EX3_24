#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include "Develompent_card.hpp"
#include "resources_card.hpp"
#include "board.hpp" // Include board header for proper declaration

namespace ariel {
    class victory;
    class year_of_happy;
    class road_build;
    class monopoly;
    class knights;
    class board;

    class Player {
        std::string name;
        int score;
        std::vector<development_card*> development_cards;
        std::vector<resources_card> resources;
        std::vector<std::string> roads;
        std::vector<std::string> settlements;
        std::vector<std::string> cities;
        static int id;
    public:
        Player(std::string playerName);
        ~Player(); // Destructor to free allocated memory
        std::string getName() const;
        int getScore() const;
        std::vector<development_card*>& getDevelopment_cards();
        std::vector<resources_card>& getResources();
        void add_development_cards(development_card* card);
        void add_resources_card(const resources_card& card); // Ensure this declaration matches the definition
        void add_const_score(int score);
        void buy_card();
        std::string getrandomcard();
        int use(development_card* card, Player& take1, Player& take2, board& board1);
        int getid() ;
       int buy_road(int id,int edge,board& b,int turn);
        void display_resources(); // Declaration of display_resources;
        void display_development_cards(); // Declaration of display_development_cards;
        void trade(Player& ask1); // Declaration of trade;
        int buy_stelment(int id,int vertex,board& b,int turn);
        int buy_city(int id,int vertex,board& b,int turn);
        int roll_number(board& b, Player &p1, Player& p2);
        void display_roads();
        void display_settlements();
        void display_cities();
        void add_road(std::string road);
        void add_settlement(std::string settlement);
        void add_city(std::string city);
         development_card* createDevelopmentCard(const std::string& card_type);

        void end_turn();
    private:
        bool hasResources(const std::vector<std::string>& required_resources) const;
        void removeResources(const std::vector<std::string>& resources_to_remove);
        void processVictoryCard();
        void processKnightCard();
        void processMonopolyCard(Player& take1, Player& take2);
        void processYearOfHappyCard();
        void processRoadBuildingCard(board& board1);
        bool removeCardOfType(const std::string& card_type);
        void takeResourceFromPlayer(Player& player, const std::string& resource);
        void to_lowercase(std::string& str);
    };
}

#endif // PLAYER_HPP
