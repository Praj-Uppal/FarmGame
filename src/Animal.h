#ifndef ANIMAL_H
#define ANIMAL_H

#include <vector>

#include "Allincludes.h"
#include "Entity.h"

class Item;

/**
 * Analogous to the Plant class, the Animal class manages the life cycle and
 * evolution of livestock. It expands on the behaviours provided by the entity
 * class and contains attributes such as the animal’s growth stage, feeding
 * status, and slaughtering status. The Animal class tracks and controls the
 * animals progress which depends on if they have been fed. Once an animal is
 * fully raised, it can be slaughtered, which returns a corresponding item into
 * the player’s inventory, or used for reproduction (this is a future feature
 * and is not planned for the initial release but may be implemented if time
 * permits).
 */
class Animal : public Entity {
 protected:
  // Define attributes
  coord position;
  bool fed;

 public:
  // Declare constructor and destructor
  Animal(int growthRequired, int careRequired, string name);

  // Virtual function which has to be implemented in the individual animals
  // classes as different animals have different evolution requirements
  virtual void raise() = 0;

  // Harvests animal and adds to user’s inventory, removes itself from Penn
  // animals array. As the type of item added to the users inventory, the
  // quantity, and slaughter conditions vary, this is a virtual function
  virtual std::vector<Item*> slaughter() = 0;

  // Whether animal has been fed, returns a bool
  bool isFed() const;
  // Set methods for feed
  void feed();
  void unfeed();

  // Set and get methods for position
  coord getPosition() const;
  void setPosition(coord value);
};

#endif