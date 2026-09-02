#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>
#include <stdbool.h>

typedef enum {ENTITY_NPC, ENTITY_MONSTER, ENTITY_CHEST} EntityType;

typedef enum {STATE_IDLE, STATE_WANDER, STATE_TALK} EntityState;

typedef struct {

    int id;
    EntityType type;
    Vector2 position;
    Vector2 size;
    Color color;
    int hp;
    bool active;
    EntityState state;
    float stateTimer;
    Vector2 moveDirection;
    float speed;
    char dialogueText[256];
    
}Entity;



Entity* entity_create(int id, EntityType type, Vector2 position, Color color);

void entity_render(const Entity* entity);

void entity_destroy(Entity* entity);



#endif //ENTITY_H