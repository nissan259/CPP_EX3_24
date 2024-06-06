#ifndef ROAD_BUILD_HPP
#define ROAD_BUILD_HPP

#include "promotion.hpp"

namespace ariel {
    class road_build : public promotion {
    public:
        road_build(std::string type, std::vector<resources_card> price);
        void display() const override;
        void special_ability() const override;
    };
}

#endif // ROAD_BUILD_HPP
