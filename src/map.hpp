#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "entity.hpp"

class Map {
    public:
        int map_w, map_h;

        Map(int win_width, int win_height, int tex_width);
        ~Map();

        void render();


    private:
        std::vector<entity_t> entities;
};

#endif