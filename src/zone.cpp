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

void Zone::fill_zone_walls(std::vector<uint32_t> &tex) {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            entt::entity e = m_registry.create();
            m_registry.emplace<TransformComponent>(e, x, y);
            m_registry.emplace<RenderComponent>(e, tex, COLOR_GRAY, COLOR_BLACK);
            m_registry.emplace<DecorativeComponent>(e);
            // m_registry.emplace<NameComponent>(e, "wall", "walls", "A solid slab of stone.");
        }
    }
}

void Zone::update_physics() {
    auto phys_group = m_registry.group<>(entt::get<TransformComponent, PhysicsComponent>);
    for (auto entity : phys_group) {
        auto [transform, physics] = phys_group.get<TransformComponent, PhysicsComponent>(entity);

        transform.x += physics.vel_x;
        transform.y += physics.vel_y;

        physics.vel_x = 0;
        physics.vel_y = 0;
    }
}

Zone::~Zone() {}
