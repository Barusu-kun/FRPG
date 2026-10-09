#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include <stdio.h>
#include <raylib.h>

typedef enum {
    TILE_GRASS, TILE_WALL, TILE_COLLECTIBLE, TILE_LAVA, TILE_WARP, TILE_FURNITURE, TILE_EMPTY
} TileType;

typedef struct {

    int target_map_id;
    Vector2 spawn_position;
    int player_direction;
} WarpData;

typedef struct {
    TileType type;
    bool isSolid;
    WarpData* warp;
} Tile;


typedef struct Map {
    int cols;
    int rows;
    int tileSize;
    Tile** tiles;
}Map;

Map* map_create(int cols, int rows, int tileSize);

Map* map_import(const char* filepath);

void map_render(const Map* map);

void map_destroy(Map* map);


#endif