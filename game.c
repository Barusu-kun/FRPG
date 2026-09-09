#include "game.h"
#include "player.h"
#include "map.h"
#include "inventory.h"
#include "item.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <raylib.h>

Game* game_create(int width, int height, const char* title) {
    
    Game* game = malloc(sizeof(Game));
    if (game == NULL) {
        return NULL;
    }
    game->largeur_ecran = width;
    game->hauteur_ecran = height;
    game->titre_fenetre = title;
    game->isRunning = true;
    game->dt = 0;
    game->FrameCount = 0;
    game->current_map_ID = malloc(sizeof(int));
    if (game->current_map_ID != NULL) {
        *game->current_map_ID = 1;
    }
    

    InitWindow(width, height, title);
    SetTargetFPS(60);
    game->player = player_create(400.0, 225.0, 200.0f);
    
    
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "assets/map/%i.csv", *(game->current_map_ID));
    game->map = map_import(filepath);


    game->camera.target = game->player->position;
    game->camera.offset = (Vector2){ (float)width / 2.0f, (float)height / 2.0f};
    game->camera.rotation = 0.0f;
    game->camera.zoom = 2.0f;

    if ( game->player == NULL || game->map == NULL) {
        
        game_destroy(game);
        return NULL;
    }

    //Item attribution
    Item placeholder = {1,"Basement key", ITEM_KEY, 0};
    Item placeholder2 = {2,"House key", ITEM_KEY, 0};
    Item placeholder3 = {3,"Ylenia", ITEM_KEY, 0};
    Item placeholder4 = {4,"Garage key", ITEM_KEY, 0};

    inventory_add_item(game->player->inventory, placeholder);
    inventory_add_item(game->player->inventory, placeholder2);
    inventory_add_item(game->player->inventory, placeholder3);
    inventory_add_item(game->player->inventory, placeholder4);

    //Entity attribution
    EntityManager* manager = entity_manager_create(5);
    Vector2 pos_mob1 = {138.0f, 80.0f};
    Vector2 pos_mob2 = {170.0f, 80.0f};
    Vector2 pos_mob3 = {400.0f, 80.0f};

    Entity* goblin = entity_create(1, ENTITY_MONSTER, pos_mob1, RED);
    Entity* orc = entity_create(2, ENTITY_MONSTER, pos_mob2, RED);
    Entity* adam = entity_create(3, ENTITY_NPC, pos_mob3, YELLOW);

    entity_manager_add(manager, goblin);
    entity_manager_add(manager, orc);
    entity_manager_add(manager, adam);

    game->entities = manager;

    game->dialogue = dialogue_create();

    return game;
}

void game_update(Game* game) {
    if (game == NULL) return;

    int map_id_before = *(game->current_map_ID);
   
    Entity* current_npc = entity_manager_get_nearest_npc(game->entities, game->player->position, 45.0f);
    if (IsKeyPressed(KEY_F) && !(current_npc == NULL) && !game->dialogue->isActive) {
        current_npc->state = STATE_TALK;
        dialogue_open(game->dialogue, "NoName", current_npc->dialogueText);
    }
    else if (IsKeyPressed(KEY_F) && !(current_npc == NULL) && game->dialogue->isActive) {
        current_npc->state = STATE_IDLE;
        dialogue_close(game->dialogue);
    }

    if (!game->dialogue->isActive) {
        // Met à jour le joueur (c'est ici que current_map_ID peut changer)
        player_update(game->player, game->map, game->dt, game->current_map_ID);

        // SI LA MAP A CHANGÉ PENDANT LA FRAME :
        if (*(game->current_map_ID) != map_id_before) {
            
            TraceLog(LOG_INFO, "[TRACK TP] Detection active ! Position joueur avant changement de fichier : Pixels(%.1f, %.1f)", game->player->position.x, game->player->position.y);
            // 1. DÉCHARGER MAP 
            if (game->map != NULL) {
                map_destroy(game->map);
            }

            // 2. CHARGER LA NOUVELLE MAP
            char filepath[256];
            snprintf(filepath, sizeof(filepath), "assets/map/%i.csv", *(game->current_map_ID));
            game->map = map_import(filepath);
            TraceLog(LOG_INFO, "[TRACK TP] Fichier charge. Nouvelle position (donnee par le fichier) : Pixels(%.1f, %.1f)", game->player->position.x, game->player->position.y);

            // 3. Décaler le joueur de 4-5 pixels 
            TraceLog(LOG_INFO, "[TRACK TP] Direction actuelle du joueur : %d", game->player->direction);
            
            if (game->player->direction == DIR_RIGHT) game->player->position.x += 8.0f;
            if (game->player->direction == DIR_LEFT)  game->player->position.x -= 8.0f;
            if (game->player->direction == DIR_UP)    game->player->position.y -= 8.0f;
            if (game->player->direction == DIR_DOWN)  game->player->position.y += 8.0f;

            TraceLog(LOG_INFO, "[TRACK TP] Position finale apres securite anti-boucle : Pixels(%.1f, %.1f) -> Tuile(Col:%d, Row:%d)", 
                     game->player->position.x, game->player->position.y,
                     (int)floor(game->player->position.x / game->map->tileSize),
                     (int)floor(game->player->position.y / game->map->tileSize));

            TraceLog(LOG_INFO, "[GAME] Changement de carte effectue proprement vers : %s", filepath);
        }
    }

    entity_manager_update(game->entities, game->map, game->dt, game->player);
    if (game->player->attackTimer == game->player->attackDuration) {
        player_get_attack_box(game->player);
        entity_manager_check_attack(game->entities, player_get_attack_box(game->player), 10);
    }

    float decaySpeed = 5.0f;
    float t = 1.0f - expf(-decaySpeed * game->dt);

    game->camera.target.x += (game->player->position.x - game->camera.target.x) * t;
    game->camera.target.y += (game->player->position.y - game->camera.target.y) * t;

    if (WindowShouldClose()) {
        game->isRunning = false;
    }
}


void game_render(const Game* game) {
    if (game == NULL) {
        return; // Handle null pointer
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(game->camera);

    map_render(game->map);
    entity_manager_render(game->entities);
    player_render(game->player);
    
    EndMode2D();

    inventory_render_debug(game->player->inventory, 10, 50);
    dialogue_render(game->dialogue, 1920,1080);
    DrawText(TextFormat("%i", game->FrameCount), 1050, 0, 10, DARKGRAY);

    EndDrawing();
    
}

void game_destroy(Game* game) {
    if (game == NULL) {
        return; // Handle null pointer
    }

    free(game->current_map_ID);
    entity_manager_destroy(game->entities);
    player_destroy(game->player);
    map_destroy(game->map);
    dialogue_destroy(game->dialogue);
    CloseWindow();
    free(game);
}
