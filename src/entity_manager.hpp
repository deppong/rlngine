#ifndef ECS_HPP
#define ECS_HPP

#include <map>
#include <array>
#include <iostream>

struct entity_t {
    unsigned int id;
};

static const int MAX_ENTITIES = 4096;

class EntityManager {
    public:
        EntityManager();
        ~EntityManager();

        entity_t create();
        std::array<entity_t, MAX_ENTITIES> entities;
    private:
        // This maps the entity's id to the same index used for the 
        // component manager
        int last_id;
};

#endif