#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <SFML/Graphics.hpp>

class Checkpoint {
 private:
  sf::FloatRect bounds;

 public:
  Checkpoint(sf::Vector2f position, sf::Vector2f size);

  bool contains(sf::Vector2f carPosition) const;
};

#endif