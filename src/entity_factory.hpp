#pragma once
#ifndef ENTITY_FACTORY_HPP
#define ENTITY_FACTORY_HPP

/**
 * This class has the intention of constructing or adding entities
 * to a registry based on a file format, making entity construction
 * much smoother.
 * 
 * Example for the file format
 * "object_id" : {
 *      "component_id" : {
 *          "value_name" : "value",
 *          "value_2"    : "value"
 *      }
 * }
*/

#ifdef __unix__
    #include "../include/entt.hpp"
#elif defined _WIN32
    #include "entt.hpp"
#endif

#include "json.hpp"

class EntityFactory {
    public:
        // constructors
        EntityFactory();
        ~EntityFactory();

        // add an entity to the registry based on the file format
        // will require some reference to the file parser
        void add_object(entt::registry &registry);

    private:
};

#endif
