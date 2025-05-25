#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>

#include <vector>

#include "Player.h"
#include "Plot.h"

class Display {
 public:
  // Declare draw functions
  static WINDOW *drawMainWindow();
  static WINDOW *drawInventoryWindow(WINDOW *mainWin);
  static WINDOW *drawDynamicWindow(WINDOW *mainWin);
  static WINDOW *drawCommandWindow(WINDOW *mainWin);
  static WINDOW *drawGameWindow(WINDOW *mainWin);
  static WINDOW *drawErrorWindow(WINDOW *mainWin);
  static void drawDays(WINDOW *mainWin, int days);
  static void drawInventory(WINDOW *invWin, Player player);
  static void drawPlayer(WINDOW *gameWin, Player player);
  static void drawFarmPlots(WINDOW *gameWin, vector<FarmPlot> plots);
  static void drawCommands(WINDOW *comWin);
};

#endif
