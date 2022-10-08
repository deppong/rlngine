#pragma once
#ifndef ZONE_HPP
#define ZONE_HPP

#include "entt.hpp"

class Zone {
    public:
        Zone(int width, int height);
        ~Zone();

        // "map generation"?
        void set_tile(entt::entity entity);


        entt::registry get_registry();

    private:
        entt::registry m_registry;

        int m_width, m_height;

};


#endif // ZONE_HPP