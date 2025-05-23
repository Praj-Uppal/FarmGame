#include "Display.h"
#include <ncurses.h>

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
    // wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void Display::drawGameWindow() {
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
}
/*
int main() {
    Display::drawGameWindow();
    getchar();
    endwin();
    return 0;
}
*/