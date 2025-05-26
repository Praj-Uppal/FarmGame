#ifndef COW_H
#define COW_H

#include <vector>

#include "Allincludes.h"
#include "Animal.h"

/**
 * The Cow class represents a cow entity being raised in the game world. The cow
 * grows and evolves over a set number of days when fed, before reaching
 * maturity at which point it can be slaughtered for items or used for
 * reproduction (WIP). Upon slaughtering, the cow deposits an according number
 * of beef into the players inventory.
 */
class Cow : public Animal {
 public:
  // Declare Constructor
  Cow(coord position);

  // Declare raise, and slaughter functions
  void raise() override;

  // Produces 3x Beef upon successful slaughter, or nothing if not mature.
  std::vector<Item*> slaughter() override;
};

#endif