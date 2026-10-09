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

void entity_manager_update(EntityManager* manager, const Map* map, float dt, Player* player) {
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

                            Vector2 vel = Vector2Scale(
                                manager->entities[i]->moveDirection,
                                manager->entities[i]->speed * dt
                            );

                            manager->entities[i]->position = physics_move_and_slide(
                                manager->entities[i]->position,
                                manager->entities[i]->size,
                                vel,
                                map
                            );

                            if (manager->entities[i]->stateTimer <= 0.0f) {
                                manager->entities[i]->state = STATE_IDLE;
                                manager->entities[i]->stateTimer = (float)(rand() % 3 + 1);
                            }
                            break;

                        default:
                            break;
                    }
                    break; 
                case ENTITY_MONSTER:
                    
                    switch (manager->entities[i]->state) {

                        case STATE_TALK: 
                                break;

                        case STATE_IDLE: 
                        if (manager->entities[i]->timeout >0.0f) manager->entities[i]->timeout -= dt;
                            TraceLog(LOG_INFO, "Entered state_idle mob : %i", i);
                            TraceLog(LOG_INFO, "%f mob %i", Vector2DistanceSqr(manager->entities[i]->position, player->position), i);
                            manager->entities[i]->stateTimer -= dt;
                            if (manager->entities[i]->stateTimer <= 0.0f) {
                                manager->entities[i]->state = STATE_WANDER;
                                TraceLog(LOG_INFO, "state from idle to wander");
                                float max_shift = 0.5f; 
                                float rand_x = ((float)rand() / (float)RAND_MAX) * (max_shift * 2.0f) - max_shift;
                                float rand_y = ((float)rand() / (float)RAND_MAX) * (max_shift * 2.0f) - max_shift;
                                Vector2 random_dir = {rand_x, rand_y};
                                manager->entities[i]->moveDirection = random_dir;
                                manager->entities[i]->stateTimer = 1.0f + (float)(rand() % 200) / 100.0f;
                            }
                            break;

                        case STATE_WANDER:
                        if (manager->entities[i]->timeout >0.0f) manager->entities[i]->timeout -= dt;
                        TraceLog(LOG_INFO, "%f mob %i", Vector2DistanceSqr(manager->entities[i]->position, player->position), i);
                        TraceLog(LOG_INFO, "Entered state_wander mob %i", i);    
                        if (Vector2DistanceSqr(manager->entities[i]->position, player->position) <= 40000.0) {
                            manager->entities[i]->state = STATE_TARGET;

                            TraceLog(LOG_INFO, "state from wander to target");
                            break;
                        }
                            
                            manager->entities[i]->stateTimer -= dt;

                            Vector2 vel = Vector2Scale(
                                manager->entities[i]->moveDirection,
                                manager->entities[i]->speed * dt
                            );

                            manager->entities[i]->position = physics_move_and_slide(
                                manager->entities[i]->position,
                                manager->entities[i]->size,
                                vel,
                                map
                            );

                            if (manager->entities[i]->stateTimer <= 0.0f) {
                                manager->entities[i]->state = STATE_IDLE;
                                TraceLog(LOG_INFO, "state from wander to idle");
                                manager->entities[i]->stateTimer = (float)(rand() % 3 + 1);
                            }
                            break;

                        case STATE_TARGET:
                                if (manager->entities[i]->timeout >0.0f) manager->entities[i]->timeout -= dt;
                                TraceLog(LOG_INFO, "%f", Vector2DistanceSqr(manager->entities[i]->position, player->position));
                                TraceLog(LOG_INFO, "inside state_target");
                                Vector2 monster2player = (Vector2){player->position.x - manager->entities[i]->position.x, player->position.y - manager->entities[i]->position.y};
                                manager->entities[i]->moveDirection = Vector2Normalize(monster2player);
                                Vector2 velo = Vector2Scale(manager->entities[i]->moveDirection,manager->entities[i]->speed * dt);
                                manager->entities[i]->position = physics_move_and_slide(manager->entities[i]->position, manager->entities[i]->size, velo, map);

                            if (Vector2DistanceSqr(manager->entities[i]->position, player->position)>= 40000.0) {
                            manager->entities[i]->state = STATE_IDLE;
                            TraceLog(LOG_INFO, "state from target to idle");
                            }
                            else if (Vector2DistanceSqr(manager->entities[i]->position, player->position) <= 5000.0) {

                                manager->entities[i]->state = STATE_ATTACK;
                            }
                        break;

                        case STATE_ATTACK:
                        ;
                        Rectangle player_hitbox = (Rectangle){player->position.x, player->position.y, player->size, player->size};

                        if (manager->entities[i]->timeout <= 0.0f && CheckCollisionRecs(entity_get_hitbox(manager->entities[i]).boxes[0], player_hitbox)) {

                            player->hp -= 10;

                        }

                        manager->entities[i]->timeout = 10.0f;
                        manager->entities[i]->state = STATE_IDLE;

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
        
        if (manager->entities[i]->active && manager->entities[i]->type == ENTITY_MONSTER) {
            Rectangle entityBox = { 
                manager->entities[i]->position.x, 
                manager->entities[i]->position.y, 
                manager->entities[i]->size.x, 
                manager->entities[i]->size.y 
            };
            
            bool isHit = false;
            int j = 0;

            while (j < 3) {
                if (CheckCollisionRecs(attackBox.boxes[j], entityBox)) {
                    isHit = true;
                    break; 
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
