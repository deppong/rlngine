#include "zone.hpp"

Zone::Zone(int width, int height):
    m_width(width),
    m_height(height)
{
}

void Zone::fill_zone_walls() {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            entt::entity e = m_registry.create();
            m_registry.emplace<TransformComponent>(e, x, y);
            m_registry.emplace<RenderComponent>(e, '#', COLOR_GRAY, COLOR_BLACK);
            // m_registry.emplace<NameComponent>(e, "wall", "walls", "A solid slab of stone.");
        }
    }
}

Zone::~Zone() {}
