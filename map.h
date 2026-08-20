#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include <raylib.h>

typedef enum {
    TILE_GRASS, TILE_WALL, TILE_POT, TILE_DOOR, TILE_FURNITURE
} TileType;

typedef struct {
    TileType type;
    bool isSolid;
} Tile;

typedef struct Map {
    int cols;
    int rows;
    int tileSize;
    Tile** tiles;
}Map;

Map* map_create(int cols, int rows, int tileSize);

void map_render(const Map* map);

void map_destroy(Map* map);


#endif