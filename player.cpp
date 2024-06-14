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
#include <sstream>

using namespace std;

namespace ariel {
    int Player::id = -2;

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
    void Player::add_road(std::string road)
    {
        roads.push_back(road);
    }
    void Player:: add_settlement(std::string settlement)
    {
        settlements.push_back(settlement);
    }
    void Player:: add_city(std::string city)
    {
        cities.push_back(city);
    }
    void Player:: display_roads()
    {
        std::cout << getName()<<" your Roads are: " << std::endl;
       for(size_t i=0;i<roads.size();i++)
       {
           std::cout<<roads.at(i)<<std::endl;
       }
    }
 void Player::display_development_cards()
{
    if (getDevelopment_cards().empty())
    {
        std::cout << getName() << ", you don't have any development cards." << std::endl;
    }
    else
    {
        for (const auto &card : getDevelopment_cards())
        {
            card->display();
        }
    }
}
    void Player:: display_settlements()
    {
        for (const auto& settlement : settlements) {
            std::cout << settlement << std::endl;
        }
    }
 void Player::display_cities()
{
    if (cities.empty())
    {
        std::cout << getName() << ", you don't have any cities." << std::endl;
    }
    else
    {
        for (const auto &city : cities)
        {
            std::cout << city << std::endl;
        }
    }
}
    


