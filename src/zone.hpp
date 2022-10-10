#pragma once
#ifndef ZONE_HPP
#define ZONE_HPP

#include "entt.hpp"
#include "components.hpp"
#include "atlas.hpp"
#include "color.hpp"
#include <iostream>

class Zone {
    public:
        Zone();
        Zone(int width, int height);
        ~Zone();

        // copy constructor
        // Zone(const Zone &zone) {
        //     m_width = zone.m_width;
        //     m_height = zone.m_height;
        //     m_registry = zone.m_registry;
        // };

        // "map generation"?
        void set_tile(entt::entity entity);
        void fill_zone(entt::entity entity);
        void fill_zone_walls(std::vector<uint32_t> &tex);

        // zone update
        void update_physics();

        entt::registry m_registry;

        int m_width, m_height;
    private:


};


#endif // ZONE_HPP