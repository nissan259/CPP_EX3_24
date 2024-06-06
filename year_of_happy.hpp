#ifndef YEAR_OF_HAPPY_HPP
#define YEAR_OF_HAPPY_HPP

#include "promotion.hpp"

namespace ariel {
    class year_of_happy : public promotion {
    public:
        year_of_happy(std::string type, std::vector<resources_card> price);
        void display() const override;
        void special_ability() const override;
    };
}

#endif // YEAR_OF_HAPPY_HPP
