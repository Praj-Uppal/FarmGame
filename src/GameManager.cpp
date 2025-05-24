#include "GameManager.h"
#include "Display.h"
#include <algorithm>

GameManager::GameManager() : currentDay(1), gameRunning(true) {
    player = new Player();
    farmPlot = new FarmPlot();
    shop = new Shop();
    
    // Give player some starting money and seeds
    player->setPlayersMoney(100);

    Item* Carrot = new Item(2, 1, "Carrot");
    Item* Potato = new Item(4,2,"Potato");

    player->getPlayersInventory()->addItem(Carrot, 5);
    player->getPlayersInventory()->addItem(Potato, 3);
}

// GameManager::~GameManager() {
//     cleanup();
//     delete player;
//     delete farmPlot;
//     delete shop;
// }

void GameManager::initializeGame() {
    Display::drawMainWindow();
    WINDOW* mainWin = Display::drawMainWindow();
    WINDOW* invWin = Display::drawInventoryWindow(mainWin);
    WINDOW* dynWin = Display::drawDynamicWindow(mainWin);
    WINDOW* commandWin = Display::drawCommandWindow(mainWin);
    WINDOW* gameWin = Display::drawGameWindow(mainWin);
    Display::drawInventory(invWin, *player);


}

void GameManager::gameLoop() {
    while (gameRunning) {
        // updateDisplay();
        // handleInput();
    }
}

// void GameManager::handleInput() {
//     int ch = getch();
//    
//     switch (ch) {
//         case KEY_UP:
//         case 'w':
//         case 'W':
//             movePlayer(0); // North
//             break;
//         case KEY_RIGHT:
//         case 'd':
//         case 'D':
//             movePlayer(1); // East
//             break;
//         case KEY_DOWN:
//         case 's':
//         case 'S':
//             movePlayer(2); // South
//             break;
//         case KEY_LEFT:
//         case 'a':
//         case 'A':
//             movePlayer(3); // West
//             break;
//         case ' ':
//         case 'e':
//         case 'E':
//             waterCurrentPlant();
//             break;
//         case 'p':
//         case 'P':
//             showPlantMenu();
//             break;
//         case 'h':
//         case 'H':
//             harvestAtCurrentPosition();
//             break;
//         case 'o':
//         case 'O':
//             openShop();
//             break;
//         case 'n':
//         case 'N':
//             advanceDay();
//             break;
//         case 'q':
//         case 'Q':
//             gameRunning = false;
//             break;
//     }
// }

// void GameManager::movePlayer(int direction) {
//     coord currentPos = player->getposition();
//     coord newPos = currentPos;
//    
//     switch (direction) {
//         case 0: // North
//             std::get<1>(newPos)--;
//             break;
//         case 1: // East
//             std::get<0>(newPos)++;
//             break;
//         case 2: // South
//             std::get<1>(newPos)++;
//             break;
//         case 3: // West
//             std::get<0>(newPos)--;
//             break;
//     }
//    
//     if (isValidPosition(newPos)) {
//         player->setPosition(newPos);
//         player->setDirection(direction);
//     }
// }

bool GameManager::isValidPosition(coord position) {
    int x = std::get<0>(position);
    int y = std::get<1>(position);
    return (x >= 0 && x < FARM_WIDTH && y >= 0 && y < FARM_HEIGHT);
}

// void GameManager::waterCurrentPlant() {
//     Plant* plant = getPlantAtPosition(player->getposition());
//     if (plant != nullptr) {
//         player->water(plant);
//     }
// }

