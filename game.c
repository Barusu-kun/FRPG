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
    Item placeholder = {1,"Basement key", ITEM_KEY, 0};
    inventory_add_item(game->player->inventory, placeholder);
    return game;
}

void game_update(Game* game) {
    if (game == NULL) {
        return; // Handle null pointer
    }

    player_update(game->player, game->map, game->dt);

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
    inventory_render_debug(game->player->inventory, 10, 50);
    player_render(game->player);

    EndDrawing();
    
}

void game_destroy(Game* game) {
    if (game == NULL) {
        return; // Handle null pointer
    }
    player_destroy(game->player);
    map_destroy(game->map);
    CloseWindow();
    free(game);
}
