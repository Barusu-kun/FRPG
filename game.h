#ifndef GAME_H
#define GAME_H


#include <stdbool.h>
#include "player.h"
#include "map.h"
#include "entity_manager.h"
#include "entity.h"


typedef struct {
    int largeur_ecran;
    int hauteur_ecran;
    const char* titre_fenetre;
    bool isRunning;
    float dt;
    Player* player;
    Map* map;
    EntityManager* entities;
    

} Game;

Game* game_create(int width, int height, const char* title);

void game_update(Game* game);

void game_render(const Game* game);

void game_destroy(Game* game);

#endif //GAME_H