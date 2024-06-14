#include <iostream>
#include <sstream>
#include <string>
#include "player.hpp"
#include "board.hpp"
#include "resources_card.hpp"
#include "year_of_happy.hpp"
#include "road_build.hpp"
#include "monopoly.hpp"
#include "knights.hpp"
#include "victory.hpp"
#include "doctest.h"

using namespace std;
using namespace ariel;

TEST_CASE("test create player") {
    Player p1("Orel");
    CHECK(p1.getName() == "Orel");
    Player p2("Nir");
    CHECK(p2.getName() == "Nir");
    Player p3("Amit");  
    CHECK(p3.getName() == "Amit");
}
TEST_CASE("test score") {
    Player p1("Orel");
    CHECK(p1.getScore() == 0);
    
}

TEST_CASE("test create board") {
    board b;
    std::ostringstream oss;
    std::streambuf* old_cout_buf = std::cout.rdbuf(oss.rdbuf());

    b.print_board();

    std::cout.rdbuf(old_cout_buf);

    std::string expected_output =
        "************ CATAN BOARD ************\n"
        "       sea   sea   sea   sea   sea       \n"
        "    sea Wheat  5 Wood  2 Brick  6 sea    \n"
        "  sea Sheep  3 Wood  8 Brick 10 Wheat  9 sea  \n"
        "sea Clay 12 Sheep 11 Desert  7 Sheep  6 Clay  4 sea\n"
        "  sea Wood  8 Wheat 10 Wood  9 Wheat 11 sea  \n"
        "    sea Sheep  3 Wood  4 Clay  5 sea    \n"
        "       sea   sea   sea   sea   sea       \n"
        "*************************************\n";

    CHECK(oss.str() == expected_output);
}
TEST_CASE("test create resources card") {
    resources_card r1("Wood");
    CHECK(r1.get_type() == "Wood");
    resources_card r2("Brick");
    CHECK(r2.get_type() == "Brick");
    resources_card r3("Sheep");
    CHECK(r3.get_type() == "Sheep");
    resources_card r4("Wheat");
    CHECK(r4.get_type() == "Wheat");
    resources_card r5("Clay");
    CHECK(r5.get_type() == "Clay");
}
TEST_CASE("test add resources to player") {
    Player p1("Orel");
    resources_card r1("Wood");
    resources_card r2("Brick");
    resources_card r3("Sheep");
    resources_card r4("Wheat");
    resources_card r5("Clay");
    p1.add_resources_card(r1);
    p1.add_resources_card(r2);
    p1.add_resources_card(r3);
    p1.add_resources_card(r4);
    p1.add_resources_card(r5);
    CHECK(p1.getResources().size() == 5);
}
TEST_CASE("test add development cards to player") {
    Player p1("Orel");
    development_card* d1 = p1.createDevelopmentCard("victory");
    development_card* d2 = p1.createDevelopmentCard("year_of_happy");
    development_card* d3 = p1.createDevelopmentCard("road_build");
    development_card* d4 = p1.createDevelopmentCard("monopoly");
    development_card* d5 = p1.createDevelopmentCard("knights");
    p1.add_development_cards(d1);
    p1.add_development_cards(d2);
    p1.add_development_cards(d3);
    p1.add_development_cards(d4);
    p1.add_development_cards(d5);
    CHECK(p1.getDevelopment_cards().size() == 5);
}
TEST_CASE("test add score to player") {
    Player p1("Orel");
    p1.add_const_score(5);
    CHECK(p1.getScore() == 4);
}
TEST_CASE("test buy card") {
    Player p1("Orel");
    resources_card r1("Wood");
    resources_card r2("Brick");
    resources_card r3("Sheep");
    resources_card r4("Wheat");
    resources_card r5("Clay");
        development_card* d1 = p1.createDevelopmentCard("victory");
    p1.add_development_cards(d1);
    p1.buy_card();
    CHECK(p1.getDevelopment_cards().size() == 0);
}
TEST_CASE("test get random card") {
    bool year_of_happy=false;
    bool monopoly=false;
    bool knights=false;
    bool victory=false;
    bool road_build=false;
        Player p1("Orel");
    while (!(year_of_happy&&monopoly&&knights&&victory&&road_build))
    {
    if(p1.getrandomcard()=="year_of_happy")
    {
        year_of_happy=true;
    
    }
    if(p1.getrandomcard()=="monopoly")
    {
        monopoly=true;
    
    }
    if(p1.getrandomcard()=="knights")
    {
        knights=true;
    
    }
    if(p1.getrandomcard()=="victory")
    {
        victory=true;
    
    }
    if(p1.getrandomcard()=="road_build")
    {
        road_build=true;
    
    }
    CHECK(year_of_happy&&monopoly&&knights&&victory&&road_build==true);
    }
}

