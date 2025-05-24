#include "GameManager.h"
#include "Allincludes.h"
#include "CarrotPlant.h"
#include "Display.h"
#include "Item.h"
#include <ncurses.h>
#include <string>

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
            } else if (getShopOpen()) {
                if (player->getMoney() >= 2) {
                    player->setPlayersMoney(player->getMoney() - 2);
                    player->getPlayersInventory()->addItem(new Item(4, 2, "Potato"));
                    Display::drawInventoryWindow(mainWin);
                }
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
            } else if (getShopOpen()) {
                if (player->getMoney() >= 1) {
                    player->setPlayersMoney(player->getMoney() - 1);
                    player->getPlayersInventory()->addItem(new Item(2, 1, "Carrot"));
                    Display::drawInventoryWindow(mainWin);
                }
            }
            break;
        case 'j':
        case 'J':
            if (getShopOpen()) {
                if (player->getPlayersInventory()->howMany("Carrot") > 1) {
                    player->getPlayersInventory()->removeItem("Carrot");
                    player->setPlayersMoney(player->getMoney()+2);
                }
            }
            break;
        case 'k':
        case 'K':
            if (getShopOpen()) {
                if (player->getPlayersInventory()->howMany("Potato") > 1) {
                    player->getPlayersInventory()->removeItem("Potato");
                    player->setPlayersMoney(player->getMoney()+4);
                }
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
        case 27:
            setPlantMenuOpen(false);
            setHarvestMenuOpen(false);
            setShopOpen(false);
            Display::drawDynamicWindow(mainWin);
            break;
        case 'o':
        case 'O':
            openShop();
            break;
        case 'Q':
        case 'q':
            gameRunning = false;
            break;
      
    }
}
void GameManager::openShop() {
    setPlantMenuOpen(false);
    setHarvestMenuOpen(false);
    setShopOpen(true);
    Display::drawDynamicWindow(mainWin);
    mvwprintw(dynWin, 0, 1, "Shop");
    mvwprintw(dynWin, 1, 1, "C: Buy carrot");
    mvwprintw(dynWin, 2, 1, "P: Buy potato");
    mvwprintw(dynWin, 3, 1, "J: Sell carrot");
    mvwprintw(dynWin, 4, 1, "K: Sell potato");

    wrefresh(dynWin);
}

bool GameManager::getShopOpen() {
    return shopOpen;
}
void GameManager::setShopOpen(bool status) {
    shopOpen = status;

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
            // for (int j = 0; j < i->getCurrentCapacity(); j++) {
                // if (i->getPlants()[j]->isMature()) {
            for (int j = i->getCurrentCapacity() - 1; j >= 0; --j) {
                if (i->getPlants()[j]->isMature()) {
                    if (plant == "Carrot") {
                        i->removePlant(j);
                        numOfCarrots++;
                    } else if (plant == "Potato") {
                        i->removePlant(j);
                        numOfPotatoes++;
                    }
                    i->setCurrentCapacity(i->getCurrentCapacity() - 1);
                }
            }
        }
    }
    Item* Carrot = new Item(2, 1, "Carrot");
    Item* Potato = new Item(4, 2, "Potato");
    int recievedCarrots = (numOfCarrots * 2);
    int recievedPotatoes = (numOfPotatoes * 4);
    if (plant == "Carrot") {
        player->getPlayersInventory()->addItem(Carrot, recievedCarrots);
    } else if (plant == "Potato") {
        player->getPlayersInventory()->addItem(Potato, recievedPotatoes);
    }
    setHarvestMenuOpen(false);
    Display::drawDynamicWindow(mainWin);
}
void GameManager::showHarvestMenu() {
    setPlantMenuOpen(false);
    setShopOpen(false);
    setHarvestMenuOpen(true);
    Display::drawDynamicWindow(mainWin);
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
            if (player->getPlayersInventory()->howMany(plantType) > 1) {

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
    Display::drawDynamicWindow(mainWin);
    setHarvestMenuOpen(false);
    setShopOpen(false);
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

