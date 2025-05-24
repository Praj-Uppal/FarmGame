#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Allincludes.h"
// #include"C:\Users\Halfa\Farmgame\FARM-GAME-1\pdcurses\PDCurses-master\curses.h"
#include <ncurses.h>
#include <string>
#include <tuple>
#include <vector>
#include"AllHeader.h"
#include "FarmPlot.h"

class GameManager {
private:
    Player* player;
    FarmPlot* farmPlot;
    Shop* shop;
    int currentDay;
    bool gameRunning;
    bool plantMenuOpen;
    bool harvestMenuOpen;
    bool shopOpen;
    vector<FarmPlot> plots;
    
    // Windows for different UI sections
    WINDOW* mainWin;
    WINDOW* invWin;
    WINDOW* dynWin;
    WINDOW* comWin;
    WINDOW* gameWin;
    
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
    void plantAtCurrentPosition(string plant);
    void harvestPlot(string plant);
    void openShop();
    
    // Utility functions
    Plant* getPlantAtPosition(coord position);
    bool isValidPosition(coord position);
    char getDisplayChar(coord position);
    bool getPlantMenuOpen();
    void setPlantMenuOpen(bool status);
    bool getHarvestMenuOpen();
    void setHarvestMenuOpen(bool status);
    bool getShopOpen();
    void setShopOpen(bool status);
};

#endif
