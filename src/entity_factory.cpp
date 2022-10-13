#include "entity_factory.hpp"

EntityFactory::EntityFactory() {
    component_id_map["transform"]       = COMPONENTS::TRANSFORM;
    component_id_map["physics"]         = COMPONENTS::PHYSICS;
    component_id_map["render"]          = COMPONENTS::RENDER;
    component_id_map["name"]            = COMPONENTS::NAME;
    component_id_map["stats"]           = COMPONENTS::STATS;
    component_id_map["controllable"]    = COMPONENTS::CONTROLLABLE;
    component_id_map["decorative"]      = COMPONENTS::DECORATIVE;
};
EntityFactory::~EntityFactory() {};

bool EntityFactory::add_object(std::string &id, entt::registry &registry) {
    if (json.objects.count(id) == 0) {
        std::cerr << "object \"" << id <<  "\" not found, maybe not loaded?" << std::endl;
        return false;
    }

    entt::entity entity = registry.create();

    for (const auto& [component_id, component_data] : json.objects[id]) {
        if (component_id_map.count(component_id) == 0 ) {
            std::cerr << "component \"" << id <<  "\" not found" << std::endl;
            registry.destroy(entity);
            return false;
        }

        
        // surely this won't be error prone or hard to debug!
        switch(component_id_map[component_id]) {
            case COMPONENTS::TRANSFORM: 
                registry.emplace<TransformComponent>(entity, std::stoi(component_data.at("x")), std::stoi(component_data.at("y")));
            break;

            case COMPONENTS::PHYSICS:
                registry.emplace<PhysicsComponent>(entity, std::stoi(component_data.at("vel_x")), std::stoi(component_data.at("vel_y")));
            break;

            case COMPONENTS::RENDER: 
                registry.emplace<RenderComponent>(entity, std::stoi(component_data.at("tile")), std::stoi(component_data.at("color")), std::stoi(component_data.at("bg_color")));
            break;

            case COMPONENTS::NAME:
                registry.emplace<NameComponent>(entity, component_data.at("name"), component_data.at("name_plr"), component_data.at("description"));
            break;

            case COMPONENTS::STATS: 
                registry.emplace<RenderComponent>(entity, std::stoi(component_data.at("STR")), std::stoi(component_data.at("CON")), std::stoi(component_data.at("DEX")));
            break;

            case COMPONENTS::CONTROLLABLE: 
                registry.emplace<ControllableComponent>(entity, std::stoi(component_data.at("in_control")));
            break;

            case COMPONENTS::DECORATIVE: 
                registry.emplace<DecorativeComponent>(entity);
            break;

            default: break;
        }
    }

    return true;
}