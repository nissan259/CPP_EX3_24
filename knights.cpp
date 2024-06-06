#include "knights.hpp"
#include <iostream>

namespace ariel {
    int knights::number_of_knights = 0;

    knights::knights(std::string type, std::vector<resources_card> &price)
        : development_card(type, price)  {
            number_of_knights++;
        }

    void knights::display() const {
        std::cout << "Type: " << get_type() << std::endl;
        std::cout << "Price: ";
        for (const auto &card : get_price()) {
            std::cout << card.get_type() << " ";
        }
        std::cout << std::endl;
        std::cout << "Number of Knights: " << number_of_knights << std::endl;
    }
     int knights::get_number_of_knights() {
        return number_of_knights;
    }
}
