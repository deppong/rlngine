#pragma once
#ifndef ZONE_HPP
#define ZONE_HPP

#include "entt.hpp"
#include "components.hpp"
#include "color.hpp"
#include <iostream>

class Zone {
    public:
        Zone();
        Zone(int width, int height);
        ~Zone();

        // "map generation"?
        void set_tile(entt::entity entity);
        void fill_zone(entt::entity entity);
        void fill_zone_walls();

        // zone update
        void update_physics();

        entt::registry m_registry;

    private:
        int m_width, m_height;


};


#endif // ZONE_HPP