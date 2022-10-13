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
    for (int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            if (x+i >= m_width || y+j >= m_height || x+i <= 0 || y+j <= 0) continue;

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
