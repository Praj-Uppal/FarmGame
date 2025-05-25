#include"Player.h"
#include"FarmPlot.h"
#include"Allincludes.h"
#include<iostream>

using namespace std;

void test_player_constructor() {
    Player player;
    //By default, player should have 0 money.
    if (player.getMoney() != 0) {
        cout << "Default Player constructor failed; Money is not 0!" << endl;
        return;
    }
    //By Default, player should be at origin
    if (player.getPosition() != coord(0,0)) {
        cout << "Default Player constructor failed; Player not at origin!" << endl;
        return;
    }
    //Checking if inventory is assigned
    if (player.getPlayersInventory()==nullptr) {
        cout << "Default Player constructor failed; Player inventory ptr is a nullptr!" << endl;
        return;
    }
    //Checking if direction is assigned correctly to north
    if (player.getDirection()!= Player::MoveDirection::North) {
        cout << "Default Player constructor failed; Player direction is not South!" << endl;
        return;
    }
    cout << "Player constructor tests passed!" << endl;
}

void test_player_money() {
    Player player;
    player.setPlayersMoney(10); //Set player money to 10
    //Check if set
    if (player.getMoney()!= 10) {
        cout << "Player money management failed; Player money is not 10!" << endl;
        return;
    }
    player.setPlayersMoney(100); //Set player money to 100
    //Check if set
    if (player.getMoney()!= 100) {
        cout << "Player money management failed; Player money is not 100!" << endl;
        return;
    }
    cout << "Player money tests passed!" << endl; //Passed all test cases
}

void test_player_inventory() {
    Player player;
    player.setPlayersInventory(new Inventory());
    //Check if set
    if (player.getPlayersInventory()==nullptr) {
        cout << "Player inventory reassignment failed; Player inventory ptr is a nullptr!" << endl;
        return;
    }
    cout << "Player inventory tests passed!" << endl; //Passed all test cases
    return;
}

void test_player_position() {
    Player player;
    player.setPosition(coord(1,1)); //Set player position to (1,1)
    //Check if set
    if (player.getPosition()!= coord(1,1)) {
        cout << "Player position reassignment failed; Player position is not (1,1)!" << endl;
        return;
    }
    player.move(coord(2,2)); //Move player to (2,2)
    //Check if set
    if (player.getPosition()!= coord(2,2)) {
        cout << "Player move function failed; Player position is not (2,2)!" << endl;
        return;
    }
    cout << "Player position tests passed!" << endl; //Passed all test cases
    return;
}

void test_player_water() {
    Player player;
    Plant* plant = new PotatoPlant(coord(1,1)); //Create a plant at (1,1)
    player.water(plant)  ; //Water the plant
    //Check if plant is watered
    if (plant->isWatered()!= 1) {
        cout << "Player water function failed; Plant is not watered!" << endl;
        delete plant;
        return;
    }
    delete plant;
    cout << "Player water test passed!" << endl; 
}

void test_player_plant() {
    Player player;
    FarmPlot* farmplot = new FarmPlot(); //Create a farmplot
    Item* item = new Item(2, 1, "Carrot"); //Create a Carrot Item
    player.plant(item, farmplot); //Plant the Carrot
    //Check if plant is planted
    if (farmplot->getPlants()[0]->getName()!= "CarrotPlant") {
        cout << "Player plant function failed; Plant is not planted!" << endl;
        delete farmplot;
        delete item;
        return;
    }
    delete farmplot;
    delete item;
    cout << "Player plant test passed!" << endl; //Test passed
}


int main() {
    cout << "Testing Player class!" << endl;
    //Call all test functions
    test_player_constructor();
    test_player_money();
   test_player_inventory();
   test_player_position();
    test_player_water();
    test_player_plant();
    return 0;
}