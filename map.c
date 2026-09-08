#include "map.h"
#include "physics.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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

    if (map->tiles == NULL) {
        free(map); 
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        map->tiles[i] = malloc(cols * sizeof(Tile));

        if (map->tiles[i] == NULL) {
            Erreur_alloc = true;
            break;
        }

        
        for (int j = 0; j < cols; j++) {
            map->tiles[i][j].warp = NULL;
            map->tiles[i][j].isSolid = false;
            map->tiles[i][j].type = TILE_EMPTY;
        }
    }
    
    if (Erreur_alloc) {
        for (int i = 0; i < rows; i++) {
            if (map->tiles[i] != NULL) {
                free(map->tiles[i]);
            }
        }
        free(map->tiles);
        free(map);
        return NULL;
    }

    return map;
}

Map* map_import(const char* filepath) {
    TraceLog(LOG_INFO, "Début du chargement du fichier de map...");
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        TraceLog(LOG_ERROR, "Impossible d'ouvrir le fichier : %s", filepath);
        return NULL;
    }

    char line[1024]; 
    int cols = 0, rows = 0, tileSize = 0, tileX = 0, tileY = 0, targetMapID = 0, spawnX = 0, spawnY = 0;
    bool metadata_read = false;
    
    // 1. LECTURE DES DONNÉES DE CONFIGURATION
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "[END]", 5) == 0) {
            break; 
        }

        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') continue;

        if (sscanf(line, "%d,%d,%d", &cols, &rows, &tileSize) == 3) {
            metadata_read = true;
            break; 
        }
    }

    if (!metadata_read) {
        fclose(file);
        return NULL;
    }

    // 2. ALLOCATION DE LA MAP
    Map* map_to_import = map_create(cols, rows, tileSize);
    if (map_to_import == NULL) {
        fclose(file);
        return NULL;
    }
    
    TraceLog(LOG_INFO, "Grille de tuiles allouée, début de la lecture...");
    
    // 3. LECTURE DE LA GRILLE DE TUILES
    int current_row = 0;
    while (fgets(line, sizeof(line), file) != NULL && current_row < rows) {
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') continue;

        int current_col = 0;
        char* token = strtok(line, ",\n\r");

        while (token != NULL && current_col < cols) {
            int tile_type_val = atoi(token); 
            
            map_to_import->tiles[current_row][current_col].type = (TileType)tile_type_val;
            map_to_import->tiles[current_row][current_col].warp = NULL;

            if (tile_type_val == TILE_WALL) {
                map_to_import->tiles[current_row][current_col].isSolid = true;
            } else {
                map_to_import->tiles[current_row][current_col].isSolid = false;
            }

            current_col++;
            token = strtok(NULL, ",\n\r"); 
        }
        current_row++;
    }

    TraceLog(LOG_INFO, "Lecture de la grille terminée. Passage aux warps...");
    
    // 4. POINTS DE WARP
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "[END]", 5) == 0) {
            break; 
        }

        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') continue;

        if (sscanf(line, "%d,%d,%d,%d,%d", &tileX, &tileY, &targetMapID, &spawnX, &spawnY) == 5) {
            // Sécurité : On vérifie qu'on ne sort pas des indices du tableau
            if (tileY >= 0 && tileY < rows && tileX >= 0 && tileX < cols) {
                map_to_import->tiles[tileY][tileX].warp = malloc(sizeof(WarpData));
                if (map_to_import->tiles[tileY][tileX].warp != NULL) {
                    map_to_import->tiles[tileY][tileX].warp->player_direction = 1;
                    map_to_import->tiles[tileY][tileX].warp->target_map_id = targetMapID;
                    map_to_import->tiles[tileY][tileX].warp->spawn_position = (Vector2){(float)spawnX, (float)spawnY};
                }
            }
        }
    }

    TraceLog(LOG_INFO, "Chargement de la map terminé avec succès !");
    fclose(file);
    return map_to_import;
}

void map_render(const Map* map) {
    if (map == NULL) return;
    
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

void map_destroy(Map* map) {
    if (map == NULL || map->tiles == NULL) return;

    
    for (int y = 0; y < map->rows; y++) {
        if (map->tiles[y] != NULL) {
            for (int x = 0; x < map->cols; x++) {
                if (map->tiles[y][x].warp != NULL) {
                    free(map->tiles[y][x].warp); 
                    map->tiles[y][x].warp = NULL;
                }
            }
            free(map->tiles[y]);
        }
    }
    free(map->tiles); 
    free(map);       
}
