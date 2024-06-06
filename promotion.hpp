#ifndef PROMOTION_HPP
#define PROMOTION_HPP

#include <string>
#include <vector>
#include "Develompent_card.hpp"

namespace ariel {
    class promotion : public development_card {
    public:
        promotion(std::string type, std::vector<resources_card> price);
        virtual void display() const = 0; // Pure virtual function
        virtual void special_ability() const = 0; // Additional pure virtual function
    };
}

#endif // PROMOTION_HPP
