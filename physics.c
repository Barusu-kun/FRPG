#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>
#include <math.h>
#include "map.h"


bool physics_check_collision(Rectangle rect, const Map* map) {

    if (map == NULL || map->tiles == NULL) {
        return false;
    }

    int minCol = floor(rect.x/map->tileSize);
    int maxCol = floor((rect.x + rect.width -1 )/map->tileSize);
    int minRow = floor(rect.y/map->tileSize);
    int maxRow = floor((rect.y + rect.height -1 )/map->tileSize);

    for (int r = minRow; r<= maxRow; r++) {
        for (int c = minCol; c<= maxCol; c++) {

            if (c < 0 || c >= map->cols || r<0 || r>= map->rows) {
                return true;
            }
            else if (map->tiles[r][c].isSolid) {
                return true;
            }
            
        }
    }
    return false;

}

Vector2 physics_move_and_slide(Vector2 position, Vector2 size, Vector2 velocity, const Map* map) {

    Vector2 newPos = position;

    Rectangle rectX;
    rectX.x = newPos.x + velocity.x;
    rectX.y = newPos.y;
    rectX.width = size.x;
    rectX.height = size.y;

    if (!physics_check_collision(rectX, map)) {
        newPos.x += velocity.x;
    }

    Rectangle rectY;
    rectY.y = newPos.y + velocity.y;
    rectY.x = newPos.x;
    rectY.width = size.x;
    rectY.height = size.y;

    if (!physics_check_collision(rectY, map)) {
        newPos.y += velocity.y;
    }
    
    return newPos;
}
