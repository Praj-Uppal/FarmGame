#include "Display.h"
#include "Allincludes.h"
#include "Inventory.h"
#include <ncurses.h>
#include <strings.h>

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	
    WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);
	return local_win;
}

WINDOW *Display::drawMainWindow() {
    WINDOW *borderWin;
    // Init ncurses
    initscr(); // This starts curses mode
    cbreak(); // Catch all keyboard input
    keypad(stdscr, TRUE); // Allows use of arrow keys
    noecho(); // Do not echo user input to terminal

    int starty = 0;
    int startx = 0;

    int height = LINES;
    int width = COLS;
    borderWin = create_newwin(height, width, starty, startx);
    wrefresh(borderWin);
    if (COLS < 111 || LINES < 43) {
        WINDOW *errorWin;
        int height = 8;
        int width = 22;
        int starty = (LINES - height) / 2;
        int startx = (COLS - width) / 2;

        errorWin = create_newwin(height, width, starty, startx);
        mvwprintw(errorWin, 1, 1, "Your Terminal is too");
        mvwprintw(errorWin, 2, 1, "small to display the");
        mvwprintw(errorWin, 3, 9, "game.");
        mvwprintw(errorWin, 4, 2, "Please expand your ");
        mvwprintw(errorWin, 5, 1, "terminal to at least");
        mvwprintw(errorWin, 6, 1, "111 cols and 43 rows");

        wrefresh(errorWin);
    }
    return borderWin;
}
WINDOW *Display::drawInventoryWindow(WINDOW *mainWin) {
    WINDOW *inventoryWin;
    int starty = (LINES * 0.85);
    int height = (LINES * 0.15);

    int startx = 1;
    int width = (COLS - 2) * 0.75;
    inventoryWin = create_newwin(height, width, starty, startx);
    mvwprintw(inventoryWin, 0, 1, "Inventory");
    wrefresh(inventoryWin);
    return inventoryWin;
}

WINDOW *Display::drawDynamicWindow(WINDOW *mainWin) {
    WINDOW *dynamicWindow;

    int starty = 1;
    int height = (LINES - 2);

    int startx = (COLS * 0.75);
    int width = (COLS * 0.25) - 1;

    dynamicWindow = create_newwin(height, width, starty, startx);
    wrefresh(dynamicWindow);
    return dynamicWindow;
}

WINDOW *Display::drawCommandWindow(WINDOW *mainWin) {
    WINDOW *commandWindow;

    int starty = 1;
    int height = (LINES * 0.15);

    int startx = 1;
    int width = (COLS - 2) * 0.75;
    commandWindow = create_newwin(height, width, starty, startx);
    mvwprintw(commandWindow, 0, 1, "Commands");
    wrefresh(commandWindow);
    return commandWindow;
}
WINDOW *Display::drawGameWindow(WINDOW *mainwin) {
    WINDOW *gameWindow;

    int starty = (LINES * 0.15) + 1;
    int height = LINES - (LINES * 0.30) - 1;

    int startx = 1;
    int width = (COLS - 2) * 0.75;

    gameWindow = create_newwin(height, width, starty, startx);
    mvwprintw(gameWindow, 0, 1, "Game");
    wrefresh(gameWindow);
    return gameWindow;
}
void Display::drawInventory(WINDOW *invWin, Player *player) {
    // Inventory *playersInv = player->getPlayersInventory();
  // for (auto index = playersInv.begin(); index != playersInv.end();
       // index++) {
    // Prints the values stored at the memory address index is pointing to.
    // Since the second entry in itself is a pair, the data needs to be printed
    // by accessing first element (second.first) and then second element
    // (second.second)
      // mvwprintw(invWin, 1, 1, "Hello");
  // }

}
int main() {
    WINDOW *win = Display::drawMainWindow();
    WINDOW *invWin = Display::drawInventoryWindow(win);
    Display::drawDynamicWindow(win);
    Display::drawCommandWindow(win);
    Display::drawGameWindow(win);
    Player testPlayer = Player();
    Inventory *inv = testPlayer.getPlayersInventory();
    inv->addItem(Carrotitem);
    // Display::drawInventory(invWin, testPlayer);
    getchar();
    endwin();
    return 0;
}
