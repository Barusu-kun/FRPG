#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"
#include "inventory.h"
#include <stdbool.h>
#include <raylib.h>


typedef enum Direction {
    DIR_DOWN,
    DIR_UP,
    DIR_LEFT,
    DIR_RIGHT
} Direction;


typedef struct {
    Vector2 position;
    float speed;
    float size;
    Color color;
    Inventory* inventory;
    Direction direction;
    bool isAttacking;
    float attackTimer;
    float attackDuration;
} Player;

typedef struct {

    Rectangle boxes[3];
} SlashHitBox;

Player* player_create(float x, float y, float speed);

void player_update(Player* player, const Map* map, float dt);

void player_render(const Player* player);

void player_destroy(Player* player);

SlashHitBox player_get_attack_box(const Player* player);



#endif // PLAYER_H