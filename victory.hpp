#ifndef VICTORY_HPP
#define VICTORY_HPP

#include <string>
#include <vector>
#include "Develompent_card.hpp"
#include "resources_card.hpp"

namespace ariel {
    class victory : public development_card {
        static int counter_victory; // Make it static
    public:
        victory(std::string type, std::vector<resources_card> price);
        void display() const override;
        static int get_counter_victory(); // Static method
    };
}

#endif // VICTORY_HPP
