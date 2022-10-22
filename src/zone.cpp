#include "zone.hpp"

Zone::Zone():
    m_width(0),
    m_height(0)
{}

Zone::Zone(int width, int height):
    m_width(width),
    m_height(height)
{
}

void Zone::make_room(int x, int y, int w, int h) {
    for (int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if (x+i > m_width || y+j > m_height || x+i < 0 || y+j < 0) continue;

            auto view = m_registry.view<TransformComponent, DecorativeComponent>();
            for (auto entity : view) {
                auto &transform = view.get<TransformComponent>(entity);
                if (transform.x == x+i && transform.y == y+j) {
                    m_registry.destroy(entity);
                }
            }
        }
    }
}

bool Zone::is_walkable(int x, int y) {
    bool walkable = true;
    auto view = m_registry.view<TransformComponent, PhysicsComponent>();
    for (auto entity : view) {
        auto [transform, physics] = view.get<TransformComponent, PhysicsComponent>(entity);
        if (transform.x == x && transform.y == y && physics.solid) {
            walkable = false;
            break;
        }
    }

    return walkable;
}

void Zone::update_physics() {
    auto phys_group = m_registry.group<>(entt::get<TransformComponent, PhysicsComponent>);
    for (auto entity : phys_group) {
        auto &[transform, physics] = phys_group.get<TransformComponent, PhysicsComponent>(entity);

        // are we even gonna move?
        if (physics.vel_x != 0 || physics.vel_y != 0) {
            int desired_x = transform.x + physics.vel_x;
            int desired_y = transform.y + physics.vel_y;

            // this is naive because if there is a tile in the way 
            // of the desired path then we are just gonna blink over it.
            // what will have to happen next is likely a djikstra map
            // of the zones, and then set the target for each object to 
            // their desired x and y coords, likely with some AI component
            if (is_walkable(desired_x, desired_y)) {
                transform.x = desired_x;
                transform.y = desired_y;
            }

            physics.vel_x = 0;
            physics.vel_y = 0;
        }
    }
}

Zone::~Zone() {}