TEST_CASE("test use development card") {
    Player p1("Orel");
    Player p2("Nir");
    board b;
    development_card* d1 = p1.createDevelopmentCard("victory");
    development_card* d2 = p1.createDevelopmentCard("year_of_happy");
    development_card* d3 = p1.createDevelopmentCard("road_build");
    development_card* d4 = p1.createDevelopmentCard("monopoly");
    development_card* d5 = p1.createDevelopmentCard("knights");
    p1.add_development_cards(d1);
    p1.add_development_cards(d2);
    p1.add_development_cards(d3);
    p1.add_development_cards(d4);
    p1.add_development_cards(d5);
    int counter=0;
    for(int i=0;i<5;i++)
    {
        if(p1.use(d1, p1, p2, b)==1)
        {
            counter++;
        }
        {
            counter++;
        }
    }
    CHECK(counter==5);
}
TEST_CASE("test buy road") {
    Player p1("Orel");
    board b;
    int turn=1;
    int id=0;
    int edge=0;
    p1.buy_road(id,edge,b,turn);
    CHECK(p1.getScore()==0);
}

TEST_CASE("test buy settlement") {
    Player p1("Orel");
    board b;
    int turn=1;
    int id=0;
    int vertex=0;
        int edge=0;
    p1.buy_road(id,edge,b,turn);
    p1.buy_stelment(id,vertex,b,turn);
    CHECK(p1.getScore()==1);
}
TEST_CASE("test buy city") {
    Player p1("Orel");
    board b;
    int turn=1;
    int id=0;
    int vertex=0;
        int edge=0;
    p1.buy_road(id,edge,b,turn);
    p1.buy_stelment(id,vertex,b,turn);
    p1.buy_city(id,vertex,b,turn);
    CHECK(p1.getScore()==2);
}
TEST_CASE("test roll number") {
    Player p1("Orel");
    Player p2("Nir");
    Player p3("Amit");
    int resourcesp1=p1.getResources().size();
    int resourcesp2=p2.getResources().size();
    int resourcesp3=p3.getResources().size();
    board b;
    p1.roll_number(b, p2, p3);
    CHECK(p1.getResources().size()>=resourcesp1+1&&p2.getResources().size()>=resourcesp2&&p3.getResources().size()>=resourcesp3);   
}
TEST_CASE("test trade") {
    Player p1("Orel");
    Player p2("Nir");
    resources_card r1("Wood");
    resources_card r2("Brick");
    resources_card r3("Sheep");
    resources_card r4("Wheat");
    resources_card r5("Clay");
    resources_card r6("Wood");

    p1.add_resources_card(r1);
    p1.add_resources_card(r2);
    p1.add_resources_card(r3);
    p1.add_resources_card(r4);
    p1.add_resources_card(r5);
    p2.add_resources_card(r6);

    std::istringstream input("Wood\nClay,Brick\ny\n");
    std::streambuf* old_cin_buf = std::cin.rdbuf(input.rdbuf());

    p1.trade(p2);

    std::cin.rdbuf(old_cin_buf);

    CHECK(p1.getResources().size() == 4);
    CHECK(p2.getResources().size() == 3);

    // Additional checks to verify the actual resources
    std::vector<std::string> p1_expected = {"Wood", "Sheep", "Wheat", "Wood"};
    std::vector<std::string> p2_expected = {"Clay", "Brick", "Wood"};

    auto p1_resources = p1.getResources();
    auto p2_resources = p2.getResources();

    CHECK(p1_resources.size() == p1_expected.size());
    CHECK(p2_resources.size() == p2_expected.size());

    for (const auto& res : p1_expected) {
        CHECK(std::find(p1_resources.begin(), p1_resources.end(), res) != p1_resources.end());
    }

    for (const auto& res : p2_expected) {
        CHECK(std::find(p2_resources.begin(), p2_resources.end(), res) != p2_resources.end());
    }
}
TEST_CASE("test display development cards") {
    Player p1("Orel");
    development_card* d1 = p1.createDevelopmentCard("victory");
    development_card* d2 = p1.createDevelopmentCard("year_of_happy");
    development_card* d3 = p1.createDevelopmentCard("road_build");
    development_card* d4 = p1.createDevelopmentCard("monopoly");
    development_card* d5 = p1.createDevelopmentCard("knights");
    p1.add_development_cards(d1);
    p1.add_development_cards(d2);
    p1.add_development_cards(d3);
    p1.add_development_cards(d4);
    p1.add_development_cards(d5);
    std::ostringstream oss;
    std::streambuf* old_cout_buf = std::cout.rdbuf(oss.rdbuf());

    p1.display_development_cards();

    std::cout.rdbuf(old_cout_buf);

    std::string expected_output =
        "Player Orel's development cards:\n"
        "victory\n"
        "year_of_happy\n"
        "road_build\n"
        "monopoly\n"
        "knights\n";

    CHECK(oss.str() == expected_output);
}
TEST_CASE("test display resources") {
    Player p1("Orel");
    resources_card r1("Wood");
    resources_card r2("Brick");
    resources_card r3("Sheep");
    resources_card r4("Wheat");
    resources_card r5("Clay");
    p1.add_resources_card(r1);
    p1.add_resources_card(r2);
    p1.add_resources_card(r3);
    p1.add_resources_card(r4);
    p1.add_resources_card(r5);
    std::ostringstream oss;
    std::streambuf* old_cout_buf = std::cout.rdbuf(oss.rdbuf());

    p1.display_resources();

    std::cout.rdbuf(old_cout_buf);

    std::string expected_output =
        "Player Orel's resources:\n"
        "Wood\n"
        "Brick\n"
        "Sheep\n"
        "Wheat\n"
        "Clay\n";

    CHECK(oss.str() == expected_output);
}
TEST_CASE("test display roads") {
    Player p1("Orel");
    p1.add_road("road1");
    p1.add_road("road2");
    p1.add_road("road3");
    std::ostringstream oss;
    std::streambuf* old_cout_buf = std::cout.rdbuf(oss.rdbuf());

    p1.display_roads();

    std::cout.rdbuf(old_cout_buf);

    std::string expected_output =
        "Player Orel's roads:\n"
        "road1\n"
        "road2\n"
        "road3\n";

    CHECK(oss.str() == expected_output);
}
TEST_CASE("test display settlements") {
    Player p1("Orel");
    p1.add_settlement("settlement1");
    p1.add_settlement("settlement2");
    p1.add_settlement("settlement3");
    std::ostringstream oss;
    std::streambuf* old_cout_buf = std::cout.rdbuf(oss.rdbuf());

    p1.display_settlements();

    std::cout.rdbuf(old_cout_buf);

    std::string expected_output =
        "Player Orel's settlements:\n"
        "settlement1\n"
        "settlement2\n"
        "settlement3\n";

    CHECK(oss.str() == expected_output);
}
TEST_CASE("test display cities") {
    Player p1("Orel");
    p1.add_city("city1");
    p1.add_city("city2");
    p1.add_city("city3");
    std::ostringstream oss;
    std::streambuf* old_cout_buf = std::cout.rdbuf(oss.rdbuf());

    p1.display_cities();

    std::cout.rdbuf(old_cout_buf);

    std::string expected_output =
        "Player Orel's cities:\n"
        "city1\n"
        "city2\n"
        "city3\n";

    CHECK(oss.str() == expected_output);
}
TEST_CASE("test end turn") {
    Player p1("Orel");
    p1.add_const_score(5);
    p1.end_turn();
    CHECK(p1.getScore() == 5);
}
TEST_CASE("test create development card") {
    Player p1("Orel");
    development_card* d1 = p1.createDevelopmentCard("victory");
    development_card* d2 = p1.createDevelopmentCard("year_of_happy");
    development_card* d3 = p1.createDevelopmentCard("road_build");
    development_card* d4 = p1.createDevelopmentCard("monopoly");
    development_card* d5 = p1.createDevelopmentCard("knights");
    CHECK(d1->get_type() == "victory");
    CHECK(d2->get_type() == "year_of_happy");
    CHECK(d3->get_type() == "road_build");
    CHECK(d4->get_type() == "monopoly");
    CHECK(d5->get_type() == "knights");
}
TEST_CASE("check victory card") {
    Player p1("Orel");
    Player p2("Nir");
    Player p3("Amit");
    board b;
    development_card* d1 = p1.createDevelopmentCard("victory");
    development_card* d2 = p1.createDevelopmentCard("victory");
    development_card* d3 = p1.createDevelopmentCard("victory");
    development_card* d4 = p1.createDevelopmentCard("victory");
    development_card* d5 = p1.createDevelopmentCard("victory");
    p1.add_development_cards(d1);
    p1.add_development_cards(d2);
    p1.add_development_cards(d3);
    p1.add_development_cards(d4);
    p1.add_development_cards(d5);
    p1.use(d1, p1, p2, b);
    CHECK(p1.getScore() == 1);
}
TEST_CASE("check year of happy card") {
    Player p1("Orel");
    Player p2("Nir");
    Player p3("Amit");
    board b;
    development_card* d1 = p1.createDevelopmentCard("year_of_happy");
    development_card* d2 = p1.createDevelopmentCard("year_of_happy");
    development_card* d3 = p1.createDevelopmentCard("year_of_happy");
    development_card* d4 = p1.createDevelopmentCard("year_of_happy");
    development_card* d5 = p1.createDevelopmentCard("year_of_happy");
    p1.add_development_cards(d1);
    p1.add_development_cards(d2);
    p1.add_development_cards(d3);
    p1.add_development_cards(d4);
    p1.add_development_cards(d5);
    p1.use(d1, p1, p2, b);
    CHECK(p1.getResources().size() == 10);
}
TEST_CASE("check year of happy card") {
    Player p1("Orel");
    Player p2("Nir");
    Player p3("Amit");
    board b;
    development_card* d1 = p1.createDevelopmentCard("year_of_happy");
    development_card* d2 = p1.createDevelopmentCard("year_of_happy");
    development_card* d3 = p1.createDevelopmentCard("year_of_happy");
    development_card* d4 = p1.createDevelopmentCard("year_of_happy");
    development_card* d5 = p1.createDevelopmentCard("year_of_happy");
    p1.add_development_cards(d1);
    p1.add_development_cards(d2);
    p1.add_development_cards(d3);
    p1.add_development_cards(d4);
    p1.add_development_cards(d5);

    std::istringstream input("Wood\nBrick\n");
    std::streambuf* old_cin_buf = std::cin.rdbuf(input.rdbuf());

    p1.use(d1, p1, p2, b);

    std::cin.rdbuf(old_cin_buf);

    CHECK(p1.getResources().size() == 7);

    // Verify that the resources added are as expected
    std::vector<std::string> p1_expected = {"Wood", "Brick"};

    auto p1_resources = p1.getResources();
    CHECK(p1_resources.size() == p1_expected.size() + 5); // Existing 5 resources + 2 new resources = 7

    for (const auto& res : p1_expected) {
        CHECK(std::find(p1_resources.begin(), p1_resources.end(), res) != p1_resources.end());
    }
}
TEST_CASE("test process Knight card") {
    Player p1("Orel");
    Player p2("Nir");
    Player p3("Amit");
    board b;
    development_card* k1 = p1.createDevelopmentCard("Knight");
    development_card* k2 = p1.createDevelopmentCard("Knight");
    development_card* k3 = p1.createDevelopmentCard("Knight");

    p1.add_development_cards(k1);
    p1.add_development_cards(k2);
    p1.add_development_cards(k3);

    CHECK(p1.getScore() == 0);

    p1.use(k1, p1, p1, b);
    CHECK(p1.getScore() == 2);
}



