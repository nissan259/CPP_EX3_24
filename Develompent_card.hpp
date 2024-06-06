#ifndef DEVELOMPENT_CARD_HPP
#define DEVELOMPENT_CARD_HPP

#include <string>
#include <vector>
#include "resources_card.hpp"

namespace ariel {

    class development_card {
        std::string type;
        std::vector<resources_card> price;
    public:
        development_card(std::string type, std::vector<resources_card> price);
        std::string get_type() const;
        std::vector<resources_card> get_price() const;
        virtual void display() const = 0; // Pure virtual function
        virtual ~development_card() = default; // Virtual destructor
    };
}

#endif // DEVELOMPENT_CARD_HPP
