#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include <vector>
#include "Player.h"
#include "Plot.h"

class Display {
    public:
        static WINDOW *drawMainWindow();
        static WINDOW *drawInventoryWindow(WINDOW *mainWin);
        static WINDOW *drawDynamicWindow(WINDOW *mainWin);
        static WINDOW *drawCommandWindow(WINDOW *mainWin);
        static WINDOW *drawGameWindow(WINDOW *mainWin);
        static void drawInventory(WINDOW *invWin, Player player);
        static void drawPlayer(WINDOW *gameWin, Player player);
        static void drawPlots(WINDOW *gameWin, vector<Plot> plots);

};

#endif
