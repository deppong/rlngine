#include "world.hpp"

World::World(int width, int height, int tile_width):
    world_w(width/tile_width),
    world_h(height/tile_width),
    new_turn(false),
    current_zone(4),
    factory()
{
    for (int i = 0; i < zones.size(); i++) {
        zones[i].m_width = world_w;
        zones[i].m_height = world_h;
    }

    factory.load_objects("../../objects/objects.json");
    std::cout << "loaded objects" << std::endl;
};

World::~World() {};

void World::copyEntity(entt::entity dst, entt::entity source, entt::registry &curr, entt::registry &dest) {
    for (auto [id, storage] : curr.storage()) {
        auto it = dest.storage(id);
        if (it != dest.storage().end() && storage.contains(source)) {
            it->second.emplace(dst, storage.get(source));
            std::cout << "emplaced " << id << std::endl;
        }
    }
    std::cout << "done" << std::endl;
}

void World::update_physics() {

    zones[current_zone].update_physics();

    // get player
    auto view = zones[current_zone].m_registry.view<ControllableComponent>();
    entt::entity player;
    for (auto entity : view) {
        auto controllable = view.get<ControllableComponent>(entity);
        if (controllable.inControl) {
            player = entity;
            break;
        }
    }

    // did the player exit the current zone?
    auto &p_transform = zones[current_zone].m_registry.get<TransformComponent>(player);

    if (p_transform.x < 0) {
        p_transform.x = world_w - 1;

        auto player_copy = factory.add_object("player", zones[current_zone-1].m_registry);

        copyEntity(player_copy, player, zones[current_zone].m_registry, zones[current_zone-1].m_registry);
 
        zones[current_zone].m_registry.destroy(player);
        current_zone--;
        std::cout << "Exited west" << std::endl;
    } else if (p_transform.y < 0) {
        p_transform.y = world_h - 1;

        auto player_copy = factory.add_object("player", zones[current_zone-3].m_registry);

        copyEntity(player_copy, player, zones[current_zone].m_registry, zones[current_zone-3].m_registry);

        zones[current_zone].m_registry.destroy(player);
        current_zone-=3;
        std::cout << "Exited north" << std::endl;

    } else if (p_transform.x > zones[current_zone].m_width - 1) {
        p_transform.x = 0;

        auto player_copy = factory.add_object("player", zones[current_zone+1].m_registry);

        copyEntity(player_copy, player, zones[current_zone].m_registry, zones[current_zone+1].m_registry);
 
        zones[current_zone].m_registry.destroy(player);
        current_zone++;
        std::cout << "Exited east" << std::endl;

    } else if (p_transform.y > zones[current_zone].m_height - 1) {
        p_transform.y = 0;

        auto player_copy = factory.add_object("player", zones[current_zone+3].m_registry);

        copyEntity(player_copy, player, zones[current_zone].m_registry, zones[current_zone+3].m_registry);

        zones[current_zone].m_registry.destroy(player);
        current_zone+=3;
        std::cout << "Exited south" << std::endl;
    }

    std::cout << "current_zone: " << current_zone << std::endl;

}

void World::construct_zone(int zone_index) {
    int zone_h = zones[zone_index].m_height;
    int zone_w = zones[zone_index].m_width;

    std::mt19937 gen(zone_index);
    std::uniform_int_distribution<> distr(0, 100);

    // TODO: This entire function should really be local to the zone once proper
    // world gen is actually done. This could be mocked up pretty soon!
    for (int y = 0; y < zone_h; y++) {
        for (int x = 0; x < zone_w; x++) {
            entt::entity entity;

            int n = distr(gen);
            if (n > 0 && n <= 25) {
                entity = factory.add_object("stone_wall", zones[zone_index].m_registry);
            } else if (n > 25 && n <= 40) {
                entity = factory.add_object("dirt_wall", zones[zone_index].m_registry);
            } else {
                entity = entt::null;
            }

            // switch(distr(gen)) {
            //     case 0: entity = factory.add_object("stone_wall", zones[zone_index].m_registry); break;
            //     case 1: entity = factory.add_object("dirt_wall", zones[zone_index].m_registry); break;
            //     case 2: entity = entt::null; break;
            // }

            if (entity != entt::null) {
                auto &transform = zones[zone_index].m_registry.get<TransformComponent>(entity);
                transform.x = x;
                transform.y = y;
            }
        }
    }

    zones[zone_index].make_room(10, 10, 20, 20);
}
