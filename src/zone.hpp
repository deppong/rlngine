#pragma once
#ifndef ZONE_HPP
#define ZONE_HPP

#ifdef __unix__
    #include "../include/entt.hpp"
#elif defined _WIN32
    #include "entt.hpp"
#endif

#include "components.hpp"
#include "atlas.hpp"
#include "color.hpp"
#include <iostream>

class Zone {
    public:
        Zone();
        Zone(int width, int height);
        ~Zone();

        // "zone generation"?
        void make_room(int x, int y, int w, int h);

        // zone update
        void update_physics();

        entt::registry m_registry;

        int m_width, m_height;
    private:


};


#endif // ZONE_HPP
