#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include "Player.h"

class Display {
    public:
        static WINDOW *drawMainWindow();
        static WINDOW *drawInventoryWindow(WINDOW *mainWin);
        static WINDOW *drawDynamicWindow(WINDOW *mainWin);
        static WINDOW *drawCommandWindow(WINDOW *mainWin);
        static WINDOW *drawGameWindow(WINDOW *mainWin);
        static void drawInventory(WINDOW *invWin, Player *player);

};

#endif
