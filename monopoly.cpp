#include "monopoly.hpp"
#include <iostream>

namespace ariel {
    monopoly::monopoly(std::string type, std::vector<resources_card> price)
        : promotion(type, price) {}

    void monopoly::display() const {
        std::cout << "Type: " << get_type() << std::endl;
        std::cout << "Price: ";
        for (const auto &card : get_price()) {
            std::cout << card.get_type() << " ";
        }
        std::cout << std::endl;
    }

    void monopoly::special_ability() const {
        std::cout << "Special ability of Monopoly card" << std::endl;
    }
}
