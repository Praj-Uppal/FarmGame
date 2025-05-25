#include "Display.h"

#include <locale.h>
#include <ncurses.h>

#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "Allincludes.h"
#include "CarrotPlant.h"
#include "FarmPlot.h"
#include "Inventory.h"
#include "Plant.h"
using std::string;

// General Function to create a new window
WINDOW *create_newwin(int height, int width, int starty, int startx) {
  // Create a window ptr
  WINDOW *local_win;
  // Create a new window and assign to ptr
  local_win = newwin(height, width, starty, startx);
  // Draw border around the window edge
  box(local_win, 0, 0);
  return local_win;
}

// Function to draw the main window
WINDOW *Display::drawMainWindow() {
  // Create a new window ptr
  WINDOW *borderWin;

  // Define starting points to be top left corner
  int starty = 0;
  int startx = 0;

  // Define height and width based on terminal size
  int height = LINES;
  int width = COLS;
  // Create the window using the function defined above and assign to ptr
  borderWin = create_newwin(height, width, starty, startx);
  wrefresh(borderWin);
  // If the terminal is too small, display an error message
  if (COLS < 111 || LINES < 43) {
    // Create a new window for the error message
    WINDOW *errorWin;
    int height = 8;
    int width = 22;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;
    errorWin = create_newwin(height, width, starty, startx);

    // Display the error message
    mvwprintw(errorWin, 1, 1, "Your Terminal is too");
    mvwprintw(errorWin, 2, 1, "small to display the");
    mvwprintw(errorWin, 3, 9, "game.");
    mvwprintw(errorWin, 4, 2, "Please expand your ");
    mvwprintw(errorWin, 5, 1, "terminal to at least");
    mvwprintw(errorWin, 6, 1, "111 cols and 43 rows");

    // Refresh the window to display changes
    wrefresh(errorWin);
  }
  return borderWin;
}
// Function to draw the inventory window
WINDOW *Display::drawInventoryWindow(WINDOW *mainWin) {
  // Create a new window ptr
  WINDOW *inventoryWin;
  // Define starting point to be at the bottom of terminal (so it starts at 15%
  // above bottom and then extends down 15% of terminal to reach bottom)
  int starty = (LINES * 0.85);
  int height = (LINES * 0.15);

  // Define width to be 75% of terminal width with some space and begin near
  // left side of terminal
  int startx = 1;
  int width = (COLS - 2) * 0.75;
  // Create the window using the function defined above and assign to ptr
  inventoryWin = create_newwin(height, width, starty, startx);
  // Label the window
  mvwprintw(inventoryWin, 0, 1, "Inventory");
  // Refresh Screen
  wrefresh(inventoryWin);
  return inventoryWin;
}

WINDOW *Display::drawDynamicWindow(WINDOW *mainWin) {
  // Create a new window ptr
  WINDOW *dynamicWindow;
  // Define y starting point to be near top, and height to be half of the entire
  // terminal height with some space
  int starty = 1;
  int height = (LINES / 2 - 1);
  // Define width to be 25% of terminal width from the right side with some
  // space
  int startx = (COLS * 0.75);
  int width = (COLS * 0.25) - 1;

  // Create the window using the function defined above and assign to ptr
  dynamicWindow = create_newwin(height, width, starty, startx);
  // refresh screen
  wrefresh(dynamicWindow);
  return dynamicWindow;
}

WINDOW *Display::drawErrorWindow(WINDOW *mainWin) {
  // Create a new window ptr
  WINDOW *errorWindow;
  // Define y starting point near the middle, and height to be half of the
  // entire terminal height with some space
  int starty = LINES / 2;
  int height = (LINES / 2 - 1);
  // Define width to be 25% of terminal width from the right side with some
  // space
  int startx = (COLS * 0.75);
  int width = (COLS * 0.25) - 1;

  // Create the window using the function defined above and assign to ptr
  errorWindow = create_newwin(height, width, starty, startx);
  //Label
  mvwprintw(errorWindow, 0, 1, "Error Messages");
  // refresh screen
  wrefresh(errorWindow);
  return errorWindow;
}

