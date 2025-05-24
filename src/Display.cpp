#include "Display.h"
#include "Allincludes.h"
#include "Inventory.h"
#include <locale.h>
#include <ncurses.h>
#include <sstream>
#include <string>
using std::string;

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
    setlocale(LC_ALL, ""); // This enables unicode support
    curs_set(0); // This hides the cursor

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
void Display::drawInventory(WINDOW *invWin, Player player) {
    Inventory *playersInv = player.getPlayersInventory();
    int horiCount = 1;
    int vertCount = 1;

    for (auto index = playersInv->begin(); index != playersInv->end();
        index++) {

        string invEntry;
        std::stringstream formatter;
        formatter << index->first << ": " << index->second.second << " ";
        invEntry = formatter.str();

        int invWidth = (COLS - 2) * 0.75;
        // If too big for one line, new line in inventory
        if ((invWidth / (10 * (horiCount + 1))) < 1) {
            horiCount = 0;
            vertCount++;
        }
    
        wmove(invWin, vertCount, 2 + (10 * (horiCount - 1)));
        wprintw(invWin, "%s", invEntry.c_str());

        wrefresh(invWin);
        horiCount++;
    }
}
void Display::drawPlayer(WINDOW *gameWin, Player player) {
    int playerY = std::get<0>(player.getPosition());
    int playerX = std::get<1>(player.getPosition());

    wmove(gameWin, playerY, playerX);
    waddwstr(gameWin, L"☺"); // display player head


    WINDOW *compassWin;

    mvwprintw(gameWin, 1, ((COLS - 2) * 0.75) - 10, "Direction");

    int starty = (LINES * 0.15) + 3;
    int height = 3;

    int startx = ((COLS - 2) * 0.75) - 6;
    int width = 3;

    compassWin = create_newwin(height, width, starty, startx);
    wmove(compassWin, 1, 1);
    if (player.getDirection() == 0) {
        waddwstr(compassWin, L"↑"); 
    } else if (player.getDirection() == 1) {
        waddwstr(compassWin, L"→"); 
    } else if (player.getDirection() == 2) {
        waddwstr(compassWin, L"↓"); 
    } else if (player.getDirection() == 3) {
        waddwstr(compassWin, L"←"); 
    }
    wrefresh(gameWin);
    wrefresh(compassWin);

}
void Display::drawPlots(WINDOW *gameWin, vector<Plot> plots) {
    for (int i = 0; i < plots.size(); i++) {
        int starty = std::get<0>(plots[i].getTopLeftCoord());
        int startx = std::get<1>(plots[i].getTopLeftCoord());
        // TODO: Fix plots to make dimensions work properly!!!!
        // int width = plots[i].getDimensions()
        // WINDOW *plotWin = create_newwin(int height, int width, int starty, int startx)
    }
}

int main() {
    WINDOW *win = Display::drawMainWindow();
    WINDOW *invWin = Display::drawInventoryWindow(win);
    Display::drawDynamicWindow(win);
    Display::drawCommandWindow(win);
    WINDOW *gameWin = Display::drawGameWindow(win);

    Player testPlayer = Player();
    Inventory *inv = testPlayer.getPlayersInventory();

    Item* Carroty = new Item(2,1,"Carrot");
    Item* Potates = new Item(4,2,"Potato");
    inv->addItem(Carroty);
    inv->addItem(Potates);
    inv->addItem(Potates);
    Display::drawInventory(invWin, testPlayer);
    testPlayer.move(coord{4, 5});
    // testPlayer.setDirection(0);
    Display::drawPlayer(gameWin, testPlayer);
    getchar();
    endwin();
    return 0;
}
