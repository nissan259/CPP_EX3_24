#ifndef RESOURCES_CARD_HPP
#define RESOURCES_CARD_HPP

#include <string>

namespace ariel {
    class resources_card {
        std::string type;
    public:
        resources_card(std::string type);
        std::string get_type() const; // Marked as const
    };
}

#endif // RESOURCES_CARD_HPP
