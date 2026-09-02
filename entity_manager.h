#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "entity.h"
#include "map.h"
#include "player.h"
#include <raylib.h>
#include <stdbool.h>

typedef struct EntityManager {
    Entity** entities;
    int count;
    int capacity;
} EntityManager;

EntityManager* entity_manager_create(int initialCapacity);

bool entity_manager_add(EntityManager* manager, Entity* entity);

void entity_manager_remove_at(EntityManager* manager, int index);

void entity_manager_update(EntityManager* manager, const Map* map, float dt);

void entity_manager_render(const EntityManager* manager);

void entity_manager_destroy(EntityManager* manager);

void entity_manager_check_attack(EntityManager* manager, SlashHitBox attackBox, int damage);

Entity* entity_manager_get_nearest_npc(EntityManager* manager, Vector2 playerPosition, float interactRadius);



#endif //ENTITY_MANAGER_H