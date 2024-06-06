#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "player.hpp"
#include "victory.hpp"
#include "year_of_happy.hpp"
#include "road_build.hpp"
#include "monopoly.hpp"
#include "knights.hpp"


using namespace std;

namespace ariel {
    int Player::id = 0;

    Player::Player(std::string playerName) : name(playerName), score(0) {
        id++;
    }

    Player::~Player() {
        for (auto card : development_cards) {
            delete card;
        }
    }

    std::string Player::getName() const {
        return name;
    }

    int Player::getScore() const {
        return score;
    }

    std::vector<development_card*>& Player::getDevelopment_cards() {
        return development_cards;
    }

    std::vector<resources_card>& Player::getResources() {
        return resources;
    }

    void Player::add_development_cards(development_card* card) {
        development_cards.push_back(card);
    }

    void Player::add_resources_card(const resources_card& card) { // Ensure this matches the declaration
        resources.push_back(card);
    }

    void Player::add_const_score(int score) {
        this->score += score;
    }

    void Player::buy() {
        cout << "Buying a card" << endl;
        if (hasResources({"Sheep", "Clay", "Wheat"})) {
            removeResources({"Sheep", "Clay", "Wheat"});
            add_development_cards(createDevelopmentCard(getrandomcard()));
        } else {
            cout << "You do not have the required resources" << endl;
        }
    }

    std::string Player::getrandomcard() {
        srand((time(NULL)));
        if(victory::get_counter_victory()>5&&knights::get_number_of_knights()>4) {
            switch (rand() % 3) {
            case 1: return "Year of Happy";
            case 2: return "Monopoly";
            default: return "Road Building";
        }
        }
        if(victory::get_counter_victory()>5) {
            switch (rand() % 4) {
            case 1: return "Year of Happy";
            case 2: return "Monopoly";
            case 3: return "Road Building";
            default: return "Knight";
        }
        }
        if(knights::get_number_of_knights()>4) {
            switch (rand() % 4) {
            case 1: return "Victory";
            case 2: return "Year of Happy";
            case 3: return "Monopoly";
            default: return "Road Building";
        }
        }
        switch (rand() % 5) {
            case 0: return "Victory";
            case 1: return "Year of Happy";
            case 2: return "Monopoly";
            case 3: return "Road Building";
            default: return "Knight";
        }
    }

    int Player::use(development_card* card, Player& take1, Player& take2, board& board1) {
        string card_type = card->get_type();
        if (card_type == "Victory") {
            processVictoryCard();
        } else if (card_type == "Knight") {
            processKnightCard();
        } else if (card_type == "Monopoly") {
            processMonopolyCard(take1, take2);
        } else if (card_type == "Year of Happy") {
            processYearOfHappyCard();
        } else if (card_type == "Road Building") {
            processRoadBuildingCard(board1);
        }
        return 0;
    }

    bool Player::hasResources(const std::vector<std::string>& required_resources) const {
        for (const auto& res : required_resources) {
            if (std::none_of(resources.begin(), resources.end(), [&](const resources_card& rc) { return rc.get_type() == res; })) {
                return false;
            }
        }
        return true;
    }

    void Player::removeResources(const std::vector<std::string>& resources_to_remove) {
        for (const auto& res : resources_to_remove) {
            resources.erase(std::remove_if(resources.begin(), resources.end(), [&](resources_card& rc) { return rc.get_type() == res; }), resources.end());
        }
    }

    development_card* Player::createDevelopmentCard(const std::string& card_type) {
        std::vector<resources_card> price = { resources_card("Sheep"), resources_card("Clay"), resources_card("Wheat") };
        if (card_type == "Victory") return new victory(card_type, price);
        if (card_type == "Year of Happy") return new year_of_happy(card_type, price);
        if (card_type == "Monopoly") return new monopoly(card_type, price);
        if (card_type == "Road Building") return new road_build(card_type, price);
        return new knights(card_type, price);
    }

    void Player::processVictoryCard() {
        if (removeCardOfType("Victory")) {
            add_const_score(1);
        }
    }

    void Player::processKnightCard() {
        if (std::count_if(development_cards.begin(), development_cards.end(), [](development_card* c) { return c->get_type() == "Knight"; }) >= 3) {
            add_const_score(2);
            removeCardOfType("Knight");
        }
    }

    void Player::processMonopolyCard(Player& take1, Player& take2) {
        cout << "Choose a resource to monopolize: ";
        string resource;
        cin >> resource;
        takeResourceFromPlayer(take1, resource);
        takeResourceFromPlayer(take2, resource);
        removeCardOfType("Monopoly");
    }

