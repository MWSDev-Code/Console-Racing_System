
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
  void setRotation(sf::Angle rotation);
  const sf::Sprite& getSprite() const;
  sf::Vector2f getPosition() const;
  int getLives() const;
  bool isActive() const;

 private:
  sf::Texture carTexture;
  sf::Sprite carsprite;
  sf::Image Track_Mask;
  int lives = 3;
  bool active = true;
  bool offTrack = false;
  float speed = 0.0f;
  const float acceleration = 150.0f;
  const float max_speed = 350.0f;
  const float braking = 300.0f;
  const float drag = 60.0f;
  const float turn_speed = 120.0f;
};
