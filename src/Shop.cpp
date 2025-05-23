#include "Shop.h"

// Define general function buy an item
bool Shop::buyItem(Item* item, int qty, Player* player) {
  // Define a variable to represent players money
  int playermon = player->getMoney();
  // Define the cost of the transaction
  int cost = qty * item->getBuyCost();

  // Check if player money more than cost
  if (playermon >= cost) {
    // if so, then subtract from players money and add item to thier inventory
    player->setPlayersMoney(playermon - cost);
    player->getPlayersInventory()->addItem(item, qty);
    return 1;
  } else {
    return 0;
  }
}

// Function to buy carrots
bool Shop::buyCarrot(int qty, Player* player) {return buyItem(Carrot, qty, player); }

// Function to buy potatos
bool Shop::buyPotato(int qty, Player* player) {return buyItem(Potato, qty, player); }

// function to buy cow cattle
bool Shop::buyCow(int qty, Player* player) {return buyItem(cattle, qty, player); }

// Define general function to sell an item
bool Shop::sellItem(Item* item, int qty, Player* player) {
  // Define sell price of item, potential revenue, and player money
  int sellPrice = item->getSellCost();
  int revenue = sellPrice * qty;
  int playermon = player->getMoney();

  // Check if player has enough of the item to make the sale
  if (player->getPlayersInventory()->howMany(item->getName()) >= qty) {
    // If so, remove the quantity sold from player inventory
    player->getPlayersInventory()->removeItem(item->getName(), qty);
    // Add the revenue to players money
    player->setPlayersMoney(playermon + revenue);
    return 1;
  } else {
    return 0;
  }
}

// Function to sell entire player inventory

void Shop::sellInventory(Player* player) {
  // Define Players inventory
  Inventory* inv = player->getPlayersInventory();

  // Define a vector which will store a list of items and thier names.
  vector<pair<string, Item*>> itemlist;
  // iterate over player inventory and populate the above vector
  for (auto index = inv->begin(); index != inv->end(); index++) {
    itemlist.push_back({index->first, index->second.first});
  }

  // Iterate over Item vector, and wherever item Quantity is above 0, use sell
  // function
  for (int index = 0; index < itemlist.size(); index++) {
    int itemQty = inv->howMany(itemlist.at(index).first);
    if (itemQty > 0) {
      sellItem(itemlist.at(index).second, itemQty, player);
    }
  }
}
