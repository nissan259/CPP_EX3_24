#ifndef MONOPOLY_HPP
#define MONOPOLY_HPP

#include "promotion.hpp"

namespace ariel {
    class monopoly : public promotion {
    public:
        monopoly(std::string type, std::vector<resources_card> price);
        void display() const override;
        void special_ability() const override;
    };
}

#endif // MONOPOLY_HPP