    void Player::processYearOfHappyCard() {
        for (int i = 0; i < 2; ++i) {
            cout << "Choose a resource you want to take: ";
            string resource;
            cin >> resource;
            add_resources_card(resources_card(resource));
        }
        removeCardOfType("Year of Happy");
    }

    void Player::processRoadBuildingCard(board& board1) {
        for (int count = 0; count < 2; ++count) {
            int id, edge;
            cout << "Enter the tile id and edge id you want to set: ";
            cin >> id >> edge;
            while (!board1.getTile(id).setedges(edge, id)) {
                cout << "Enter the tile id and edge id you want to set: ";
                cin >> id >> edge;
            }
        }
        removeCardOfType("Road Building");
    }

    bool Player::removeCardOfType(const std::string& card_type) {
        auto it = std::find_if(development_cards.begin(), development_cards.end(), [&](development_card* c) { return c->get_type() == card_type; });
        if (it != development_cards.end()) {
            delete *it;
            development_cards.erase(it);
            return true;
        }
        return false;
    }

    void Player::takeResourceFromPlayer(Player& player, const std::string& resource) {
        auto& player_resources = player.getResources();
        auto it = std::remove_if(player_resources.begin(), player_resources.end(), [&](resources_card& rc) { return rc.get_type() == resource; });
        resources.insert(resources.end(), player_resources.begin(), it);
        player_resources.erase(it, player_resources.end());
    }
    int Player::getid()const {
        return id;
    }
    int Player::roll_number() {
        srand(static_cast<unsigned int>(time(0)));

        return rand() % 6 + 1+rand() % 6 + 1;}

    int Player::buy_road(int id,int edge,board& b){
        if(hasResources({"Brick", "Wood"})){
            if(b.getTile(id).setedges(edge,id))
            {
                removeResources({"Brick", "Wood"});
                std::cout<<"Road was bought at id:"<<id<<" edge "<<edge<<std::endl;
                return 1;
            }
            else{
                std::cout<<"Road was not bought at id:"<<id<<" edge "<<edge<<std::endl;
                return 0;
            }
            if(!hasResources({"Brick", "Wood"}))
            {
                std::cout<<"Road was not bought at you dont have the resources"<<std::endl;
                return 0;
            }
            if (!b.getTile(id).setedges(edge,id))
            {
                std::cout<<"Road was not bought beacuse there is road"<<std::endl;
            }
            removeResources({"Sheep", "Clay"});
            std::cout<<"Road was bought at id:"<<id<<" edge "<<edge<<std::endl;
            return 1;
        }
    }
    void Player::display_resources(){
        for (const auto& res : resources) {
            std::cout << res.get_type() << std::endl;
        }
    }
    void Player::display_development_cards(){
        for (const auto& card : development_cards) {
            card->display();
        }
    }


void Player::trade(Player& ask1) {
    std::string input;
    std::cout << "Enter the resources you want to receive and give, separated by a comma (e.g., wood, brick): ";
    std::getline(std::cin, input);

    size_t commaPos = input.find(',');
    if (commaPos != std::string::npos) {
        std::string wantResource = input.substr(0, commaPos);
        std::string giveResource = input.substr(commaPos + 1);

        // Trim whitespace
        auto trim = [](std::string& str) {
            str.erase(0, str.find_first_not_of(" \t\n\r\f\v"));
            str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);
        };
        trim(wantResource);
        trim(giveResource);

        if (ask1.hasResources({wantResource}) && hasResources({giveResource})) {
            char response;
            std::cout << "Player " << ask1.getName() << ", do you agree to trade your " << wantResource << " for " << giveResource << "? (y/n): ";
            std::cin >> response;
            std::cin.ignore(); // Clear the newline character from the input buffer

            if (response == 'y' || response == 'Y') {
                ask1.removeResources({wantResource});
                removeResources({giveResource});
                add_resources_card(resources_card(wantResource));
                ask1.add_resources_card(resources_card(giveResource));
                std::cout << "Trade successful!" << std::endl;
            } else {
                std::cout << "Player " << ask1.getName() << " declined the trade." << std::endl;
            }
        } else {
            if (!ask1.hasResources({wantResource})) {
                std::cout << "Player " << ask1.getName() << " does not have the requested resource." << std::endl;
            }
            if (!hasResources({giveResource})) {
                std::cout << "You do not have the resource to trade." << std::endl;
            }
        }
    } else {
        std::cout << "Invalid input. Please enter the resources in the format: resource1, resource2" << std::endl;
    }
}
}