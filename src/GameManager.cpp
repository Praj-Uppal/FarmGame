#include "GameManager.h"
#include "Allincludes.h"
#include "CarrotPlant.h"
#include "Display.h"
#include "Item.h"
#include <ncurses.h>
#include <string>
#include <utility>

GameManager::GameManager() : currentDay(1), gameRunning(true) {
    // Init ncurses
    initscr(); // This starts curses mode
    cbreak(); // Catch all keyboard input
    keypad(stdscr, TRUE); // Allows use of arrow keys
    noecho(); // Do not echo user input to terminal
    setlocale(LC_ALL, ""); // This enables unicode support
    curs_set(0); // This hides the cursor
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);

 
    player = new Player();
    farmPlot = new FarmPlot();
    shop = new Shop();
    
    // Give player some starting money and seeds
    player->setPlayersMoney(100);

    Item* Carrot = new Item(2, 1, "Carrot");
    Item* Potato = new Item(4,2,"Potato");
    player->getPlayersInventory()->addItem(Carrot, 5);
    player->getPlayersInventory()->addItem(Potato, 3);

    // breaks up game window into segments
    int vSplit = ((LINES - (LINES * 0.30) - 1) / 3);
    int hSplit = ((COLS - 2) * 0.75 ) / 5;

    // Set players initial position
    player->setPosition(coord{vSplit, hSplit * 1.6});
    player->setDirection(2);

    // Generate farm plots
    FarmPlot farmA = FarmPlot(coord{0,0}, coord{vSplit - 1, hSplit - 1});
    FarmPlot farmB = FarmPlot(coord{vSplit,0}, coord{vSplit - 1, hSplit - 1});
    FarmPlot farmC = FarmPlot(coord{vSplit * 2,0}, coord{vSplit - 1, hSplit - 1});
    FarmPlot farmD = FarmPlot(coord{0,hSplit}, coord{vSplit - 1, (hSplit * 1.3) - 1});
    FarmPlot farmE = FarmPlot(coord{vSplit,hSplit}, coord{vSplit - 1, (hSplit * 1.3) - 1});
    FarmPlot farmF = FarmPlot(coord{vSplit * 2,hSplit}, coord{vSplit - 1, (hSplit * 1.3) - 1});
    FarmPlot farmG = FarmPlot(coord{0,hSplit * 2.3}, coord{vSplit - 1, (hSplit) - 1});
    FarmPlot farmH = FarmPlot(coord{vSplit,hSplit * 2.3}, coord{vSplit - 1, (hSplit) - 1});
    FarmPlot farmI = FarmPlot(coord{vSplit * 2,hSplit * 2.3}, coord{vSplit - 1, (hSplit) - 1});
    FarmPlot farmJ = FarmPlot(coord{0,hSplit * 3.3}, coord{vSplit * 3 - 1, (hSplit) - 1});
    plots.push_back(farmA);
    plots.push_back(farmB);
    plots.push_back(farmC);
    plots.push_back(farmD);
    plots.push_back(farmE);
    plots.push_back(farmF);
    plots.push_back(farmG);
    plots.push_back(farmH);
    plots.push_back(farmI);
    plots.push_back(farmJ);
}

void GameManager::initializeGame() {
    mainWin = Display::drawMainWindow();
    invWin = Display::drawInventoryWindow(mainWin);
    dynWin = Display::drawDynamicWindow(mainWin);
    comWin = Display::drawCommandWindow(mainWin);
    gameWin = Display::drawGameWindow(mainWin);
    Display::drawDays(mainWin, currentDay);
    Display::drawInventory(invWin, *player);
    Display::drawFarmPlots(gameWin, plots);
    Display::drawPlayer(gameWin, *player);
    Display::drawCommands(comWin);
}

