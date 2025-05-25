#include <iostream>

#include "Inventory.h"
#include "Item.h"
using namespace std;

void inventory_additems_test() {
  // Create a new inventory;
  Inventory inv;
  // Item definitions
  Item* Potato = new Item(4, 2, "Potato");
  Item* Potato2 = new Item(4, 2, "Potato");
  Item* Carrot = new Item(2, 1, "Carrot");
  // Add 2 potato to inventory
  inv.addItem(Potato);
  // Check if added
  if (inv.howMany("Potato") != 1) {
    cout << "Inventory Item Addition failed at first check! Overloaded "
            "function not working!"
         << endl;
    return;
  }
  // Add 4 more potato
  inv.addItem(Potato2, 4);
  // Check if added
  if (inv.howMany("Potato") != 5) {
    cout << "Inventory Item Addition failed at second check!" << endl;
    return;
  }
  // Add 3 carrots
  inv.addItem(Carrot, 3);
  // Check if added
  if (inv.howMany("Carrot") != 3) {
    cout << "Inventory Item Addition failed at third check! 3 carrots were not "
            "found!"
         << endl;
    return;
  }

  cout << "All Item Addition tests passed!" << endl;
  return;
}

void inventory_IteratorTests() {
  // Create a new inventory
  Inventory inv;
  // Item Definitions
  Item* Potato1 = new Item(4, 2, "Potato");
  Item* Carrot2 = new Item(2, 1, "Carrot");
  // Add a few items
  inv.addItem(Potato1, 2);
  inv.addItem(Carrot2, 3);

  // Check if Iterators work as intended
  if (inv.begin()->first != "Carrot") {
    cout << "Begining Iterator failed!" << endl;
    return;
  }
  //Since end is not a valid element, we have to go one before last
  auto index =  inv.end();
  index--;
  if (index->first != "Potato") {
    cout << "Ending iterator failed!" << endl;
    return;
  }
  cout << "All iterator tests passed!" << endl;
  return;
}

void Inventory_removeItemtests() {
  Inventory inv;
  // Item defeinitions
  Item* Potato = new Item(4, 2, "Potato");
  Item* Carrot = new Item(2, 1, "Carrot");
  // Add items
  inv.addItem(Potato, 2);
  inv.addItem(Carrot, 3);
  // Remove Potatoes
  inv.removeItem("Potato", 2);
  // Check if item was removed
  if (inv.howMany("Potato") != 0) {
    cout << "Remove Item failed first test! Removal of 2 Potatoes failed!"
         << endl;
    return;
  }
  inv.removeItem("Carrot");
  // Check if that item count was decreased by 1
  if (inv.howMany("Carrot") != 2) {
    cout << "Remove item failed second test! Removal of 1 Carrot failed!"
         << endl;
  }
  cout << "All Remove Items tests passed!" << endl;
  return;
}

void setInventoryMap_tests() {
  // Create inventory
  Inventory inv;
  // Create new map
  map<string, pair<Item*, int>> inventory2;
  // Set inventory map to inventory 2
  inv.setInventorymap(inventory2);
  // Check
  if (inv.getInventorymap() != inventory2) {
    cout << "Set Inventory Map test Failed!" << endl;
  }

  cout << "Inventory Map Tests passed!" << endl;
}

void printInventory_Tests() {
  // Create inventory tests
  Inventory inv;
  // Item definitions
  Item* Potato = new Item(4, 2, "Potato");
  Item* Carrot = new Item(2, 1, "Carrot");
  // Add items
  inv.addItem(Potato, 2);
  inv.addItem(Carrot, 3);

  // Print Items (Must be verified visually)
  inv.printInventory();
}

int main(void) {
// Run tests
  setInventoryMap_tests();
 inventory_additems_test();
  inventory_IteratorTests();
  Inventory_removeItemtests();
  printInventory_Tests();
  return 0;
}