// void GameManager::showPlantMenu() {
//     WINDOW* plantWin = newwin(8, 40, LINES/2 - 4, COLS/2 - 20);
//     box(plantWin, 0, 0);
//     mvwprintw(plantWin, 0, 2, " Plant Menu ");
//    
//     mvwprintw(plantWin, 2, 2, "1. Plant Carrot (Have: %d)", 
//               player->getPlayersInventory()->howMany("Carrot"));
//     mvwprintw(plantWin, 3, 2, "2. Plant Potato (Have: %d)", 
//               player->getPlayersInventory()->howMany("Potato"));
//     mvwprintw(plantWin, 5, 2, "Press 1 or 2 to plant, ESC to cancel");
//    
//     wrefresh(plantWin);
//    
//     int ch = getch();
//     if (ch == '1' && player->getPlayersInventory()->howMany("Carrot") > 0) {
//         player->plant(Carrotitem, farmPlot);
//         player->getPlayersInventory()->removeItem("Carrot", 1);
//     } else if (ch == '2' && player->getPlayersInventory()->howMany("Potato") > 0) {
//         player->plant(Potatoitem, farmPlot);
//         player->getPlayersInventory()->removeItem("Potato", 1);
//     }
//    
//     delwin(plantWin);
// }

// void GameManager::harvestAtCurrentPosition() {
//     Plant* plant = getPlantAtPosition(player->getposition());
//     if (plant != nullptr && plant->isMature()) {
//         vector<tuple<Item*,int>> harvest = plant->harvest();
//         for (auto& item : harvest) {
//             player->getPlayersInventory()->addItem(std::get<0>(item), std::get<1>(item));
//         }
//        
//         // Remove plant from farm plot
//         vector<Plant*> plants = farmPlot->getPlants();
//         for (int i = 0; i < plants.size(); i++) {
//             if (plants[i] == plant) {
//                 farmPlot->removePlant(i);
//                 break;
//             }
//         }
//     }
// }

// void GameManager::openShop() {
//     WINDOW* shopWin = newwin(12, 50, LINES/2 - 6, COLS/2 - 25);
//     box(shopWin, 0, 0);
//     mvwprintw(shopWin, 0, 2, " Shop - Money: $%d ", player->getMoney());
//    
//     mvwprintw(shopWin, 2, 2, "BUY:");
//     mvwprintw(shopWin, 3, 2, "1. Carrot Seeds ($1 each)");
//     mvwprintw(shopWin, 4, 2, "2. Potato Seeds ($2 each)");
//     mvwprintw(shopWin, 6, 2, "SELL:");
//     mvwprintw(shopWin, 7, 2, "3. Sell All Items");
//     mvwprintw(shopWin, 9, 2, "Press 1-3 to select, ESC to exit");
//    
//     wrefresh(shopWin);
//    
//     int ch = getch();
//     switch (ch) {
//         case '1':
//             if (shop->buyCarrot(1, player)) {
//                 mvwprintw(shopWin, 10, 2, "Bought 1 Carrot Seed!");
//             } else {
//                 mvwprintw(shopWin, 10, 2, "Not enough money!");
//             }
//             wrefresh(shopWin);
//             getch();
//             break;
//         case '2':
//             if (shop->buyPotato(1, player)) {
//                 mvwprintw(shopWin, 10, 2, "Bought 1 Potato Seed!");
//             } else {
//                 mvwprintw(shopWin, 10, 2, "Not enough money!");
//             }
//             wrefresh(shopWin);
//             getch();
//             break;
//         case '3':
//             shop->sellInventory(player);
//             mvwprintw(shopWin, 10, 2, "Sold all items!");
//             wrefresh(shopWin);
//             getch();
//             break;
//     }
//    
//     delwin(shopWin);
// }
//
// Plant* GameManager::getPlantAtPosition(coord position) {
//     vector<Plant*> plants = farmPlot->getPlants();
//     for (Plant* plant : plants) {
//         if (plant->getPosistion() == position) {
//             return plant;
//         }
//     }
//     return nullptr;
// }
//
// void GameManager::advanceDay() {
//     currentDay++;
//     vector<Plant*> plants = farmPlot->getPlants();
//     for (Plant* plant : plants) {
//         plant->advanceDay();
//     }
// }
//
// void GameManager::updateDisplay() {
//     drawFarm();
//     drawInventory();
//     drawPlayerInfo();
//     drawInstructions();
//    
//     wrefresh(gameWin);
//     wrefresh(farmWin);
//     wrefresh(inventoryWin);
//     wrefresh(infoWin);
// }

