#ifndef KNIGHTS_HPP
#define KNIGHTS_HPP

#include <string>
#include <vector>
#include "Develompent_card.hpp"
#include "resources_card.hpp"
#include "player.hpp"

namespace ariel {
    class knights : public development_card {
        static int number_of_knights;
    public:
        knights(std::string type, std::vector<resources_card> &price);
        void display() const override; // Implementing the pure virtual function
        static int get_number_of_knights(); // Static method
    };
}

#endif // KNIGHTS_HPP