void GameManager::gameLoop() {
    while (gameRunning) {
        updateDisplay();
        handleInput();
    }
}
void GameManager::updateDisplay() {
    Display::drawFarmPlots(gameWin, plots);
    Display::drawPlayer(gameWin, *player);
    Display::drawInventory(invWin, *player);
}
void GameManager::handleInput() {
    int ch = getchar();
    switch (ch) {
        case KEY_UP:
        case 'w':
        case 'W':
            movePlayer(0); // North
            break;
        case KEY_RIGHT:
        case 'd':
        case 'D':
            movePlayer(1); // East
            break;
        case KEY_DOWN:
        case 's':
        case 'S':
            movePlayer(2); // South
            break;
        case KEY_LEFT:
        case 'a':
        case 'A':
            movePlayer(3); // West
            break;
        case 'p':
        case 'P':
            if (getPlantMenuOpen()) {
                // Plant potato
                plantAtCurrentPosition("Potato");
            } else if (getHarvestMenuOpen()) {
                harvestPlot("Potato");
            } else {
                showPlantMenu();
            }
            break;
        case 'c':
        case 'C':
            if (getPlantMenuOpen()) {
                plantAtCurrentPosition("Carrot");
                // Plant carrot
            } else if (getHarvestMenuOpen()) {
                harvestPlot("Carrot");
            }
            break;
        case 'E':
        case 'e':
        case KEY_ENTER:
        case '\n':
        case '\r':
            waterCurrentPlant();
            break;
        case 'N':
        case 'n':
            advanceDay();
            Display::drawDays(mainWin, currentDay);
            break;
        case 'H':
        case 'h':
            showHarvestMenu();

            break;
        case 'Q':
        case 'q':
            gameRunning = false;
            break;
      
    }
}
void GameManager::harvestPlot(string plant) {
    int y = std::get<0>(player->getPosition());
    int x = std::get<1>(player->getPosition());
    switch (player->getDirection()) {
        case 0: // North
            y--;
            break;
        case 1: // East
            x++;
            break;
        case 2: // South
            y++;
            break;
        case 3: // West
            x--;
            break;
    }
    int numOfCarrots = 0;
    int numOfPotatoes = 0;
    for (auto i = plots.begin(); i != plots.end(); i++) {
        int currentCap = i->getCurrentCapacity();
        int topY = std::get<0>(i->getTopLeftCoord());
        int leftX = std::get<1>(i->getTopLeftCoord());
        int bottomY = topY + std::get<0>(i->getDimensions());
        int rightX = leftX + std::get<1>(i->getDimensions());
    
        if (y > topY && y < bottomY && x > leftX && x < rightX) {
            for (int j = 0; j < i->getCurrentCapacity(); j++) {
                if (i->getPlants()[j]->isMature()) {
                    if (plant == "Carrot") {
                        i->removePlant(j);
                        numOfCarrots++;
                    } else if (plant == "Potato") {
                        i->removePlant(j);
                        numOfPotatoes++;
                    }
                }
            }
        }
    }
    // Item* Carrotb = new Item(2, 1, "Carrot");
    // player->getPlayersInventory()->addItem(Carrotb, 5);
    // if (plant == "Carrot") {
    //     player->getPlayersInventory()->addItem(new Item(2, 1, "Carrot"), 1);
    // } else if (plant == "Potato") {
    //     player->getPlayersInventory()->addItem(new Item(4, 2, "Potato"), 1);
    // }
}
void GameManager::showHarvestMenu() {
    setPlantMenuOpen(false);
    setHarvestMenuOpen(true);
    mvwprintw(dynWin, 0, 1, "Harvest");
    int y = std::get<0>(player->getPosition());
    int x = std::get<1>(player->getPosition());
    switch (player->getDirection()) {
        case 0: // North
            y--;
            break;
        case 1: // East
            x++;
            break;
        case 2: // South
            y++;
            break;
        case 3: // West
            x--;
            break;
    }
    int numOfCarrots = 0;
    int numOfPotatoes = 0;
    for (auto i = plots.begin(); i != plots.end(); i++) {
        int currentCap = i->getCurrentCapacity();
        int topY = std::get<0>(i->getTopLeftCoord());
        int leftX = std::get<1>(i->getTopLeftCoord());
        int bottomY = topY + std::get<0>(i->getDimensions());
        int rightX = leftX + std::get<1>(i->getDimensions());
    
        if (y > topY && y < bottomY && x > leftX && x < rightX) {
            for (int j = 0; j < i->getCurrentCapacity(); j++) {
                if (i->getPlants()[j]->isMature()) {
                    if (i->getPlants()[j]->getName() == "CarrotPlant") {
                        numOfCarrots++;
                    } else if (i->getPlants()[j]->getName() == "PotatoPlant") {
                        numOfPotatoes++;
                    }
                    mvwprintw(dynWin, 8, 1, "test  %s", i->getPlants()[j]->getName().c_str());
                }
            }
        }
    }
    mvwprintw(dynWin, 1, 1, "Potatoes ready: %d", numOfPotatoes);
    mvwprintw(dynWin, 2, 1, "Carrots ready: %d", numOfCarrots);
    mvwprintw(dynWin, 3, 1, "C: Harvest carrots");
    mvwprintw(dynWin, 4, 1, "P: Harvest potatoes");

    wrefresh(dynWin);
}
void GameManager::plantAtCurrentPosition(string plantType) {
    int y = std::get<0>(player->getPosition());
    int x = std::get<1>(player->getPosition());
    switch (player->getDirection()) {
        case 0: // North
            y--;
            break;
        case 1: // East
            x++;
            break;
        case 2: // South
            y++;
            break;
        case 3: // West
            x--;
            break;
    }
    for (auto i = plots.begin(); i != plots.end(); i++) {
        int currentCap = i->getCurrentCapacity();
        int topY = std::get<0>(i->getTopLeftCoord());
        int leftX = std::get<1>(i->getTopLeftCoord());
        int bottomY = topY + std::get<0>(i->getDimensions());
        int rightX = leftX + std::get<1>(i->getDimensions());

        if (y > topY && y < bottomY && x > leftX && x < rightX) {
            if (player->getPlayersInventory()->howMany(plantType) > 0) {

                // Map number to position in the plot
                int yy = currentCap / (std::get<1>(i->getDimensions()) - 2);
                int xx = currentCap % (std::get<1>(i->getDimensions()) - 2);

                if (currentCap != i->getMaxCapacity()) {
                    if (plantType == "Carrot") {
                        i->addPlant(new CarrotPlant(coord{yy,xx}));
                    } else if (plantType == "Potato") {
                        i->addPlant(new PotatoPlant(coord{yy,xx}));
                    }
                    i->setCurrentCapacity(currentCap + 1);
                } 
                player->getPlayersInventory()->removeItem(plantType);
            } else {
                    // not enough, show error
            }
        }

    }
}
void GameManager::movePlayer(int direction) {
    int y = std::get<0>(player->getPosition());
    int x = std::get<1>(player->getPosition());
      
    if (direction == player->getDirection()) {
        switch (direction) {
            case 0: // North
                y--;
                break;
            case 1: // East
                x++;
                break;
            case 2: // South
                y++;
                break;
            case 3: // West
                x--;
                break;
        }
    }
    coord newPos = coord{y, x};
    if (isValidPosition(newPos)) {
        player->setDirection(direction);
        player->setPosition(newPos);
    }
}
bool GameManager::isValidPosition(coord position) {
    int y = std::get<0>(position);
    int x = std::get<1>(position);
    int height = LINES - (LINES * 0.30) - 1;
    int width = (COLS - 2) * 0.75;
    return (x >= 1 && x < width - 1 && y >= 1 && y < height - 1);
}
void GameManager::showPlantMenu() {
    setHarvestMenuOpen(false);
    setPlantMenuOpen(true);
    mvwprintw(dynWin, 0, 1, "Plants");
    mvwprintw(dynWin, 1, 1, "C: Plant carrot");
    mvwprintw(dynWin, 2, 1, "P: Plant potato");

    wrefresh(dynWin);
}
bool GameManager::getPlantMenuOpen() {
    return plantMenuOpen;
}
void GameManager::setPlantMenuOpen(bool status) {
    plantMenuOpen = status;
}
bool GameManager::getHarvestMenuOpen() {
    return harvestMenuOpen;
}
void GameManager::setHarvestMenuOpen(bool status) {
    harvestMenuOpen = status;
}
void GameManager::waterCurrentPlant() {
    int y = std::get<0>(player->getPosition());
    int x = std::get<1>(player->getPosition());
    switch (player->getDirection()) {
        case 0: // North
            y--;
            break;
        case 1: // East
            x++;
            break;
        case 2: // South
            y++;
            break;
        case 3: // West
            x--;
            break;
    }
    for (auto i = plots.begin(); i != plots.end(); i++) {
        int currentCap = i->getCurrentCapacity();
        int topY = std::get<0>(i->getTopLeftCoord());
        int leftX = std::get<1>(i->getTopLeftCoord());
        int bottomY = topY + std::get<0>(i->getDimensions());
        int rightX = leftX + std::get<1>(i->getDimensions());

        if (y > topY && y < bottomY && x > leftX && x < rightX) {
            for (int j = 0; j < i->getCurrentCapacity(); j++) {
                i->getPlants()[j]->waterPlant();
            }
        }
    }
}
void GameManager::advanceDay() {
    currentDay++;
    for (auto i = plots.begin(); i != plots.end(); i++) {
        for (int j = 0; j < i->getCurrentCapacity(); j++) {
            i->getPlants()[j]->advanceDay();
        }
    }
}
// void GameManager::advanceDay() {
//     currentDay++;
//     vector<Plant*> plants = farmPlot->getPlants();
//     for (Plant* plant : plants) {
//         plant->advanceDay();
//     }
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
// void GameManager::drawInventory() {
//     int line = 2;
//     mvwprintw(inventoryWin, line++, 2, "Money: $%d", player->getMoney());
//     line++;
//    
//     Inventory* inv = player->getPlayersInventory();
//     for (auto it = inv->begin(); it != inv->end(); ++it) {
//         if (it->second.second > 0) {
//             mvwprintw(inventoryWin, line++, 2, "%s: %d", 
//                      it->first.c_str(), it->second.second);
//         }
//     }
// }

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

// void GameManager::drawInstructions() {
//     int startY = FARM_HEIGHT + INFO_HEIGHT + 6;
//     mvwprintw(gameWin, startY, 4, "Controls:");
//     mvwprintw(gameWin, startY + 1, 4, "WASD/Arrows: Move");
//     mvwprintw(gameWin, startY + 2, 4, "E/Space: Water plant");
//     mvwprintw(gameWin, startY + 3, 4, "P: Plant menu");
//     mvwprintw(gameWin, startY + 4, 4, "H: Harvest");
//     mvwprintw(gameWin, startY + 5, 4, "O: Open shop");
//     mvwprintw(gameWin, startY + 6, 4, "N: Next day");
//     mvwprintw(gameWin, startY + 7, 4, "Q: Quit");
// }

// void GameManager::cleanup() {
//     if (gameWin) delwin(gameWin);
//     if (farmWin) delwin(farmWin);
//     if (inventoryWin) delwin(inventoryWin);
//     if (infoWin) delwin(infoWin);
//     endwin();
// }
