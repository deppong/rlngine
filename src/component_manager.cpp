#include "component_manager.hpp"

ComponentManager::ComponentManager() {};

ComponentManager::~ComponentManager(){};

void ComponentManager::add_component(entity_t entity, std::string component_name, component_t component) {
    components[component_name].insert(std::make_pair(entity.id, component));
}

std::map<int, component_t> ComponentManager::get_component_list(std::string name) {
    auto search = components.find(name);
    if (search == components.end()) {
        std::cerr << "component not found: " << name << std::endl;
    }
    return search->second;

}

void ComponentManager::destroy(entity_t entity) {
    for(auto i : components) {
        i.first.find(entity.id);
    }
}
