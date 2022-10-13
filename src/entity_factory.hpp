#pragma once
#ifndef ENTITY_FACTORY_HPP
#define ENTITY_FACTORY_HPP

/**
 * This class has the intention of constructing or adding entities
 * to a registry based on a file format, making entity construction
 * much smoother. There is something to be seriously considered. 
 * if the object base becomes very large, I should really not just load 
 * all of them, but load them in a smart/lazy way, meaning: only load the 
 * files in which we need objects from. I could also have an option in 
 * the json loader to remove certain objects that we've loaded on every
 * zone load, however I can add this if I see it as being necessary
 * 
 * Example for the file format
 * "object_id" : {
 *      "component_id" : {
 *          "value_name" : "value",
 *          "value_2"    : "value"
 *      },
 *      "component_id_2" : {
 *          "something" : "asdf"
 *      }
 * },
 * "object_2" {
 *      "comp" : {
 *          ...
 *      }
 * },
 * ...
 * .
 * .
*/

#ifdef __unix__
    #include "../include/entt.hpp"
#elif defined _WIN32
    #include "entt.hpp"
#endif

#include "json.hpp"
#include "components.hpp"
#include "color.hpp"

// uh oh! this seems like a hacky and dumb solution that's probably not in the right file!!!!! (i don't care though)
enum class COMPONENTS {
    PHYSICS,
    TRANSFORM,
    RENDER,
    CONTROLLABLE,
    DECORATIVE,
    NAME,
    STATS
};

class EntityFactory {
    public:
        // constructors
        EntityFactory();
        ~EntityFactory();

        // add an entity to the registry based on json, returns if it succeeded.
        entt::entity add_object(std::string id, entt::registry &registry);

        bool load_objects(std::string filepath);

    private:
        Json json;

        std::map<std::string, COMPONENTS> component_id_map;

};

#endif
