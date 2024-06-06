#include "year_of_happy.hpp"
#include <iostream>

namespace ariel {
    year_of_happy::year_of_happy(std::string type, std::vector<resources_card> price)
        : promotion(type, price) {}

    void year_of_happy::display() const {
        std::cout << "Type: " << get_type() << std::endl;
        std::cout << "Price: ";
        for (const auto &card : get_price()) {
            std::cout << card.get_type() << " ";
        }
        std::cout << std::endl;
    }

    void year_of_happy::special_ability() const {
        std::cout << "Special ability of Year of Happy card" << std::endl;
    }
}
