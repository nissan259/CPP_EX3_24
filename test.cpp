#include "doctest.h"
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
#include <string> 

using namespace ariel;

TEST_CASE("initialize_player")
{
    Player p1("orel");
    CHECK(p1.getName() == "orel"); 
    CHECK(p1.getScore() == 0);
    CHECK(p1.getId() == 1); // Fixed typo from getid() to getId()
}

TEST_CASE("initialize_resources_card")
{
    resources_card r1("Wood");
    resources_card r2("Brick");
    resources_card r3("Sheep");
    resources_card r4("Wheat");
    resources_card r5("Clay");

    CHECK(r1.get_type() == "Wood");
    CHECK(r2.get_type() == "Brick");
    CHECK(r3.get_type() == "Sheep");
    CHECK(r4.get_type() == "Wheat");
    CHECK(r5.get_type() == "Clay");
}

TEST_CASE("initialize_board_print")
{
    board b1;
    b1.print(); // This assumes print() has a visible output or returns something that can be checked
}
TEST_CASE("initialize_year_of_happy")
{
    year_of_happy y1;
    CHECK(y1.get_type() == "Year of Plenty");
}
TEST_CASE("initialize_road_build")
{
    road_build r1;
    CHECK(r1.get_type() == "Road Building");
}
TEST_CASE("initialize_monopoly")
{
    monopoly m1;
    CHECK(m1.get_type() == "Monopoly");
}
TEST_CASE("initialize_knights")
{
    knights k1;
    CHECK(k1.get_type() == "Knights");
}
TEST_CASE("initialize_victory")
{
    victory v1;
    CHECK(v1.get_type() == "Victory");
}
TEST_CASE("check_board_print")
{
    
}
TEST_CASE("check_player")
{
    Player p1("orel");
    p1.setScore(5);
    CHECK(p1.getScore() == 5);
    p1.setScore(10);
    CHECK(p1.getScore() == 10);
    p1.setScore(0);
    CHECK(p1.getScore() == 0);
}
TEST_CASE("check_resources_card")
{
    resources_card r1("Wood");
    r1.set_type("Brick");
    CHECK(r1.get_type() == "Brick");
    r1.set_type("Sheep");
    CHECK(r1.get_type() == "Sheep");
    r1.set_type("Wheat");
    CHECK(r1.get_type() == "Wheat");
    r1.set_type("Clay");
    CHECK(r1.get_type() == "Clay");
}
TEST_CASE("check_year_of_happy")
{
    year_of_happy y1;
    y1.set_type("Year of Plenty");
    CHECK(y1.get_type() == "Year of Plenty");
}


