

#include <stdlib.h>
#include <stdio.h>
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
    player->color = BLUE;
    player->inventory = inventory_create(10);
    player->direction = DIR_DOWN;
    player->isAttacking = false;
    player->attackTimer = 0.0f;
    player->attackDuration = 0.2f;
    if (player->inventory == NULL) {
        free(player);
        return NULL;
    }

    return player;
}

void player_update(Player* player, const Map* map, float dt) {
    if (player == NULL){
        return; //Handle exception
    }

    if (player->isAttacking) {
        
        player->attackTimer -= dt;
        if (player->attackTimer <= 0.0f) player->isAttacking = false;

    }
    
    if (IsKeyPressed(KEY_SPACE) && !player->isAttacking) {
        player->isAttacking = true;
        player->attackTimer = player->attackDuration;
        
    }
    Vector2 velocity = {0.0f, 0.0f};

    if (IsKeyDown(KEY_RIGHT)) {
        player->direction = DIR_RIGHT;
        velocity.x += player->speed * dt;
    }
    if (IsKeyDown(KEY_LEFT)) {
        player->direction = DIR_LEFT;
        velocity.x -= player->speed * dt;
    }
    if (IsKeyDown(KEY_UP)) {
        player->direction = DIR_UP;
        velocity.y -= player->speed * dt;
    }
    if (IsKeyDown(KEY_DOWN)) {
        player->direction = DIR_DOWN;
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
    inventory_destroy(player->inventory);
    free(player);
}

//inutile mais joli a voir pour le playtest

void DrawAttaqueTrigo(AttaqueTrigo *att) {
    // 1. Calcul de la progression (de 0.0 à 1.0)
    if (att->frameCount > att->maxFrames) att->frameCount = att->maxFrames;
    float progression = (float)att->frameCount / (float)att->maxFrames;

    // 2. Détermination de l'angle de départ selon la direction (Angles Raylib)
    float angleDepart = 0.0f;
    switch (att->direction) {
        case DIR_RIGHT: angleDepart = 0.0f;   break; // Droite
        case DIR_DOWN:  angleDepart = 90.0f;  break; // Bas
        case DIR_LEFT:  angleDepart = 180.0f; break; // Gauche
        case DIR_UP:    angleDepart = 270.0f; break; // Haut
    }

    // 3. Calcul de l'angle final
    // On part de l'angle de direction, et on soustrait pour aller en sens anti-horaire
    float angleDegres = angleDepart - (progression * 180.0f); 

    // 4. Définition du rectangle de base
    Rectangle rect = { att->pivot.x, att->pivot.y, att->longueur, att->largeur };

    // 5. Définition du point pivot LOCAL
    Vector2 origineLocale = { 0.0f, att->largeur / 2.0f };

    // 6. Dessin avec rotation
    DrawRectanglePro(rect, origineLocale, angleDegres, YELLOW);
}

//fin du truc inutile


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
