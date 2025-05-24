#include"Plant.h"
#include"Item.h"
#include"FarmPlot.h"
#include "Inventory.h"
#include"PotatoPlant.h"
#include"CarrotPlant.h"
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <tuple>
typedef tuple<int, int> coord;

using namespace std;
class Player {
 protected:
  // Player attributes including position, facing direction, player inventory
  // and thier money.
  coord position;
  int direction;
  Inventory* playersInventory;
  int money;

 public:
  // Player constructor
  Player();

  //Declare Get methods for variables
  coord getPosition() const;
  int getDirection() const;
  Inventory* getPlayersInventory() const;
  int getMoney() const;

  //Declare set methods for attributes
  void setPosition(coord newpos);
  void setDirection(int dir);
  void setPlayersInventory(Inventory* newinv);
  void setPlayersMoney(int newmoney);

  // Function to move player
  void move(coord newPositon);
  
    //Function for player to water plant (Plants yet to implement)
  void water(Plant* plant1);

  /*  //Function for player to feed animals
    void feed(*Animal animal1)
  */

  // Function for players to gather an entity
  Item gather(Entity* E1);

  //Function for planting a new plant into the farmplot
   void plant(Item* item, FarmPlot* farmplot);


};

#endif
