/*#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Allincludes.h"
//My header file so far! basically jsut a copy paste of gpts tbh.
class GameManager {
 protected:
  // Define gameplay elements like the player, farmplot, and shop alongisde game
  // info like current days, and if running
  Player* player;
  FarmPlot* farmPlot;
  Shop* shop;
  int currentDay;
  bool gameRunning;

  // Define display stuff here

  // Display dimensions etc, whatever you need in terms of variables

 public:
  // Declare constructor and desconstructor
  GameManager();
  ~GameManager();

  // main game functions
  void initialiseGame();
  void gameLoop();
  void clean();

  // Functions to manage game state
  void advanceDay();
  void updateDisplay();  // Not sure how this would work
  void handleInput();

  // UI functions  (Stuff for displaying windows and such)

  // Actions in the game
  void movePlayer(int direction);
  void waterCurrentPlant();
  void newplantatposition();
  void harvestplant();
  void openShop();

  //Other functions needed 
  Plant* getPlantCoords(Plant* plant);
  bool validPositiontoPlant(coord position);
  char getDisplayChar(coord position);


}

#endif
*/
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Allincludes.h"
// #include"C:\Users\Halfa\Farmgame\FARM-GAME-1\pdcurses\PDCurses-master\curses.h"
#include <ncurses.h>
#include"AllHeader.h"

class GameManager {
private:
    Player* player;
    FarmPlot* farmPlot;
    Shop* shop;
    int currentDay;
    bool gameRunning;
    
    // Windows for different UI sections
    WINDOW* gameWin;
    WINDOW* infoWin;
    WINDOW* inventoryWin;
    WINDOW* farmWin;
    
    // UI dimensions and positions
    static const int FARM_WIDTH = 20;
    static const int FARM_HEIGHT = 15;
    static const int INFO_HEIGHT = 10;
    static const int INVENTORY_WIDTH = 30;

public:
    GameManager();
    // ~GameManager();
    
    // Main game functions
    void initializeGame();
    void gameLoop();
    void cleanup();
    
    // Game state management
    void advanceDay();
    void updateDisplay();
    void handleInput();
    
    // UI functions
    void drawFarm();
    void drawInventory();
    void drawPlayerInfo();
    void drawInstructions();
    void showShopMenu();
    void showPlantMenu();
    void showHarvestMenu();
    
    // Game actions
    void movePlayer(int direction);
    void waterCurrentPlant();
    void plantAtCurrentPosition();
    void harvestAtCurrentPosition();
    void openShop();
    
    // Utility functions
    Plant* getPlantAtPosition(coord position);
    bool isValidPosition(coord position);
    char getDisplayChar(coord position);
};

#endif
