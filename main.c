#include "game.h"
#include <stdio.h>

int main(void) {

    Game* game = game_create(1920, 1080, "My Game");
    if (game == NULL) {
        printf("Failed to create game\n");
        return 1;
    }

    while (game->isRunning) {
        game->dt = GetFrameTime();
        game->FrameCount = GetTime();
        game_update(game);
        game_render(game);
    }

    game_destroy(game);
    return 0;
}