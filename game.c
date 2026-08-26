#include "game.h"
#include "player.h"
#include "map.h"
#include "inventory.h"
#include "item.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>

Game* game_create(int width, int height, const char* title) {
    
    Game* game = malloc(sizeof(Game));
    if (game == NULL) {
        return NULL; // Memory allocation failed
    }
    game->largeur_ecran = width;
    game->hauteur_ecran = height;
    game->titre_fenetre = title;
    game->isRunning = true;
    game->dt = 0;

    InitWindow(width, height, title);
    SetTargetFPS(60);
    game->player = player_create(400.0, 225.0, 200.0f);
    

    
    game->map = map_create(25,14,32);

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

    return game;
}

void game_update(Game* game) {
    if (game == NULL) {
        return; // Handle null pointer
    }

    player_update(game->player, game->map, game->dt);
    entity_manager_update(game->entities, game->map, game->dt);

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
    DrawText("Hello, World!", 10, 10, 20, DARKGRAY);
    map_render(game->map);
    entity_manager_render(game->entities);
    inventory_render_debug(game->player->inventory, 10, 50);
    player_render(game->player);

    EndDrawing();
    
}

void game_destroy(Game* game) {
    if (game == NULL) {
        return; // Handle null pointer
    }
    entity_manager_destroy(game->entities);
    player_destroy(game->player);
    map_destroy(game->map);
    CloseWindow();
    free(game);
}
