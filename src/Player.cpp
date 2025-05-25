#include "Player.h"

#include <ncurses.h>

coord origin = {0, 0};

// Define default constructor to spawn player at origin facing North, with no
// money. Also intialize player inventory.
Player::Player()
    : position(origin),
      prevPosition(origin),
      direction(MoveDirection::North),
      playersInventory(new Inventory()),
      money(0) {};

// Define Destructor
// Player::~Player() {
// delete playersInventory;
// }  // Just need to delete inventory pointer only since dynamically allocated

// Define get methods
coord Player::getPosition() const { return position; }
coord Player::getPrevPosition() const { return prevPosition; }
Player::MoveDirection Player::getDirection() const { return direction; }
Inventory* Player::getPlayersInventory() const { return playersInventory; }
int Player::getMoney() const { return money; }

// Define set Methods
void Player::setPosition(coord newpos) {
  prevPosition = position;
  position = newpos;
}
void Player::setDirection(Player::MoveDirection dir) { direction = dir; }
void Player::setPlayersInventory(Inventory* newinv) {
  delete playersInventory;    // Deleting the old inventory pointer
  playersInventory = newinv;  // Assigning the new inventory pointer
}
void Player::setPlayersMoney(int newmoney) { money = newmoney; }

// Define move function
void Player::move(coord newpos) { setPosition(newpos); }

// Define water Function
void Player::water(Plant* plant1) { plant1->waterPlant(); }

// Define Planting function:
void Player::plant(Item* item, FarmPlot* farmplot) {
  coord playerposition = this->position;
  vector<Plant*> plantsvector = farmplot->getPlants();
  // Check if a plant is already planted at player location. If so, just return.
  for (int i = 0; i < plantsvector.size(); i++) {
    if (plantsvector.at(i)->getPosistion() == playerposition) {
      return;
    }
  }

  // Define general plant pointer
  Plant* p1;
  if (item->getName() == "Potato") {
    // If item is potato, let p1 be a new potato plant
    p1 = new PotatoPlant(this->position);
  } else if (item->getName() == "Carrot") {
    // if item is carrot, let p1 be a new carrot plant
    p1 = new CarrotPlant(this->position);
  }
  // add new plant to the farmplot;
  farmplot->addPlant(p1);
}
