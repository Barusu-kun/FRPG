#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"
#include "inventory.h"
#include <stdbool.h>
#include <raylib.h>

typedef struct {
    Vector2 position;
    float speed;
    float size;
    Color color;
    Inventory* inventory;
} Player;

Player* player_create(float x, float y, float speed);

void player_update(Player* player, const Map* map, float dt);

void player_render(const Player* player);

void player_destroy(Player* player);


#endif // PLAYER_H