#include "Inventory.h"

using namespace std;
// Default constructor. To reiterate from header file, maps are automaticlly initialised and there are no other variables to initalise.
Inventory::Inventory() {};

int Inventory::howMany(string itemName)
{
    // Tries to locate item in the inventory map and return its quantity.
    try
    {
        // If item is in inventory, reuturns the second value of the pair which was its quantity.
        return inventoryMap.at(itemName).second;
    }
    // If item not found in inventory, at function throws an out_of_range exception error, which is caught.
    catch (const out_of_range *e)
    {
        // Since item was not in inventory, return 0 for the quantity.
        return 0;
    }
}

void Inventory::addItem(Item *itemtoadd, int quanity)
{
    string itemName = itemtoadd->getName();
    // if item is found in inventory, increments the number of it in the inventory by the quantity to be added.
    if (howMany(itemName) > 0)
    {
        inventoryMap.at(itemName).second += quanity;
        return;
    }
    else
    { // This is the case where the item is not found in the inventory
        // If the item is not pre-existing, inserts a new key and value into the map for that item.
        pair<Item *, int> itemEntry = {itemtoadd, quanity}; // Defines the item entry with the item and quantity
        inventoryMap.insert({itemName, itemEntry});         // inserts it into map
        return;
    }
}

void Inventory::removeItem(string itemName, int quantity)
{
    // Check if item is inventory with how many function
    if (howMany(itemName) > 0)
    {
        // The case where the item is in the inventory, it subtracts the quantity to remove
        inventoryMap.at(itemName).second -= quantity;
        if (howMany(itemName) < 0)
        { // If quantity becomes negative, sets it to 0
            inventoryMap.at(itemName).second = 0;
            return;
        }
    }
    else
    { // In the case where item does not exist, there is nothing to remove.
        return;
    }
}

void Inventory::printInventory()
{
    // Iterate over map entries until index (or rather memory address) reaches the end.
    for (auto index = inventoryMap.begin(); index != inventoryMap.end(); index++)
    {
        // Prints the values stored at the memory address index is pointing to. 
        // Since the second entry in itself is a pair, the data needs to be printed by accessing first element (second.first) and then second element (second.second)
        cout << index->first << " " << index->second.first << " " << index->second.second << endl;
    }
    return;
}