// void GameManager::drawFarm() {
//     // Clear farm area
//     for (int y = 1; y < FARM_HEIGHT + 1; y++) {
//         for (int x = 1; x < FARM_WIDTH + 1; x++) {
//             mvwaddch(farmWin, y, x, '.');
//         }
//     }
//    
//     // Draw plants
//     vector<Plant*> plants = farmPlot->getPlants();
//     for (Plant* plant : plants) {
//         coord pos = plant->getPosistion();
//         int x = std::get<0>(pos) + 1;
//         int y = std::get<1>(pos) + 1;
//        
//         char plantChar = 'o'; // Default plant
//         if (plant->isMature()) {
//             plantChar = 'O'; // Mature plant
//         }
//         if (plant->isWatered()) {
//             plantChar = '*'; // Watered plant
//         }
//        
//         mvwaddch(farmWin, y, x, plantChar);
//     }
//    
//     // Draw player
//     coord playerPos = player->getposition();
//     int px = std::get<0>(playerPos) + 1;
//     int py = std::get<1>(playerPos) + 1;
//     mvwaddch(farmWin, py, px, '@');
// }
//
void GameManager::drawInventory() {
    int line = 2;
    mvwprintw(inventoryWin, line++, 2, "Money: $%d", player->getMoney());
    line++;
    
    Inventory* inv = player->getPlayersInventory();
    for (auto it = inv->begin(); it != inv->end(); ++it) {
        if (it->second.second > 0) {
            mvwprintw(inventoryWin, line++, 2, "%s: %d", 
                     it->first.c_str(), it->second.second);
        }
    }
}

// void GameManager::drawPlayerInfo() {
//     mvwprintw(infoWin, 2, 2, "Day: %d", currentDay);
//     mvwprintw(infoWin, 3, 2, "Position: (%d, %d)", 
//               std::get<0>(player->getposition()), std::get<1>(player->getposition()));
//    
//     Plant* currentPlant = getPlantAtPosition(player->getposition());
//     if (currentPlant != nullptr) {
//         mvwprintw(infoWin, 5, 2, "Plant here:");
//         mvwprintw(infoWin, 6, 2, "Growth: %d/%d", 
//                   currentPlant->getGrowthStage(), currentPlant->getMaxGrowth());
//         mvwprintw(infoWin, 7, 2, "Care: %d/%d", 
//                   currentPlant->getCaredForDays(), currentPlant->getCareRequired());
//         mvwprintw(infoWin, 8, 2, "Watered: %s", currentPlant->isWatered() ? "Yes" : "No");
//     }
// }

void GameManager::drawInstructions() {
    int startY = FARM_HEIGHT + INFO_HEIGHT + 6;
    mvwprintw(gameWin, startY, 4, "Controls:");
    mvwprintw(gameWin, startY + 1, 4, "WASD/Arrows: Move");
    mvwprintw(gameWin, startY + 2, 4, "E/Space: Water plant");
    mvwprintw(gameWin, startY + 3, 4, "P: Plant menu");
    mvwprintw(gameWin, startY + 4, 4, "H: Harvest");
    mvwprintw(gameWin, startY + 5, 4, "O: Open shop");
    mvwprintw(gameWin, startY + 6, 4, "N: Next day");
    mvwprintw(gameWin, startY + 7, 4, "Q: Quit");
}

void GameManager::cleanup() {
    if (gameWin) delwin(gameWin);
    if (farmWin) delwin(farmWin);
    if (inventoryWin) delwin(inventoryWin);
    if (infoWin) delwin(infoWin);
    endwin();
}
