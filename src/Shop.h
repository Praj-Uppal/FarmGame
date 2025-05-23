#include "Allincludes.h"
#include"Item.h"
#include"Inventory.h"
#include"Player.h"
#ifndef SHOP_H
#define SHOP_H

class Shop {
 private:
  // Define prices for different items (currently constant)
  int carrotPrice = 1;
  int potatoPrice = 2;
  int cowPrice = 4;

 public:
  // Declare purchasing functions for player to buy from
  bool buyItem(Item* item,int qty, Player* player);
  bool buyCarrot(int qty, Player* player);
  bool buyPotato(int qty, Player* player);
  bool buyCow(int qty, Player* player);

  //Function to sell a single item
  bool sellItem(Item* item, int qty, Player* player);

  // Function to sell all items in players inventory and convert to money
  void sellInventory(Player* player);

  // Displays show in the "dynamic window space"
  void displayShop();
};

#endif
