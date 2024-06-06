#include "resources_card.hpp"

namespace ariel {
    resources_card::resources_card(std::string type) : type(type) {}

    std::string resources_card::get_type() const { // Marked as const
        return type;
    }
}
