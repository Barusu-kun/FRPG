#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"
#include "inventory.h"
#include <stdbool.h>
#include <raylib.h>


typedef enum Direction {
    DIR_DOWN,
    DIR_UP,
    DIR_LEFT,
    DIR_RIGHT
} Direction;


typedef struct {
    Vector2 position;
    float speed;
    float size;
    Color color;
    Inventory* inventory;
    Direction direction;
    bool isAttacking;
    float attackTimer;
    float attackDuration;
} Player;

typedef struct {

    Rectangle boxes[3];
} SlashHitBox;

//inutile mais joli a voir pour le playtest

typedef struct {
    Vector2 pivot;       // Le point central (ex: la position du joueur)
    float longueur;      // La longueur du rectangle (qui pointe vers l'extérieur)
    float largeur;       // L'épaisseur du rectangle
    int frameCount;      // Frame actuelle
    int maxFrames;       // Durée de la rotation en frames
    Direction direction; // AJOUT : La direction initiale lors du déclenchement
} AttaqueTrigo;

//fin des trucs inutiles

Player* player_create(float x, float y, float speed);

void player_update(Player* player, const Map* map, float dt);

void player_render(const Player* player);

void player_destroy(Player* player);

void DrawAttaqueTrigo(AttaqueTrigo *att);

SlashHitBox player_get_attack_box(const Player* player);



#endif // PLAYER_H