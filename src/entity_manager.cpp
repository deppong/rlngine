#include "entity_manager.hpp"

EntityManager::EntityManager():
    last_id(0)
{};

EntityManager::~EntityManager(){};

entity_t EntityManager::create() {
    entity_t entity = {last_id};
    entities[last_id] = entity;
    last_id++;
    return entity;
}