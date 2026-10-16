

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "player.h"
#include "physics.h"
#include "inventory.h"
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
    player->hp = 100;
    player->color = BLUE;
    player->inventory = inventory_create(10);
    player->direction = DIR_DOWN;
    player->isAttacking = false;
    player->attackTimer = 0.0f;
    player->attackDuration = 0.2f;
    player->state = IDLE;
    player->playertexture = LoadTexture("./assets/Sprites/mc.png");
    if (player->inventory == NULL) {
        free(player);
        return NULL;
    }

    return player;
}

void player_update(Player* player, const Map* map, float dt, int* current_map_ID) {
    if (player == NULL){
        return; //Handle exception
    }

    if (player->isAttacking) {
        
        player->attackTimer -= dt;
        if (player->attackTimer <= 0.0f) player->isAttacking = false;

    }
    
    if (IsKeyDown(KEY_SPACE) && !player->isAttacking) {
        player->isAttacking = true;
        player->attackTimer = player->attackDuration;
        
    }
    
    Vector2 size = { player->size, player->size };

    Vector2 velocity = {0.0f, 0.0f};

    bool isMoving = false;

    if (IsKeyDown(KEY_RIGHT)) {
        player->direction = DIR_RIGHT;
        velocity.x += player->speed * dt;
        isMoving = true;
    }
    if (IsKeyDown(KEY_LEFT)) {
        player->direction = DIR_LEFT;
        velocity.x -= player->speed * dt;
        isMoving = true;
    }
    if (IsKeyDown(KEY_UP)) {
        player->direction = DIR_UP;
        velocity.y -= player->speed * dt;
        isMoving = true;
    }
    if (IsKeyDown(KEY_DOWN)) {
        player->direction = DIR_DOWN;
        velocity.y += player->speed * dt;
        isMoving = true;
    }


    Player_State newState = IDLE;

    if (player->isAttacking) {
        newState = ATTACKING; 
    } 
    else if (isMoving) {
        newState = RUNNING;
    } 
    else {
        newState = IDLE;
    }

    
    if (newState != player->state) {
        player->state = newState;
        
    }

    
    player->position = physics_move_and_slide(player->position, size, velocity, map);

    Rectangle playerRect = { player->position.x, player->position.y, size.x, size.y };

    
    WarpData* activeWarp = physics_check_warp(playerRect, map);

    if (activeWarp != NULL) {

        if (activeWarp->target_map_id != *(current_map_ID)){

        player->position = activeWarp->spawn_position;

        *current_map_ID = activeWarp->target_map_id;
        return;
        }
        
        
    }

}

void player_render(const Player* player) {
    if (player == NULL) {
        return;
    }
    
    // 1. Dessiner le joueur

    

    Rectangle source_rec = { 0.0f, 0.0f, 16.0f, 16.0f };

    switch (player->direction) {

        case DIR_DOWN : source_rec.y = 64.0f;
        DrawTextureRec(player->playertexture, source_rec, player->position, WHITE);
        break;
        case DIR_UP : source_rec.y = 16.0f;
        DrawTextureRec(player->playertexture, source_rec, player->position, WHITE);
        break;
        case DIR_RIGHT : source_rec.y = 32.0f;
        DrawTextureRec(player->playertexture, source_rec, player->position, WHITE);
        break;
        case DIR_LEFT : source_rec.y = 49.0f;
        DrawTextureRec(player->playertexture, source_rec, player->position, WHITE);
        break;
    }
    
    

    
    const float bar_width = player->size-10;
    const float bar_height = 5.0f;
    Vector2 bar_pos = (Vector2){ player->position.x + 5.0f, player->position.y - 5.0f };

    // 2. Fond rouge
    DrawRectangleV(bar_pos, (Vector2){ bar_width, bar_height }, RED);

    // 3. Portion verte
    float hp_ratio = (float)player->hp / (float)100;

    // Sécurité pour éviter les valeurs négatives ou > 1.0f
    if (hp_ratio < 0.0f) hp_ratio = 0.0f;
    if (hp_ratio > 1.0f) hp_ratio = 1.0f;

    float green_size = hp_ratio * bar_width;
    DrawRectangleV(bar_pos, (Vector2){ green_size, bar_height }, LIME);
    
    
}


void player_destroy(Player* player) {
    if (player == NULL) {
        return;
    }
    inventory_destroy(player->inventory);
    UnloadTexture(player->playertexture);
    free(player);
}




SlashHitBox player_get_attack_box(const Player* player) {
    SlashHitBox hitbox = { 0 };

    switch (player->direction) {
        case DIR_RIGHT:
            hitbox.boxes[0] = (Rectangle){ player->position.x + 32, player->position.y - 10, 20, 50 };
            hitbox.boxes[1] = (Rectangle){ player->position.x + 52, player->position.y - 20, 25, 70 };
            hitbox.boxes[2] = (Rectangle){ player->position.x + 77, player->position.y - 5,  15, 40 };
            break;

        case DIR_LEFT:
            hitbox.boxes[0] = (Rectangle){ player->position.x - 20, player->position.y - 10, 20, 50 };
            hitbox.boxes[1] = (Rectangle){ player->position.x - 45, player->position.y - 20, 25, 70 };
            hitbox.boxes[2] = (Rectangle){ player->position.x - 60, player->position.y - 5,  15, 40 };
            break;

        case DIR_DOWN:
            hitbox.boxes[0] = (Rectangle){ player->position.x - 10, player->position.y + 32, 50, 20 };
            hitbox.boxes[1] = (Rectangle){ player->position.x - 20, player->position.y + 52, 70, 25 };
            hitbox.boxes[2] = (Rectangle){ player->position.x - 5,  player->position.y + 77, 40, 15 };
            break;

        case DIR_UP:
            hitbox.boxes[0] = (Rectangle){ player->position.x - 10, player->position.y - 20, 50, 20 };
            hitbox.boxes[1] = (Rectangle){ player->position.x - 20, player->position.y - 45, 70, 25 };
            hitbox.boxes[2] = (Rectangle){ player->position.x - 5,  player->position.y - 60, 40, 15 };
            break;
    }

    return hitbox;
}
