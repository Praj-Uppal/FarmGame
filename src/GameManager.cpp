#include "GameManager.h"

#include <ncurses.h>

#include <string>

#include "Allincludes.h"
#include "CarrotPlant.h"
#include "Display.h"
#include "Item.h"


GameManager::GameManager()
    : currentDay(1),
      gameRunning(true),
      //Set all menu options to false
      plantMenuOpen(false),
      harvestMenuOpen(false),
      shopOpen(false),
      FullPlotError(false),
      InsufficientItemsError(false),
      InsufficientMoneyError(false),
      NoPotatoesToHarvest(false),
      NoCarrotsToHarvest(false),
      NoPotatoesToSell(false),
      NoCarrotsToSell(false) {
  // Init ncurses
  initscr();              // This starts curses mode
  cbreak();               // Catch all keyboard input
  keypad(stdscr, TRUE);   // Allows use of arrow keys
  noecho();               // Do not echo user input to terminal
  setlocale(LC_ALL, "");  // This enables unicode support
  curs_set(0);            // This hides the cursor
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK);

  // initialise Game variables
  player = new Player();
  farmPlot = new FarmPlot();
  shop = new Shop();

  // Give player some starting money and seeds
  player->setPlayersMoney(100);

  Item* Carrot = new Item(1, 1, "Carrot");
  Item* Potato = new Item(4, 4, "Potato");
  player->getPlayersInventory()->addItem(Carrot);
  player->getPlayersInventory()->addItem(Potato);

  //Try to load in data from save file
  ifstream test("save.dat"); //Check if file exists
  if (test.is_open()) {
    test.close();
    loadMoney();
  }

  //Check is save money is below or at 0, and if so set to 10
  if (player->getMoney() <= 0) {
    player->setPlayersMoney(10);
  }

  // breaks up game window into segments
  int vSplit = ((LINES - (LINES * 0.30) - 1) / 3);
  int hSplit = ((COLS - 2) * 0.75) / 5;

  // Set players initial position
  player->setPosition(coord{vSplit, hSplit * 1.6});
  player->setDirection(Player::MoveDirection::North);

  // Generate farm plots
  FarmPlot farmA = FarmPlot(coord{0, 0}, coord{vSplit - 1, hSplit - 1});
  FarmPlot farmB = FarmPlot(coord{vSplit, 0}, coord{vSplit - 1, hSplit - 1});
  FarmPlot farmC =
      FarmPlot(coord{vSplit * 2, 0}, coord{vSplit - 1, hSplit - 1});
  FarmPlot farmD =
      FarmPlot(coord{0, hSplit}, coord{vSplit - 1, (hSplit * 1.3) - 1});
  FarmPlot farmE =
      FarmPlot(coord{vSplit, hSplit}, coord{vSplit - 1, (hSplit * 1.3) - 1});
  FarmPlot farmF = FarmPlot(coord{vSplit * 2, hSplit},
                            coord{vSplit - 1, (hSplit * 1.3) - 1});
  FarmPlot farmG =
      FarmPlot(coord{0, hSplit * 2.3}, coord{vSplit - 1, (hSplit)-1});
  FarmPlot farmH =
      FarmPlot(coord{vSplit, hSplit * 2.3}, coord{vSplit - 1, (hSplit)-1});
  FarmPlot farmI =
      FarmPlot(coord{vSplit * 2, hSplit * 2.3}, coord{vSplit - 1, (hSplit)-1});
  FarmPlot farmJ =
      FarmPlot(coord{0, hSplit * 3.3}, coord{vSplit * 3 - 1, (hSplit)-1});
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
// Function to initialise game
void GameManager::initializeGame() {
  // Draw windows, and assign windows
  mainWin = Display::drawMainWindow();
  invWin = Display::drawInventoryWindow(mainWin);
  dynWin = Display::drawDynamicWindow(mainWin);
  comWin = Display::drawCommandWindow(mainWin);
  gameWin = Display::drawGameWindow(mainWin);
  errorWin = Display::drawErrorWindow(mainWin);
  // Display information in windows
  Display::drawDays(mainWin, currentDay);
  Display::drawInventory(invWin, *player);
  Display::drawFarmPlots(gameWin, plots);
  Display::drawPlayer(gameWin, *player);
  Display::drawCommands(comWin);
}
// Function to manage gameloop
void GameManager::gameLoop() {
  // While game is running continously update display, and handle input
  while (gameRunning) {
    updateDisplay();
    handleInput();
  }
}
// Update display function
void GameManager::updateDisplay() {
  // Updates information in windows like inventory and main game window
  Display::drawFarmPlots(gameWin, plots);
  Display::drawPlayer(gameWin, *player);
  Display::drawInventory(invWin, *player);
}
// Function to handle input
void GameManager::handleInput() {
  // Gets char pressed
  int ch = getchar();
  // Based on the key pressed, different actions
  switch (ch) {
    case KEY_UP:
    case 'w':
    case 'W':
      movePlayer(Player::MoveDirection::North);
      break;
    case KEY_RIGHT:
    case 'd':
    case 'D':
      movePlayer(Player::MoveDirection::East);
      break;
    case KEY_DOWN:
    case 's':
    case 'S':
      movePlayer(Player::MoveDirection::South);
      break;
    case KEY_LEFT:
    case 'a':
    case 'A':
      movePlayer(Player::MoveDirection::West);
      break;
    case 'p':
    case 'P':  // Key for potato interactions
      if (getPlantMenuOpen()) {
        // Plant potato if plant menu open
        plantAtCurrentPosition("Potato");
      } else if (getHarvestMenuOpen()) {
        // harvest potato if potato menu open
        harvestPlot("Potato");
      } else if (getShopOpen()) {
        // If shop open try to buy potato
        if (player->getMoney() >= 4) {
          player->setPlayersMoney(player->getMoney() - 4);
          player->getPlayersInventory()->addItem(new Item(4, 4, "Potato"));
          // Update inventory
          Display::drawInventoryWindow(mainWin);
        } else {
          showInsufficientMoneyError();
        }
      } else {
        // On default show plant menu
        showPlantMenu();
      }
      break;
    case 'c':
    case 'C':  // Carrot interactions
      if (getPlantMenuOpen()) {
        plantAtCurrentPosition("Carrot");
        // Plant carrot if plant menu open
      } else if (getHarvestMenuOpen()) {
        harvestPlot("Carrot");     // Harvest carrot if harvest menu open
      } else if (getShopOpen()) {  // If shop menu open, buy carrot
        if (player->getMoney() >= 1) {
          player->setPlayersMoney(player->getMoney() - 1);
          player->getPlayersInventory()->addItem(new Item(1, 1, "Carrot"));
          Display::drawInventoryWindow(mainWin);
        } else {
          showInsufficientMoneyError();
        }
      }
      break;
    case 'j':
    case 'J':  // Key to sell carrot when shop open
      if (getShopOpen()) {
        if (player->getPlayersInventory()->howMany("Carrot") > 1) {
          player->getPlayersInventory()->removeItem("Carrot");
          player->setPlayersMoney(player->getMoney() + 1);
        } else {
          showNoCarrotSellError();
        }
      }
      break;
    case 'k':
    case 'K':  // key to sell potato when shop open
      if (getShopOpen()) {
        if (player->getPlayersInventory()->howMany("Potato") > 1) {
          player->getPlayersInventory()->removeItem("Potato");
          player->setPlayersMoney(player->getMoney() + 4);
        } else {
          showNoPotatoSellError();
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
    case 'n':  // Key to advance day
      advanceDay();
      // Updates day counter
      Display::drawDays(mainWin, currentDay);
      break;
    case 'H':
    case 'h':  // Opens harvest menu
      showHarvestMenu();
      break;
    case 27:  // Clear dynamic window
      setPlantMenuOpen(false);
      setHarvestMenuOpen(false);
      setShopOpen(false);
      Display::drawDynamicWindow(mainWin);
      break;
    case 'o':
    case 'O':  // Key to open shop
      openShop();
      break;
    case 'Q':
    case 'q':  // Key to quit game
      gameRunning = false;
      break;
  }
}
// Function to open shop
void GameManager::openShop() {
  // Close plant and harvest menu if open
  setPlantMenuOpen(false);
  setHarvestMenuOpen(false);
  // Open shop menu
  setShopOpen(true);
  // Update dynamic window
  Display::drawDynamicWindow(mainWin);
  // Add Labels
  mvwprintw(dynWin, 0, 1, "Shop");
  mvwprintw(dynWin, 1, 1, "C: Buy carrot");
  mvwprintw(dynWin, 2, 1, "P: Buy potato");
  mvwprintw(dynWin, 3, 1, "J: Sell carrot");
  mvwprintw(dynWin, 4, 1, "K: Sell potato");

  // Refresh dynamic window
  wrefresh(dynWin);
}

// Function to return shop menu status
bool GameManager::getShopOpen() { return shopOpen; }
// Function to set shop menu status
void GameManager::setShopOpen(bool status) { shopOpen = status; }

// Function to harvest plot
void GameManager::harvestPlot(string plant) {
  // Get player coordinates
  int y = std::get<0>(player->getPosition());
  int x = std::get<1>(player->getPosition());
  // Based on player direction, get plot facing in front of them
  switch (player->getDirection()) {
    case Player::MoveDirection::North:  // North
      y--;
      break;
    case Player::MoveDirection::East:  // East
      x++;
      break;
    case Player::MoveDirection::South:  // South
      y++;
      break;
    case Player::MoveDirection::West:  // West
      x--;
      break;
  }
  // initialise carrot and potato count to 0
  int numOfCarrots = 0;
  int numOfPotatoes = 0;
  // Loop through plots
  for (auto i = plots.begin(); i != plots.end(); i++) {
    int currentCap = i->getCurrentCapacity();
    int topY = std::get<0>(i->getTopLeftCoord());
    int leftX = std::get<1>(i->getTopLeftCoord());
    int bottomY = topY + std::get<0>(i->getDimensions());
    int rightX = leftX + std::get<1>(i->getDimensions());

    if (y > topY && y < bottomY && x > leftX && x < rightX) {
      // for (int j = 0; j < i->getCurrentCapacity(); j++) {
      // if (i->getPlants()[j]->isMature()) {
      // loop over plants in plot and check if mature
      if (plant == "Carrot") {
        for (int j = i->getCurrentCapacity() - 1; j >= 0; --j) {
          // If mature and a carrot, increment carrot or potato count
          if (i->getPlants()[j]->isMature() &&
              i->getPlants()[j]->getName() == "CarrotPlant") {
            i->removePlant(j);
            numOfCarrots++;
          }
        }
      } else if (plant == "Potato") {
        for (int j = i->getCurrentCapacity() - 1; j >= 0; --j) {
          if (i->getPlants()[j]->isMature() &&
              i->getPlants()[j]->getName() == "PotatoPlant") {
            i->removePlant(j);
            numOfPotatoes++;
          }
        }
      }
    }
  }

  // Define carrot and potato items and add to player inventory
  Item* Carrot = new Item(1, 1, "Carrot");
  Item* Potato = new Item(4, 4, "Potato");
  int recievedCarrots = (numOfCarrots * 2);
  int recievedPotatoes = (numOfPotatoes * 4);
  // Add to player inventory
  if (plant == "Carrot") {
    if (recievedCarrots == 0) {
      showNoCarrotHarvestError();
    }
    player->getPlayersInventory()->addItem(Carrot, recievedCarrots);
  } else if (plant == "Potato") {
    if (recievedPotatoes == 0) {
      showNoPotatoHarvestError();
    }
    player->getPlayersInventory()->addItem(Potato, recievedPotatoes);
  }
  // close harvest menu
  setHarvestMenuOpen(false);
  // update dynamic window
  Display::drawDynamicWindow(mainWin);
}

// Function to show Harvest menu
void GameManager::showHarvestMenu() {
  // Close other menus and open Harvest menu
  setPlantMenuOpen(false);
  setShopOpen(false);
  setHarvestMenuOpen(true);
  // Draw Dynamic window
  Display::drawDynamicWindow(mainWin);
  // Label
  mvwprintw(dynWin, 0, 1, "Harvest");
  // Get player coords
  int y = std::get<0>(player->getPosition());
  int x = std::get<1>(player->getPosition());
  // Based on player direction, get plot facing in front of them
  switch (player->getDirection()) {
    case Player::MoveDirection::North:  // North
      y--;
      break;
    case Player::MoveDirection::East:  // East
      x++;
      break;
    case Player::MoveDirection::South:  // South
      y++;
      break;
    case Player::MoveDirection::West:  // West
      x--;
      break;
  }
  // Initialize number of carrots and potatoes in plot facing in front of them
  int numOfCarrots = 0;
  int numOfPotatoes = 0;
  // Iterate through plots and check if plot is the one player is facing
  for (auto i = plots.begin(); i != plots.end(); i++) {
    int currentCap = i->getCurrentCapacity();
    int topY = std::get<0>(i->getTopLeftCoord());
    int leftX = std::get<1>(i->getTopLeftCoord());
    int bottomY = topY + std::get<0>(i->getDimensions());
    int rightX = leftX + std::get<1>(i->getDimensions());

    if (y > topY && y < bottomY && x > leftX && x < rightX) {
      // For the right plot, iterate through plants and check if matured to get
      // potential count
      for (int j = 0; j < i->getCurrentCapacity(); j++) {
        if (i->getPlants()[j]->isMature()) {
          if (i->getPlants()[j]->getName() == "CarrotPlant") {
            numOfCarrots++;
          } else if (i->getPlants()[j]->getName() == "PotatoPlant") {
            numOfPotatoes++;
          }
        }
      }
    }
  }
  // Display the number of potatoes and carrots ready to be harvested
  mvwprintw(dynWin, 1, 1, "Potatoes ready: %d", numOfPotatoes);
  mvwprintw(dynWin, 2, 1, "Carrots ready: %d", numOfCarrots);
  mvwprintw(dynWin, 3, 1, "C: Harvest carrots");
  mvwprintw(dynWin, 4, 1, "P: Harvest potatoes");
  // Refresh dynamic window
  wrefresh(dynWin);
}

// Funtion to plant a new plant at the current position
void GameManager::plantAtCurrentPosition(string plantType) {
  // Get player coords
  int y = std::get<0>(player->getPosition());
  int x = std::get<1>(player->getPosition());
  // Based on player direction, get coord facing in front of them
  switch (player->getDirection()) {
    case Player::MoveDirection::North:  // North
      y--;
      break;
    case Player::MoveDirection::East:  // East
      x++;
      break;
    case Player::MoveDirection::South:  // South
      y++;
      break;
    case Player::MoveDirection::West:  // West
      x--;
      break;
  }
  // Iterate through plots and check which plot is the one player is facing
  for (auto i = plots.begin(); i != plots.end(); i++) {
    int currentCap = i->getCurrentCapacity();
    int topY = std::get<0>(i->getTopLeftCoord());
    int leftX = std::get<1>(i->getTopLeftCoord());
    int bottomY = topY + std::get<0>(i->getDimensions());
    int rightX = leftX + std::get<1>(i->getDimensions());
    // For the right plot, first check if player has enough items to plant
    if (y > topY && y < bottomY && x > leftX && x < rightX) {
      if (player->getPlayersInventory()->howMany(plantType) > 1) {
        // Map number to position in the plot
        int yy = currentCap / (std::get<1>(i->getDimensions()) - 2);
        int xx = currentCap % (std::get<1>(i->getDimensions()) - 2);
        // If plot is not full, plant plant
        if (currentCap != i->getMaxCapacity()) {
          // Based on the type of item or plant, create a new plant object
          if (plantType == "Carrot") {
            i->addPlant(new CarrotPlant(coord{yy, xx}));
          } else if (plantType == "Potato") {
            i->addPlant(new PotatoPlant(coord{yy, xx}));
          }
          // Update capacity
          i->setCurrentCapacity(currentCap + 1);
          // Remove item from inventory
          player->getPlayersInventory()->removeItem(plantType);
        } else {
          showFullPlotError();
        }
      } else {
        showInsufficientItemsError();
      }
    }
  }
}

// Function to move player
void GameManager::movePlayer(Player::MoveDirection direction) {
  // Get players coords
  int y = std::get<0>(player->getPosition());
  int x = std::get<1>(player->getPosition());
  // Adjust based on player direction
  if (direction == player->getDirection()) {
    switch (direction) {
      case Player::MoveDirection::North:
        y--;
        break;
      case Player::MoveDirection::East:
        x++;
        break;
      case Player::MoveDirection::South:
        y++;
        break;
      case Player::MoveDirection::West:
        x--;
        break;
    }
  }
  // Check if new position is valid
  coord newPos = coord{y, x};
  if (isValidPosition(newPos)) {
    player->setDirection(direction);
    player->setPosition(newPos);
  }
}
// Function to check if position is valid
bool GameManager::isValidPosition(coord position) {
  // Get x,y coords and check if they are within the window bounds
  int y = std::get<0>(position);
  int x = std::get<1>(position);
  int height = LINES - (LINES * 0.30) - 1;
  int width = (COLS - 2) * 0.75;
  return (x >= 1 && x < width - 1 && y >= 1 && y < height - 1);
}

// Function to show plant menu
void GameManager::showPlantMenu() {
  // Draw dynamic window
  Display::drawDynamicWindow(mainWin);
  // Close all menus and open plant menu
  setHarvestMenuOpen(false);
  setShopOpen(false);
  setPlantMenuOpen(true);
  // Labels
  mvwprintw(dynWin, 0, 1, "Plants");
  mvwprintw(dynWin, 1, 1, "C: Plant carrot");
  mvwprintw(dynWin, 2, 1, "P: Plant potato");
  // Refresh dynamic window
  wrefresh(dynWin);
}

bool GameManager::getPlantMenuOpen() {
  return plantMenuOpen;
}  // Get methods for plant menu
void GameManager::setPlantMenuOpen(bool status) {
  plantMenuOpen = status;
}  // Set methods for plant menu
bool GameManager::getHarvestMenuOpen() {
  return harvestMenuOpen;
}  // Get methods for harvest menu
void GameManager::setHarvestMenuOpen(bool status) {
  harvestMenuOpen = status;
}  // set method for harvest menu

// Function to water current plant
void GameManager::waterCurrentPlant() {
  // Get player coords
  int y = std::get<0>(player->getPosition());
  int x = std::get<1>(player->getPosition());
  // Adjust based on direction player is facing
  switch (player->getDirection()) {
    case Player::MoveDirection::North:
      y--;
      break;
    case Player::MoveDirection::East:
      x++;
      break;
    case Player::MoveDirection::South:
      y++;
      break;
    case Player::MoveDirection::West:
      x--;
      break;
  }
  // iterate over plots to find which plot they are facing
  for (auto i = plots.begin(); i != plots.end(); i++) {
    int currentCap = i->getCurrentCapacity();
    int topY = std::get<0>(i->getTopLeftCoord());
    int leftX = std::get<1>(i->getTopLeftCoord());
    int bottomY = topY + std::get<0>(i->getDimensions());
    int rightX = leftX + std::get<1>(i->getDimensions());
    // For the right plot, water all plants in the plot
    if (y > topY && y < bottomY && x > leftX && x < rightX) {
      for (int j = 0; j < i->getCurrentCapacity(); j++) {
        i->getPlants()[j]->waterPlant();
      }
    }
  }
}
// Function to advance day
void GameManager::advanceDay() {
  // increment current day
  currentDay++;
  // Iterate over plots
  for (auto i = plots.begin(); i != plots.end(); i++) {
    // Iterate over plants in plots
    for (int j = 0; j < i->getCurrentCapacity(); j++) {
      // Call advance day on plants
      i->getPlants()[j]->advanceDay();
    }
  }
}


// Function to show error when players trying to plant in full plot
void GameManager::showFullPlotError() {
  // Draw Error window
  Display::drawErrorWindow(mainWin);
  // Close all other types of errors and open specific error
  setFullPlotError(true);
  setInsufficientItemsError(false);
  setInsufficientMoneyError(false);
  setNoCarrotSellError(false);
  setNoPotatoSellError(false);
  setNoCarrotHarvestError(false);
  setNoPotatoHarvestError(false);
  // Labels
  mvwprintw(errorWin, 1, 1, "Trying to plant in full");
  mvwprintw(errorWin, 2, 1, "Plot!");
  mvwprintw(errorWin, 3, 1, "Move to different plot!");
  // Refresh Error window
  wrefresh(errorWin);
}

// Get method for fullploterror
bool GameManager::getFullPlotError() { return FullPlotError; }
// Set method for fullploterror
void GameManager::setFullPlotError(bool status) { FullPlotError = status; }

// Function to show error when players trying to plant in plot but not enough
// items
void GameManager::showInsufficientItemsError() {
  // Draw Error window
  Display::drawErrorWindow(mainWin);
  // Close all other types of errors and open specific error
  setInsufficientItemsError(true);
  setFullPlotError(false);
  setInsufficientMoneyError(false);
  setNoCarrotSellError(false);
  setNoPotatoSellError(false);
  setNoCarrotHarvestError(false);
  setNoPotatoHarvestError(false);
  // Labels
  mvwprintw(errorWin, 1, 1, "Insufficient Items to");
  mvwprintw(errorWin, 2, 1, "Plant!");
  // Refresh Error window
  wrefresh(errorWin);
}

// Get method for insufficientItemsError
bool GameManager::getInsufficientItemsError() { return InsufficientItemsError; }
// Set method for insufficientItemsError
void GameManager::setInsufficientItemsError(bool status) {
  InsufficientItemsError = status;
}

// Function to show error when players dont have enough funds to buy item
void GameManager::showInsufficientMoneyError() {
  // Draw Error window
  Display::drawErrorWindow(mainWin);
  // Close all other types of errors and open specific error
  setInsufficientMoneyError(true);
  setInsufficientItemsError(false);
  setFullPlotError(false);
  setNoCarrotSellError(false);
  setNoPotatoSellError(false);
  setNoCarrotHarvestError(false);
  setNoPotatoHarvestError(false);
  // Labels
  mvwprintw(errorWin, 1, 1, "Not Enough Money To Buy");
  mvwprintw(errorWin, 2, 1, "Item!");
  // Refresh Error window
  wrefresh(errorWin);
}

// Get method for insufficient money error
bool GameManager::getInsufficientMoneyError() { return InsufficientMoneyError; }
// Set method for insufficientMoneyError
void GameManager::setInsufficientMoneyError(bool status) {
  InsufficientMoneyError = status;
}

// Function to show error when players dont have an carrot to sell
void GameManager::showNoCarrotSellError() {
  // Draw Error window
  Display::drawErrorWindow(mainWin);
  // Close all other types of errors and open specific error
  setNoCarrotSellError(true);
  setNoPotatoSellError(false);
  setInsufficientMoneyError(true);
  setInsufficientItemsError(false);
  setFullPlotError(false);
  setNoCarrotHarvestError(false);
  setNoPotatoHarvestError(false);
  // Labels
  mvwprintw(errorWin, 1, 1, "You dont have any");
  mvwprintw(errorWin, 2, 1, "Carrots to sell!");
  // Refresh Error window
  wrefresh(errorWin);
}

// Get method for No carrots to sell
bool GameManager::getNoCarrotSellError() { return NoCarrotsToSell; }
// Set method for No carrots to sell
void GameManager::setNoCarrotSellError(bool status) {
  NoCarrotsToSell = status;
}

// Function to show error when players dont have an Potato to sell
void GameManager::showNoPotatoSellError() {
  // Draw Error window
  Display::drawErrorWindow(mainWin);
  // Close all other types of errors and open specific error
  setNoPotatoSellError(true);
  setNoCarrotSellError(false);
  setInsufficientMoneyError(true);
  setInsufficientItemsError(false);
  setFullPlotError(false);
  setNoCarrotHarvestError(false);
  setNoPotatoHarvestError(false);
  // Labels
  mvwprintw(errorWin, 1, 1, "You dont have any");
  mvwprintw(errorWin, 2, 1, "Potatoes to sell!");
  // Refresh Error window
  wrefresh(errorWin);
}

// Get method for No Potatoes to sell
bool GameManager::getNoPotatoSellError() { return NoPotatoesToSell; }
// Set method for No Potatoes to sell
void GameManager::setNoPotatoSellError(bool status) {
  NoPotatoesToSell = status;
}

// Function to show error when no potatos to harvest
void GameManager::showNoPotatoHarvestError() {
  // Draw Error window
  Display::drawErrorWindow(mainWin);
  // Close all other types of errors and open specific error
  setNoPotatoHarvestError(true);
  setNoCarrotHarvestError(false);
  setNoPotatoSellError(false);
  setNoCarrotSellError(false);
  setInsufficientMoneyError(true);
  setInsufficientItemsError(false);
  setFullPlotError(false);
  // Labels
  mvwprintw(errorWin, 1, 1, "There are no mature");
  mvwprintw(errorWin, 2, 1, "Potatoes to harvest");
  mvwprintw(errorWin, 3, 1, "in this plot!");
  // Refresh Error window
  wrefresh(errorWin);
}

// Get method for No Potatoes to harvest
bool GameManager::getNoPotatoHarvestError() { return NoPotatoesToHarvest; }
// Set method for No Potatoes to harvest
void GameManager::setNoPotatoHarvestError(bool status) {
  NoPotatoesToHarvest = status;
}

// Function to show error when no Carrots to harvest
void GameManager::showNoCarrotHarvestError() {
  // Draw Error window
  Display::drawErrorWindow(mainWin);
  // Close all other types of errors and open specific error
  setNoCarrotHarvestError(true);
  setNoPotatoHarvestError(false);
  setNoPotatoSellError(false);
  setNoCarrotSellError(false);
  setInsufficientMoneyError(true);
  setInsufficientItemsError(false);
  setFullPlotError(false);
  // Labels
  mvwprintw(errorWin, 1, 1, "There are no mature");
  mvwprintw(errorWin, 2, 1, "Carrots to harvest");
  mvwprintw(errorWin, 3, 1, "in this plot!");
  // Refresh Error window
  wrefresh(errorWin);
}

// Get method for No Potatoes to harvest
bool GameManager::getNoCarrotHarvestError() { return NoCarrotsToHarvest; }
// Set method for No Potatoes to harvest
void GameManager::setNoCarrotHarvestError(bool status) {
  NoCarrotsToHarvest = status;
}
// Function to close the program
void GameManager::cleanup() {
    //Save money to save file
    saveMoney();
    // This causes the program to return the terminal to normal mode
    // from curses mode
    endwin();
}

//Function to make a save file
void GameManager::saveMoney() {
  //Open file to put data in
  ofstream saveFile("save.dat");
    if (saveFile.is_open()) { //If save file is open, save money in it!
      saveFile << player->getMoney() << endl;
      saveFile.close();
    }
}

void GameManager::loadMoney() {
  //Open file to get data from
  ifstream saveFile("save.dat");
    if (saveFile.is_open()) { //If save file is open, load money from it!
      int money;
      saveFile >> money;
      player->setPlayersMoney(money);
      saveFile.close();
    }
}
