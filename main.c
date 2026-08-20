#include "game.h"
#include <stdio.h>

int main(void) {

    Game* game = game_create(800, 450, "My Game");
    if (game == NULL) {
        printf("Failed to create game\n");
        return 1;
    }

    while (game->isRunning) {
        game_update(game);
        game_render(game);
    }

    game_destroy(game);
    return 0;
}