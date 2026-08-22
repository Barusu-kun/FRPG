#ifndef PHYSICS_H
#define PHYSICS_H


#include <stdbool.h>
#include <raylib.h>
#include "map.h"



bool physics_check_collision(Rectangle rect, const Map* map);

Vector2 physics_move_and_slide(Vector2 position, Vector2 size, Vector2 velocity, const Map* map);









#endif //PYHYSICS_H