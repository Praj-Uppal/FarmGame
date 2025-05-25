#include "Animal.h"

// Define constructor
Animal::Animal(int _growthRequired, int _careRequired, string name) {
  growthStage = 0;
  growthRequired = _growthRequired;
  this->name = name;
  caredForDays = 0;
  careRequired = _careRequired;
}

// Get method for position
coord Animal::getPosition() const { return position; }
// Set method for position
void Animal::setPosition(coord value) { position = value; }

// Set Methods for feed
void Animal::feed() { fed = true; }
void Animal::unfeed() { fed = false; }
// Get methods for feed, returns a bool
bool Animal::isFed() const { return fed; }