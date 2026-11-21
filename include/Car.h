
#pragma once

#include <SFML/Graphics.hpp>

struct CarControls {
  sf::Keyboard::Key accelerate;
  sf::Keyboard::Key brake;
  sf::Keyboard::Key left;
  sf::Keyboard::Key right;
};

class Car {
 public:
  Car();
  bool load(int selectedCar = -1);
  void update(float deltaTime, const CarControls& controls);
  void setPosition(sf::Vector2f position);
  const sf::Sprite& getSprite() const;
  sf::Vector2f getPosition() const;

 private:
  sf::Texture carTexture;
  sf::Sprite carsprite;
  sf::Image Track_Mask;
  float speed = 0.0f;  // Keep the speed between frames (pixels per second).
  const float acceleration = 50.0f;  // Pixels per second gained each second.
  const float max_speed = 250.0f;
  const float braking = 300.0f;  // We use const to keep it a fixed value.
  const float drag = 60.0f;  // Drag means the car gradually slows down when we
                             // are not pressing anything.
  const float turn_speed = 120.0f;
};
