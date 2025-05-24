#include "GameManager.h"



int main() {
    GameManager game;
    game.initializeGame();
    game.gameLoop();
    // game.cleanup();
    return 0;
}
