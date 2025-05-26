#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Allincludes.h"
#include <ncurses.h>
#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include"AllHeader.h"
#include "FarmPlot.h"
#include "Player.h"

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
    bool FullPlotError;
    bool InsufficientItemsError;
    bool InsufficientMoneyError;
    bool NoPotatoesToSell;
    bool NoCarrotsToSell;
    bool NoCarrotsToHarvest;
    bool NoPotatoesToHarvest;
    vector<FarmPlot> plots;
    
    // Windows for different UI sections
    WINDOW* mainWin;
    WINDOW* invWin;
    WINDOW* dynWin;
    WINDOW* comWin;
    WINDOW* gameWin;
    WINDOW* errorWin;

    //Save/ Load functions for money
    void saveMoney();
    void loadMoney();
    
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
    void showFullPlotError();
    void showInsufficientItemsError();
    void showInsufficientMoneyError();
    void showNoPotatoSellError();
    void showNoCarrotSellError();
    void showNoPotatoHarvestError();
    void showNoCarrotHarvestError();
    
    // Game actions
	void movePlayer(Player::MoveDirection direction);
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
    bool getFullPlotError();
    void setFullPlotError(bool status);
    bool getInsufficientItemsError();
    void setInsufficientItemsError(bool status);
    bool getInsufficientMoneyError();
    void setInsufficientMoneyError(bool status);
    bool getNoPotatoSellError();
    void setNoPotatoSellError(bool status);
    bool getNoCarrotSellError();
    void setNoCarrotSellError(bool status);
    bool getNoPotatoHarvestError();
    void setNoPotatoHarvestError(bool status);
    bool getNoCarrotHarvestError();
    void setNoCarrotHarvestError(bool status);

};

#endif