    void Player::buy_card() {
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
    // Create a copy of the resources to remove to keep track of what has been removed
    std::vector<std::string> to_remove = resources_to_remove;

    for (auto it = to_remove.begin(); it != to_remove.end(); ++it) {
        // Find the resource in the player's resources
        auto res_it = std::find_if(resources.begin(), resources.end(),
            [&](resources_card& rc) {
                return rc.get_type() == *it;
            });

        // If found, remove the resource
        if (res_it != resources.end()) {
            resources.erase(res_it);
        }
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
    int Player::getid() {
        return id;
    }
int Player::roll_number(board& b, Player& p1, Player &p2) {
    srand(static_cast<unsigned int>(time(0)));
    int roll = rand() % 6 + 1 + rand() % 6 + 1;
    std::cout << "The number is: " << roll << std::endl;

    if (roll == 7) {
        // Handle resources for the current player
        if (getResources().size() > 7) {
            display_resources();
            std::cout << getName() << " has more than 7 resources. Cutting resources by half." << std::endl;
            int numResourcesToRemove = getResources().size() / 2;
            for (int i = 0; i < numResourcesToRemove; ++i) {
                std::string resource;
                std::cout << "Enter the resource you want to remove: ";
                std::cin >> resource;
                if (hasResources({resource})) {
                    removeResources({resource});
                } else {
                    std::cout << "Resource not found. Please enter a valid resource." << std::endl;
                    --i;
                }
            }
        } else {
            std::cout << getName() << " has 7 or fewer resources. No need to remove resources." << std::endl;
        }

        // Handle resources for player 1
        if (p1.getResources().size() > 7) {
            p1.display_resources();
            std::cout << p1.getName() << " has more than 7 resources. Cutting resources by half." << std::endl;
            int numResourcesToRemove = p1.getResources().size() / 2;
            for (int i = 0; i < numResourcesToRemove; ++i) {
                std::string resource;
                std::cout << "Enter the resource you want to remove: ";
                std::cin >> resource;
                if (p1.hasResources({resource})) {
                    p1.removeResources({resource});
                } else {
                    std::cout << "Resource not found. Please enter a valid resource." << std::endl;
                    --i;
                }
            }
        } else {
            std::cout << p1.getName() << " has 7 or fewer resources. No need to remove resources." << std::endl;
        }

        // Handle resources for player 2
        if (p2.getResources().size() > 7) {
            p2.display_resources();
            std::cout << p2.getName() << " has more than 7 resources. Cutting resources by half." << std::endl;
            int numResourcesToRemove = p2.getResources().size() / 2;
            for (int i = 0; i < numResourcesToRemove; ++i) {
                std::string resource;
                std::cout << "Enter the resource you want to remove: ";
                std::cin >> resource;
                if (p2.hasResources({resource})) {
                    p2.removeResources({resource});
                } else {
                    std::cout << "Resource not found. Please enter a valid resource." << std::endl;
                    --i;
                }
            }
        } else {
            std::cout << p2.getName() << " has 7 or fewer resources. No need to remove resources." << std::endl;
        }
        return 1;
    }

    for (int i = 0; i < 19; ++i) {
        std::cout << "The number is: " << i << std::endl;
        try {
            const auto& vertexes = b.getTile(i).getvertexes();
            if (b.getTile(i).getvalue_roll() == roll) {
                for (int j = 0; j < 6; ++j) {
                    try {
                        const auto& type = vertexes.at(1).at(j);
                        const auto& id = vertexes.at(0).at(j);

                        if (id == p1.getid()) {
                            if (type == 2) {
                                std::cout << "Player 1 gets 2 resources of type " << b.getTile(i).gettype() << std::endl;
                                p1.add_resources_card(resources_card(b.getTile(i).gettype()));
                                p1.add_resources_card(resources_card(b.getTile(i).gettype()));
                            } else if (type == 1) {
                                                                std::cout << "Player 1 gets 1 resources of type " << b.getTile(i).gettype() << std::endl;
                                p1.add_resources_card(resources_card(b.getTile(i).gettype()));
                            }
                        }
                        if (id == p2.getid()) {
                            if (type == 2) {
                                std::cout << "Player 2 gets 2 resources of type " << b.getTile(i).gettype() << std::endl;
                                p2.add_resources_card(resources_card(b.getTile(i).gettype()));
                                p2.add_resources_card(resources_card(b.getTile(i).gettype()));
                            } else if (type == 1) {
                                p2.add_resources_card(resources_card(b.getTile(i).gettype()));
                            }
                        }
                        if (id == getid()) {
                            if (type == 2) {
                                std::cout << "You get 2 resources of type " << b.getTile(i).gettype() << std::endl;
                                add_resources_card(resources_card(b.getTile(i).gettype()));
                                add_resources_card(resources_card(b.getTile(i).gettype()));
                            } else if (type == 1) {
                                add_resources_card(resources_card(b.getTile(i).gettype()));
                            }
                        }
                    } catch (const std::out_of_range& e) {
                        std::cerr << "Out of range exception in roll_number (inner loop): " << e.what() << std::endl;
                        continue; // Skip to the next iteration
                    }
                }
            }
        } catch (const std::out_of_range& e) {
            std::cerr << "Out of range exception in roll_number (outer loop): " << e.what() << std::endl;
            continue; // Skip to the next iteration
        }
    }
    return 1;
}

    int Player::buy_road(int tile,int edge,board& b,int turn){
        if(hasResources({"Brick", "Wood"})){
            if(b.getTile(id).setedges(edge,id)&&turn!=3)
            {
                std::cout<<"orel"<<id<<" nissan "<<edge<<std::endl;
                removeResources({"Brick", "Wood"});
                std::cout<<"Road was bought at id:"<<tile<<" edge "<<edge<<std::endl;
                 std::string type="you have city at id:"+std::to_string(tile)+" vertex "+std::to_string(edge);
                add_road(type);
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
        return 0;  
    }
    int Player::buy_city(int tile,int vertex,board& b,int turn)
    {
     

        if(hasResources({"Clay","Clay", "Wheat", "Clay","Wheat"})){
            if(b.getTile(tile).getvertexes().at(0).at(0)==id)
            {
                removeResources({"Clay","Clay", "Wheat", "Clay","Wheat"});
                std::cout<<"Stelment was bought at id:"<<id<<" vertex "<<vertex<<std::endl;
                b.getTile(tile).getvertexes().at(1).at(vertex)=2;
                add_const_score(1);
                std::cout<<"you have now "<<getScore()<<" points"<<std::endl;
                std::string type="you have city at id:"+std::to_string(id)+" vertex "+std::to_string(vertex);
                add_city(type);
                return 1;
            }
            else{
                std::cout<<"Stelment was not bought at tile:"<<tile<<" vertex "<<vertex<<std::endl;
                return 0;
            }
            if(!hasResources({"Clay","Clay", "Wheat", "Clay","Wheat"}))
            {
                std::cout<<"Stelment was not bought at you dont have the resources"<<std::endl;
                return 0;
            }
            if (!b.getTile(tile).setedges(vertex,getid()))
            {
                std::cout<<"Stelment was not bought beacuse there is stelment"<<std::endl;
            }
            removeResources({"Clay","Clay", "Wheat", "Clay","Wheat"});
            std::cout<<"Stelment was bought at id:"<<id<<" vertex "<<vertex<<std::endl;
        }
        return 1;
    }
    int Player::buy_stelment(int id,int vertex,board &b,int turn)
    {
        if(hasResources({"Clay","Wood", "Wheat", "Sheep"})){
            if(b.getTile(id).set_vertex(vertex,id,getid()))
            {
                removeResources({"Clay","Wood", "Wheat", "Sheep"});
                std::cout<<"Stelment was bought at id:"<<id<<" vertex "<<vertex<<std::endl;
                add_const_score(1);
              std::string type="the tile"+std::to_string(id)+"put settlement in vertex"+std::to_string(vertex);
                add_settlement(type);
                return 1;
            }
            else{
                std::cout<<"Stelment was not bought at id:"<<id<<" vertex "<<vertex<<std::endl;
                return 0;
            }
            if(!hasResources({"Clay","Wood", "Wheat", "Sheep"}))
            {
                std::cout<<"Stelment was not bought at you dont have the resources"<<std::endl;
                return 0;
            }
            if (!b.getTile(id).set_vertex(vertex,id,getid()))
            {
                std::cout<<"Stelment was not bought beacuse there is stelment"<<std::endl;
            }
            removeResources({"Clay","Wood", "Wheat", "Sheep"});
            std::cout<<"Stelment was bought at id:"<<id<<" vertex "<<vertex<<std::endl;
            return 1;
        }
        return 0;
    }

 void Player::display_resources()
{
    std::cout << getName() << " your resources are:" << std::endl;
    if (resources.empty())
    {
        std::cout << "You don't have any resources." << std::endl;
    }
    else
    {
        for (const auto &res : resources)
        {
            std::cout << res.get_type() << std::endl;
        }
    }
}

    void to_lowercase(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}
std::vector<std::string> splitStringByComma(const std::string& str) {
    std::vector<std::string> result;
    std::istringstream stream(str);
    std::string token;

    while (std::getline(stream, token, ',')) {
        // Trim whitespace
        token.erase(0, token.find_first_not_of(" \t\n\r\f\v"));
        token.erase(token.find_last_not_of(" \t\n\r\f\v") + 1);
        result.push_back(token);
    }

    return result;
}


void Player::trade(Player& ask1) {
    std::string resource_take;
    std::string resource_give;
    std::cout << "Enter the resource you want to trade:";
    std::cin >> resource_take;    
    std::cout << "Enter the resource you want to give:";
    std::cin >> resource_give;
    std::vector<resources_card> resources_take = ask1.getResources();
    std::vector<resources_card> resources2_give = getResources();
    std::vector<std::string> resources_give_str=splitStringByComma(resource_give);
    std::vector<std::string> resources_take_str=splitStringByComma(resource_take);
    std::cout << "the ofer is take:"<<resource_take<<" give:"<<resource_give<<std::endl;
    char answer;
    std::cout << "Do you accept the trade? (y/n):";
    std::cin >> answer;
    if(answer=='Y'||answer=='y')
    {
        if(this->hasResources(resources_give_str)&&ask1.hasResources(resources_take_str))
        {
            this->removeResources(resources_give_str);
            ask1.removeResources(resources_take_str);
            for(const auto& res:resources_give_str)
            {
                ask1.add_resources_card(resources_card(res));
            }
            for(const auto& res:resources_take_str)
            {
                this->add_resources_card(resources_card(res));
            }
            std::cout << "Trade was accepted" << std::endl;
            std::cout << "Your resources after trade:" << std::endl;
            this->display_resources();
        }
        else
        {
            std::cout << "Trade was not accepted" << std::endl;
        }
    }
    else
    {
        std::cout << "Trade was not accepted" << std::endl;
    }
}
    void Player::end_turn() {
        std::cout << "Ending turn" <<  std::endl;
        std::cout << "Your score: " << getScore() << std::endl;
        display_roads();
        std::cout << "Your settlements: " << std::endl;
        display_settlements();
        display_cities();
        display_resources();
        display_development_cards();
}
}
