

#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include "physics.h"
#include <raylib.h>

Player* player_create(float x, float y, float speed) {

    Player* player = malloc(sizeof(Player));
    if (player == NULL) {
        return NULL; //Handle exception
    }

    player->position.x = x;
    player->position.y = y;
    player->speed = speed;
    player->size = 28.0f;
    player->color = BLUE;

    return player;
}

void player_update(Player* player, const Map* map, float dt) {
    if (player == NULL){
        return; //Handle exception
    }

    Vector2 velocity = {0.0f, 0.0f};

    if (IsKeyDown(KEY_RIGHT)) {
        velocity.x += player->speed * dt;
    }
    if (IsKeyDown(KEY_LEFT)) {
        velocity.x -= player->speed * dt;
    }
    if (IsKeyDown(KEY_UP)) {
        velocity.y -= player->speed * dt;
    }
    if (IsKeyDown(KEY_DOWN)) {
        velocity.y += player->speed * dt;
    }

    Vector2 size = { player->size, player->size };
    player->position = physics_move_and_slide(player->position, size, velocity, map);

}

void player_render(const Player* player) {
    if (player == NULL) {
        return; //handle the fkng exception
    }
    
    DrawRectangleV(player->position, (Vector2){ player->size, player->size }, player->color);
    
}

void player_destroy(Player* player) {
    if (player == NULL) {
        return;
    }
    free(player);
}

