

#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include <raylib.h>

Player* player_create(float x, float y, float speed) {

    Player* player = malloc(sizeof(Player));
    if (player == NULL) {
        return NULL; //Handle exception
    }

    player->position.x = x;
    player->position.y = y;
    player->speed = speed;
    player->size = 30.0f;
    player->color = BLUE;

    return player;
}

void player_update(Player* player) {
    if (player == NULL){
        return; //Handle exception
    }
    if (IsKeyDown(KEY_RIGHT)) {
        player->position.x += player->speed;
    }
    if (IsKeyDown(KEY_LEFT)) {
        player->position.x -= player->speed;
    }
    if (IsKeyDown(KEY_UP)) {
        player->position.y -= player->speed;
    }
    if (IsKeyDown(KEY_DOWN)) {
        player->position.y += player->speed;
    }
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