WINDOW *Display::drawCommandWindow(WINDOW *mainWin) {
  // Create a new window ptr
  WINDOW *commandWindow;

  // Define y starting point to be at the top of terminal and then extend 15%
  // down, much like inventory window
  int starty = 1;
  int height = (LINES * 0.15);

  // Define width to be 70% of terminal width with some space and start from
  // left
  int startx = 1;
  int width = (COLS - 2) * 0.70;
  // Create the new window and assign to ptr
  commandWindow = create_newwin(height, width, starty, startx);
  // Label Window
  mvwprintw(commandWindow, 0, 1, "Commands");
  // refresh window
  wrefresh(commandWindow);
  return commandWindow;
}
void Display::drawDays(WINDOW *mainWin, int days) {
  // Create a new window ptr
  WINDOW *daysWindow;

  // Define y starting point to be at top, and height to be 15% of terminal
  int starty = 1;
  int height = (LINES * 0.15);

  // Define the x starting point to be around 70% of terminal to left and then
  // extend 5% to right
  //(so it starts at 70% of terminal and then extends 5% to right until 75%)
  int startx = (COLS - 2) * 0.70 + 1;
  int width = (COLS - 2) * 0.05;
  // Create the new window and assign to ptr
  daysWindow = create_newwin(height, width, starty, startx);
  // Label window
  mvwprintw(daysWindow, 0, 1, "Days");
  // Add data to it
  mvwprintw(daysWindow, 2, 1, "%d", days);
  // refresh
  wrefresh(daysWindow);
}

// Function to put data in the command window
void Display::drawCommands(WINDOW *comWin) {
  // Starts near top
  int startY = 1;
  // Insert Labels with spaces in between!
  mvwprintw(comWin, startY, 4, "Controls:");
  wprintw(comWin, "    ");
  wprintw(comWin, "WASD/Arrows: Move");
  wprintw(comWin, "    ");
  wprintw(comWin, "E/Space: Water plant");
  wprintw(comWin, "    ");
  wprintw(comWin, "P: Plant menu");
  wmove(comWin, startY + 1, 4);
  wprintw(comWin, "H: Harvest");
  wprintw(comWin, "    ");
  wprintw(comWin, "O: Open shop");
  wprintw(comWin, "    ");
  wprintw(comWin, "N: Next day");
  wprintw(comWin, "    ");
  wprintw(comWin, "Q: Quit");
  wprintw(comWin, "    ");
  wmove(comWin, startY + 2, 4);
  wprintw(comWin, "Esc: Close Dynamic window");
  wrefresh(comWin);
}
// Function to draw the main game window
WINDOW *Display::drawGameWindow(WINDOW *mainwin) {
  // Create a new window ptr
  WINDOW *gameWindow;

  // Define starting y point to be 15% below top and height to be 70% with some
  // space
  int starty = (LINES * 0.15) + 1;
  int height = LINES - (LINES * 0.30) - 1;

  // Define starting x point to be close to left and then almost extend 75% of
  // terminal
  int startx = 1;
  int width = (COLS - 2) * 0.75;

  // Create the game window and assign to ptr
  gameWindow = create_newwin(height, width, starty, startx);
  mvwprintw(gameWindow, 0, 1, "Game");  // Label window
  // Refresh
  wrefresh(gameWindow);
  return gameWindow;
}
// Function to draw the inventory
void Display::drawInventory(WINDOW *invWin, Player player) {
  // Get inventory ptr
  Inventory *playersInv = player.getPlayersInventory();
  int horiCount = 1;
  int vertCount = 1;

  // Display money
  mvwprintw(invWin, 0, (COLS - 2) * 0.75 - 15, "Money: $%d", player.getMoney());
  // Iterate over inventory and display items
  for (auto index = playersInv->begin(); index != playersInv->end(); index++) {
    string invEntry;
    std::stringstream formatter;
    formatter << index->first << ": " << (index->second.second - 1)
              << " ";  // Display the name of the item and the number of items
                       // in the inventory
    invEntry = formatter.str();
    // Get width of inventory window
    int invWidth = (COLS - 2) * 0.75;
    // If too big for one line, new line in inventory
    if ((invWidth / (11 * (horiCount + 1))) < 1) {
      horiCount = 0;
      vertCount++;
    }
    // Move to correct position and print inventory entry
    wmove(invWin, vertCount, 2 + (11 * (horiCount - 1)));
    wprintw(invWin, "%s", invEntry.c_str());

    // Refresh window to display change
    wrefresh(invWin);
    horiCount++;
  }
}
// Function to draw the player
void Display::drawPlayer(WINDOW *gameWin, Player player) {
  // Get player coordinates
  int playerY = std::get<0>(player.getPosition());
  int playerX = std::get<1>(player.getPosition());
  // Get Previous player coordinates
  int prevPlayerY = std::get<0>(player.getPrevPosition());
  int prevPlayerX = std::get<1>(player.getPrevPosition());

  // Delete old player char since its moving
  if (prevPlayerX != 0 && prevPlayerY != 0) {
    wmove(gameWin, prevPlayerY, prevPlayerX);
    waddch(gameWin, ' ');
  }
  // Move to player position and display player
  wmove(gameWin, playerY, playerX);
  waddwstr(gameWin, L"☺");  // display player head

  // Create a window for the player's direction
  WINDOW *compassWin;

  // Label the direction window
  mvwprintw(gameWin, 1, ((COLS - 2) * 0.75) - 10, "Direction");

  // Define starting point, and height, and width of direction window
  int starty = (LINES * 0.15) + 3;
  int height = 3;

  int startx = ((COLS - 2) * 0.75) - 6;
  int width = 3;

  // Create the compass window to display direction and assign to ptr
  compassWin = create_newwin(height, width, starty, startx);
  wmove(compassWin, 1, 1);

  // Based on player input display the direction the player is facing
  if (player.getDirection() == Player::MoveDirection::North) {
    waddwstr(compassWin, L"↑");
  } else if (player.getDirection() == Player::MoveDirection::East) {
    waddwstr(compassWin, L"→");
  } else if (player.getDirection() == Player::MoveDirection::South) {
    waddwstr(compassWin, L"↓");
  } else if (player.getDirection() == Player::MoveDirection::West) {
    waddwstr(compassWin, L"←");
  }
  // Refresh windows
  wrefresh(gameWin);
  wrefresh(compassWin);
}

