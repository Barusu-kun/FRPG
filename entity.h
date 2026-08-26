#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>
#include <stdbool.h>

typedef enum {ENTITY_NPC, ENTITY_MONSTER, ENTITY_CHEST} EntityType;

typedef struct {

    int id;
    EntityType type;
    Vector2 position;
    Vector2 size;
    Color color;
    int hp;
    bool active;

}Entity;

Entity* entity_create(int id, EntityType type, Vector2 position, Color color);

void entity_render(const Entity* entity);

void entity_destroy(Entity* entity);



#endif //ENTITY_H