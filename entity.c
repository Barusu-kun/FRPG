#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "player.h"
#include "physics.h"
#include "inventory.h"
#include "entity.h"
#include <raylib.h>


Entity* entity_create(int id, EntityType type, Vector2 position, Color color) {


    Entity* entity = malloc(sizeof(Entity));

    if (entity == NULL) return NULL;

    entity->id = id;
    entity->type = type;
    entity->position = position;
    entity->color = color;
    entity->hp = 100;
    entity->timeout = 0.0f;
    entity->size.x = 28.0f;
    entity->size.y = 28.0f;
    entity->active = true;
    entity->state = STATE_IDLE;
    entity->stateTimer = 2.0f;
    entity->speed = 50.0f;
    entity->moveDirection.x = 0.0f;
    entity->moveDirection.y = 0.0f;
    snprintf(entity->dialogueText, sizeof(entity->dialogueText), "%s", "Placeholder text for Diaogue :) @#~123456/*- `èéù ");

    return entity;

}

void entity_render(const Entity* entity) {

    if (entity == NULL || !entity->active) return;

    DrawRectangleV(entity->position, entity->size, entity->color);

}

void entity_destroy(Entity* entity) {

    if (entity == NULL) return;

    free(entity);
}

SlashHitBox entity_get_hitbox(const Entity* entity) {
    SlashHitBox hitbox = { 0 };

    hitbox.boxes[0] = (Rectangle){ entity->position.x- entity->size.x, entity->position.y - entity->size.y, entity->size.x * 3.0f, entity->size.y * 3.0f };
    hitbox.boxes[1] = (Rectangle){ entity->position.x, entity->position.y, entity->size.x , entity->size.y };
    hitbox.boxes[2] = (Rectangle){ 0.0f,0.0f,0.0f,0.0f};

    

    return hitbox;
}
