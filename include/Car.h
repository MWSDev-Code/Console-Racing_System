#pragma once

#include <SFML/Graphics.hpp>

class Car {
 public:
  Car();
  bool load();
  void update(float deltaTime);
  const sf::Sprite& getSprite() const;
  sf::Vector2f getPosition() const;

 private:
  sf::Texture carTexture;
  sf::Sprite carsprite;
  sf::Image Track_Mask;
  float speed = 0.0f;  // Keep the speed between frames (pixels per second).
  const float acceleration = 180.0f;  // Pixels per second gained each second.
  const float max_speed = 450.0f;
  const float braking = 300.0f;  // We use const to keep it a fixed value.
  const float drag = 60.0f;  // Drag means the car gradually slows down when we
                             // are not pressing anything.
  const float turn_speed = 120.0f;
};
