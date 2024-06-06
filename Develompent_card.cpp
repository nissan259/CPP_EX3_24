#include "Develompent_card.hpp"

namespace ariel {
    development_card::development_card(std::string type, std::vector<resources_card> price)
        : type(type), price(price) {}

    std::string development_card::get_type() const {
        return type;
    }

    std::vector<resources_card> development_card::get_price() const {
        return price;
    }
}
