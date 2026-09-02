#include "entity_manager.h"
#include "entity.h"
#include "map.h"
#include "player.h"
#include "physics.h"
#include <raylib.h>
#include <raymath.h>
#include <float.h>   
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

EntityManager* entity_manager_create(int initialCapacity) {
    EntityManager* entitymanager = malloc(sizeof(EntityManager));
    if (entitymanager == NULL) return NULL;

    entitymanager->entities = malloc(initialCapacity * sizeof(Entity*));
    if (entitymanager->entities == NULL) { 
        free(entitymanager);
        return NULL;
    }

    entitymanager->count = 0;
    entitymanager->capacity = initialCapacity;

    return entitymanager;
}

bool entity_manager_add(EntityManager* manager, Entity* entity) {
    if (manager == NULL || entity == NULL) return false;

    if (manager->count >= manager->capacity) {
        int newCapacity = manager->capacity * 2;
        Entity** newArray = realloc(manager->entities, newCapacity * sizeof(Entity*));

        if (newArray == NULL) return false;

        manager->entities = newArray;
        manager->capacity = newCapacity;
    }
    manager->entities[manager->count] = entity;
    manager->count++;
    return true;
}

void entity_manager_remove_at(EntityManager* manager, int index) {
    if (index < 0 || index >= manager->count) return;

    entity_destroy(manager->entities[index]);

    manager->entities[index] = manager->entities[manager->count - 1];
    manager->count--;
}

void entity_manager_update(EntityManager* manager, const Map* map, float dt) {
    if (manager == NULL || map == NULL) return;

    for (int i = 0; i < manager->count; i++)  {
        if (manager->entities[i]->active) {
            switch (manager->entities[i]->type) {
                case ENTITY_NPC: 
                    switch (manager->entities[i]->state) {
                        case STATE_TALK: 
                            break;

                        case STATE_IDLE: 
                            manager->entities[i]->stateTimer -= dt;
                            if (manager->entities[i]->stateTimer <= 0.0f) {
                                manager->entities[i]->state = STATE_WANDER;
                                float max_shift = 0.5f; 
                                float rand_x = ((float)rand() / (float)RAND_MAX) * (max_shift * 2.0f) - max_shift;
                                float rand_y = ((float)rand() / (float)RAND_MAX) * (max_shift * 2.0f) - max_shift;
                                Vector2 random_dir = {rand_x, rand_y};
                                manager->entities[i]->moveDirection = random_dir;
                                manager->entities[i]->stateTimer = 1.0f + (float)(rand() % 200) / 100.0f;
                            }
                            break;

                        case STATE_WANDER:
                            manager->entities[i]->stateTimer -= dt;
                            Vector2 vel = Vector2Scale(manager->entities[i]->moveDirection, manager->entities[i]->speed * dt);
                            physics_move_and_slide(manager->entities[i]->moveDirection, manager->entities[i]->size, vel, map);

                            if (manager->entities[i]->stateTimer <= 0.0f) {
                                manager->entities[i]->state = STATE_IDLE;
                                manager->entities[i]->stateTimer = (float)(rand() % 3 + 1); 
                            }
                            break;
                        default:
                            break;
                    }
                    break; 
                default:
                    break;
            }
        }
    }
}

void entity_manager_render(const EntityManager* manager) {
    if (manager == NULL) return;

    for (int i = 0; i < manager->count; i++)  {
        if (manager->entities[i]->active) {
            entity_render(manager->entities[i]);
        }
    }
}

void entity_manager_destroy(EntityManager* manager) {
    if (manager == NULL) return;
    
    for (int i = 0; i < manager->count; i++) {
        entity_destroy(manager->entities[i]);
    }
    free(manager->entities);
    free(manager);
}

void entity_manager_check_attack(EntityManager* manager, SlashHitBox attackBox, int damage) {
    if (manager == NULL) return;

    for (int i = 0; i < manager->count; i++) {
        // On vérifie que l'entité est un monstre actif
        if (manager->entities[i]->active && manager->entities[i]->type == ENTITY_MONSTER) {
            Rectangle entityBox = { 
                manager->entities[i]->position.x, 
                manager->entities[i]->position.y, 
                manager->entities[i]->size.x, 
                manager->entities[i]->size.y 
            };
            
            bool isHit = false;   // convention C : minuscule au début
int j = 0;

// Parcourt les 3 boîtes de collision de l'attaque
        while (j < 3) {
            if (CheckCollisionRecs(attackBox.boxes[j], entityBox)) {
                isHit = true;
                break; // inutile de tester les 2 autres boîtes une fois touché
            }
            j++;
        }

        if (isHit) {
            manager->entities[i]->hp -= damage;
            if (manager->entities[i]->hp <= 0) {
                manager->entities[i]->active = false;
            }
        }
        }
    }
}


Entity* entity_manager_get_nearest_npc(EntityManager* manager, Vector2 playerPosition, float interactRadius) {
    if (manager == NULL) return NULL;
    float min_distance = FLT_MAX;
    int min_index = -1;
    
    for (int i = 0; i < manager->count; i++) {
        if (manager->entities[i]->active && manager->entities[i]->type == ENTITY_NPC) {
            float distance_act = Vector2DistanceSqr(playerPosition, manager->entities[i]->position);

            if (distance_act < min_distance) {
                min_distance = distance_act;
                min_index = i;
            }
        }
    }
    
    if (min_index >= 0 && min_distance <= (interactRadius * interactRadius)) {
        return manager->entities[min_index];
    }

    return NULL;
}
