#include "victory.hpp"
#include <iostream>

namespace ariel {
    int victory::counter_victory = 0; // Define the static member

    victory::victory(std::string type, std::vector<resources_card> price)
        : development_card(type, price) {
        counter_victory++; // Increment the counter in the constructor
    }

    void victory::display() const {
        std::cout << "Type: " << get_type() << std::endl;
        std::cout << "Price: ";
        for (const auto &card : get_price()) {
            std::cout << card.get_type() << " ";
        }
        std::cout << std::endl;
        std::cout << "Victory Cards Count: " << counter_victory << std::endl;
    }

    int victory::get_counter_victory() {
        return counter_victory; // Define the get_counter_victory method
    }
}
