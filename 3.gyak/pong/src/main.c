#include "game.h"

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    Game game;

    init_game(&game, 1000, 800);
    while (game.is_running) {
        handle_game_events(&game);
        update_game(&game);
        render_game(&game);
    }
    destroy_game(&game);

    return 0;
}
