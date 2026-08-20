#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>

Map* map_create(int cols, int rows, int tileSize) {
    bool Erreur_alloc = false;
    Map* map = malloc(sizeof(Map));

    if (map == NULL) {
        return NULL;
    }
    map->cols = cols;
    map->rows = rows;
    map->tileSize = tileSize;
    
    // ALLOCATION MEMOIRE DU GRID MAP
    map->tiles = malloc(rows * sizeof(Tile*));

    if(map->tiles == NULL) {
        free(map); 
        return NULL;
    }

    for (int i = 0; i < rows; i++){
        map->tiles[i] = malloc(cols * sizeof(Tile));

        if(map->tiles[i] == NULL) {
            Erreur_alloc = true;
        }
    }
    
    if (Erreur_alloc) {
        for (int i = 0; i < rows; i++){
            if (map->tiles[i] != NULL) {
                free(map->tiles[i]);
            }
        }
        free(map->tiles);
        free(map);
        return NULL;
    }

    // INITIALISATION TERRAIN
    
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if(x == 0 || x == cols - 1 || y == 0 || y == rows - 1) {
                map->tiles[y][x] = (Tile){TILE_WALL, true};
            }
            else{
                map->tiles[y][x] = (Tile){TILE_GRASS, false};
            }
        }
    }
    return map;
}

void map_render(const Map* map) {
    if (map == NULL){
        return;
    }
    
    Color color;
   
    for (int y = 0; y < map->rows; y++) {
        for (int x = 0; x < map->cols; x++) {
            int posX = x * map->tileSize;
            int posY = y * map->tileSize;
            
            
            if (map->tiles[y][x].type == TILE_GRASS) {
                color = GREEN;
            }
            else if (map->tiles[y][x].type == TILE_WALL) {
                color = GRAY;
            }
            else {
                color = PINK;
            }
            DrawRectangle(posX, posY, map->tileSize, map->tileSize, color);
        }
    }
}

void map_destroy(Map* map){
    if (map == NULL){
        return;
    }

    
    for (int y = 0; y < map->rows; y++) {
        if (map->tiles[y] != NULL) {
            free(map->tiles[y]);
        }
    }
    free(map->tiles);
    free(map);
}
