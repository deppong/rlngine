#include "world.hpp"

World::World(int width, int height, int tile_width):
    world_w(width/tile_width),
    world_h(height/tile_width),
    new_turn(false),
    world_coords(0, 0),
    current_zone(4),
    factory()
{
    for (int i = 0; i < zones.size(); i++) {
        zones[i].m_width = world_w;
        zones[i].m_height = world_h;
    }

    factory.load_objects("../../objects/objects.json");
    std::cout << "loaded objects" << std::endl;

    construct_zone(0, 0);
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

Zone& World::get_zone(int x, int y) {
    return *zone_map.at(x + y * MAX_WORLD_WIDTH);
}

entt::registry& World::current_registry() {
    return get_zone(world_coords.x, world_coords.y).m_registry;
}

bool World::zone_exists(int x, int y) {
    if (zone_map.find(x + y*MAX_WORLD_WIDTH) != zone_map.end()) {
        return true;
    } 
    return false;
}

entt::entity World::get_player() {
    auto view = current_registry().view<ControllableComponent>();
    entt::entity player;
    for (auto entity : view) {
        auto controllable = view.get<ControllableComponent>(entity);
        if (controllable.inControl) {
            player = entity;
            break;
        }
    }
    return player;
}

void World::update_physics() {

    get_zone(world_coords.x, world_coords.y).update_physics();

    // get player
    entt::entity player = get_player();

    // ideally this would be for every single entity in that has a transform that changed
    // look into entt::observer

    // did the player exit the current zone?
    auto &p_transform = current_registry().get<TransformComponent>(player);

    if (p_transform.x < 0) {
        p_transform.x = world_w - 1;

        construct_zone(world_coords.x - 1, world_coords.y);

        auto player_copy = factory.add_object("player", get_zone(world_coords.x - 1, world_coords.y).m_registry);

        copyEntity(player_copy, player, current_registry(), get_zone(world_coords.x - 1, world_coords.y).m_registry);

        current_registry().destroy(player);

        world_coords.x += -1;
        world_coords.y +=  0;
        std::cout << "Changed to the southern zone" << std::endl;
    } else if (p_transform.y < 0) {
        p_transform.y = world_h - 1;

        construct_zone(world_coords.x, world_coords.y - 1);

        auto player_copy = factory.add_object("player", get_zone(world_coords.x, world_coords.y - 1).m_registry);

        copyEntity(player_copy, player, current_registry(), get_zone(world_coords.x, world_coords.y - 1).m_registry);

        current_registry().destroy(player);

        world_coords.x +=  0;
        world_coords.y += -1;
        std::cout << "Changed to the northern zone" << std::endl;

    } else if (p_transform.x > get_zone(world_coords.x, world_coords.y).m_width - 1) {
        p_transform.x = 0;

        construct_zone(world_coords.x + 1, world_coords.y);

        auto player_copy = factory.add_object("player", get_zone(world_coords.x + 1, world_coords.y).m_registry);

        copyEntity(player_copy, player, current_registry(), get_zone(world_coords.x + 1, world_coords.y).m_registry);

        current_registry().destroy(player);

        world_coords.x +=  1;
        world_coords.y +=  0;
        std::cout << "Changed to the eastern zone" << std::endl;

    } else if (p_transform.y > get_zone(world_coords.x, world_coords.y).m_height - 1) {
        p_transform.y = 0;

        construct_zone(world_coords.x, world_coords.y + 1);

        auto player_copy = factory.add_object("player", get_zone(world_coords.x, world_coords.y + 1).m_registry);

        copyEntity(player_copy, player, current_registry(), get_zone(world_coords.x, world_coords.y + 1).m_registry);

        current_registry().destroy(player);

        world_coords.x +=  0;
        world_coords.y +=  1;
        std::cout << "Changed to the southern zone" << std::endl;
    }

    std::cout << "current_zone: " << world_coords.x << "," << world_coords.y << std::endl;

}

void World::construct_zone(int world_x, int world_y) {
    if (zone_exists(world_x, world_y)) {
        return;
    }
    zone_map.emplace(world_x + world_y * MAX_WORLD_WIDTH, new Zone(world_w, world_h));

    std::cout << "added zone" << std::endl;

    std::mt19937 gen((world_x ^ world_y) << 4);
    std::uniform_int_distribution<> distr(0, 100);

    // TODO: This entire function should really be local to the zone once proper
    // world gen is actually done. This could be mocked up pretty soon!
    for (int y = 0; y < world_h; y++) {
        for (int x = 0; x < world_w; x++) {
            entt::entity entity;

            int n = distr(gen);
            if (n > 0 && n <= 25) {
                entity = factory.add_object("stone_wall", get_zone(world_x, world_y).m_registry);
            } else if (n > 25 && n <= 40) {
                entity = factory.add_object("dirt_wall", get_zone(world_x, world_y).m_registry);
            } else {
                entity = entt::null;
            }

            // switch(distr(gen)) {
            //     case 0: entity = factory.add_object("stone_wall", zones[zone_index].m_registry); break;
            //     case 1: entity = factory.add_object("dirt_wall", zones[zone_index].m_registry); break;
            //     case 2: entity = entt::null; break;
            // }

            if (entity != entt::null) {
                auto &transform = get_zone(world_x, world_y).m_registry.get<TransformComponent>(entity);
                transform.x = x;
                transform.y = y;
            }
        }
    }

    get_zone(world_x, world_y).make_room(10, 10, 20, 20);
}
