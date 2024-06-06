#include "road_build.hpp"
#include <iostream>

namespace ariel {
    road_build::road_build(std::string type, std::vector<resources_card> price)
        : promotion(type, price) {}

    void road_build::display() const {
        std::cout << "Type: " << get_type() << std::endl;
        std::cout << "Price: ";
        for (const auto &card : get_price()) {
            std::cout << card.get_type() << " ";
        }
        std::cout << std::endl;
    }

    void road_build::special_ability() const {
        std::cout << "Special ability of Road Build card" << std::endl;
    }
}
