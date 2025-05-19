#include "Player.h"

coord origin = {0, 0};

// Define default constructor to spawn player at origin facing south, with no
// money. Also intialize player inventory.
Player::Player()
    : position(origin),
      direction(2),
      playersInventory(new Inventory()),
      money(0) {};

// Define get methods
coord Player::getposition() const { return position; }
int Player::getDirection() const { return direction; }
Inventory* Player::getPlayersInventory() const { return playersInventory; }
int Player::getMoney() const { return money; }

// Define set Methods
void Player::setPosition(coord newpos) { position = newpos; }
void Player::setDirection(int dir) { direction = dir; }
void Player::setPlayersInventory(Inventory* newinv) {
  delete playersInventory;
  playersInventory = newinv;
}
void Player::setPlayersMoney(int newmoney) {money = newmoney;}

//Define move function
void Player::move(coord newpos) {setPosition(newpos);}

//Define gather function (I dont actually know what this does)
