#include "entity_manager.h"
#include "entity.h"
#include "map.h"
#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

EntityManager* entity_manager_create(int initialCapacity) {

    EntityManager* entitymanager = malloc(sizeof(EntityManager));

    if(entitymanager == NULL) return NULL;

    entitymanager->entities = malloc(initialCapacity * sizeof(Entity*));

    for (int i = 0; i<initialCapacity; i++) {
        if (entitymanager->entities == NULL) {

            for (int j = 0; j<i; j++) {

                free(entitymanager->entities[j]);
            }
            break;
        }
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
    manager->count ++;
    return true;
}

void entity_manager_remove_at(EntityManager* manager, int index) {

    if (index<0 || index>=manager->count) return;

    entity_destroy(manager->entities[index]);

    manager->entities[index] = manager->entities[manager->count-1];
    manager->count --;

}

void entity_manager_update(EntityManager* manager, const Map* map, float dt) {

    if (manager == NULL || map == NULL) return;

    for (int i = 0; i<manager->count; i++)  {

        if (manager->entities[i]->active) {

            //IMPLEMENTATION IA COMPORTEMENT I GUESS :)

        }

    }
}

void entity_manager_render(const EntityManager* manager) {

    if (manager == NULL) return;

    for (int i = 0; i<manager->count; i++)  {

        if (manager->entities[i]->active) {

            entity_render(manager->entities[i]);

        }

    }

}

void entity_manager_destroy(EntityManager* manager) {

    for (int i = 0; i < manager->count; i++) {

        entity_destroy(manager->entities[i]);

    }
    free(manager->entities);
    free(manager);
}




