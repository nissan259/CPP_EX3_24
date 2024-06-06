#include "promotion.hpp"

namespace ariel {
    promotion::promotion(std::string type, std::vector<resources_card> price)
        : development_card(type, price) {}
}
