#include "checkpoint.h"

Checkpoint::Checkpoint(sf::Vector2f position, sf::Vector2f size)
    : bounds(position, size) {}

bool Checkpoint::contains(sf::Vector2f carPosition) const {
  return bounds.contains(carPosition);
}