void Display::drawFarmPlots(WINDOW *gameWin, vector<FarmPlot> plots) {
  // Iterate over plots and draw them
  for (int i = 0; i < plots.size(); i++) {
    // Get Plot coordinates
    int starty = (std::get<0>(plots[i].getTopLeftCoord()) + (LINES * 0.15) + 2);
    int startx = (std::get<1>(plots[i].getTopLeftCoord()) + 2);
    // Get Plot dimensions
    int height = std::get<0>(plots[i].getDimensions());
    int width = std::get<1>(plots[i].getDimensions());
    // Get plants in plot
    vector<Plant *> plants = plots[i].getPlants();
    // Create specific Plot window
    WINDOW *plotWin = create_newwin(height, width, starty, startx);
    // Iterate over plants in plot and draw them
    for (int j = 0; j < plants.size(); j++) {
      // If plant is watered, display it in Blue
      if (plants[j]->isWatered()) {
        wattron(plotWin, COLOR_PAIR(1));
      }
      // Move to plant position and display it
      wmove(plotWin, (std::get<0>(plants[j]->getPosistion()) + 1),
            (std::get<1>(plants[j]->getPosistion())) + 1);

      // Display plant based on plant type, and its growth stage
      if (plants[j]->getName() == "CarrotPlant") {
        switch (plants[j]->getGrowthStage()) {
          case 0:
          case 1:
            waddwstr(plotWin, L"▢");
            break;
          case 2:
            waddwstr(plotWin, L"▨");
            break;
          case 3:
          default:
            waddwstr(plotWin, L"▩");
            break;
        }
      } else if (plants[j]->getName() == "PotatoPlant") {
        switch (plants[j]->getGrowthStage()) {
          case 0:
          case 1:
            waddwstr(plotWin, L"○");
            break;
          case 2:
            waddwstr(plotWin, L"◑");
            break;
          case 3:
          default:
            waddwstr(plotWin, L"●");
            break;
        }
      }
      wattroff(plotWin, COLOR_PAIR(1));
    }
    // refresh window to display changes
    wrefresh(plotWin);
  }
}

// some testing code
//  int main() {
//      WINDOW *win = Display::drawMainWindow();
//      WINDOW *invWin = Display::drawInventoryWindow(win);
//      Display::drawDynamicWindow(win);
//      Display::drawCommandWindow(win);
//      WINDOW *gameWin = Display::drawGameWindow(win);
//
//      Player testPlayer = Player();
//      Inventory *inv = testPlayer.getPlayersInventory();
//
//      Item* Carroty = new Item(2,1,"Carrot");
//      Item* Potates = new Item(4,2,"Potato");
//      inv->addItem(Carroty);
//      inv->addItem(Potates);
//      inv->addItem(Potates);
//      Display::drawInventory(invWin, testPlayer);
//      testPlayer.move(coord{4, 5});
//      // testPlayer.setDirection(0);
//      Display::drawPlayer(gameWin, testPlayer);
//      CarrotPlant *carrot = new CarrotPlant(coord{0,0});
//      CarrotPlant *carrot2 = new CarrotPlant(coord{0,1});
//      FarmPlot farm = FarmPlot(coord{0,0}, coord{5,4});
//      farm.addPlant(carrot);
//      carrot->waterPlant();
//      carrot->setGrowthStage(2);
//      carrot2->dryPlant();
//      farm.addPlant(carrot2);
//      vector<FarmPlot> test = {farm};
//      Display::drawFarmPlots(gameWin, test);
//      getchar();
//      endwin();
//      return 0;
//  }
