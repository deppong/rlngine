#ifndef COMP_MAN_HPP
#define COMP_MAN_HPP

#include "entity_manager.hpp"
#include <string>
#include <any>

struct component_t {
    std::map<std::string, std::any> data;
};

class ComponentManager {
    public:
        ComponentManager();
        ~ComponentManager();

        // get a specific component
        std::map<int, component_t> get_component_list(std::string name);
        void add_component(entity_t entity, std::string component_name, component_t component);
        void destroy(entity_t entity);
    private:
        // map of all component lists
        std::map<std::string, std::map<int, component_t>> components;
    
};

#endif