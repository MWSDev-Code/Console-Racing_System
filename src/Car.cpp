#include "Car.h"

#include <algorithm>
#include <cmath>

Car::Car() : carsprite(carTexture) {}

bool Car::load() {
  if (!carTexture.loadFromFile("assets/cars/Car1.png")) {
    return false;
  }

  carsprite.setTexture(carTexture, true);
  carsprite.setScale({0.12f, 0.12f});
  sf::FloatRect carBounds = carsprite.getLocalBounds();

  carsprite.setOrigin({carBounds.position.x + carBounds.size.x / 2.0f,
                       carBounds.position.y + carBounds.size.y / 2.0f});
  carsprite.setPosition({500.0f, 530.0f});
  carsprite.setRotation(sf::degrees(90));

  return true;
}
void Car::update(float deltaTime) {
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Key::S)) {  //  We use max here to have the max speed at
                                    //  0
    speed = std::max(0.0f, speed - braking * deltaTime);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
    speed = std::min(
        max_speed,
        speed + acceleration * deltaTime);  // We ise min because we want the
                                            // maximum speed is 450f.
  } else {
    speed = std::max(
        0.0f, speed - drag * deltaTime);  // IF neither is pressed, the car
                                          // speed gradually decreases
  }  // We use max beacuse we want to stop it not to reverse it

  if (speed > 0.0f) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
      carsprite.rotate(sf::degrees(-turn_speed * deltaTime));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
      carsprite.rotate(sf::degrees(turn_speed * deltaTime));
    }
  }

  float angle = carsprite.getRotation().asRadians() - 3.14159265f / 2.0f;

  float moveX = std::cos(angle) * speed * deltaTime;
  float moveY = std::sin(angle) * speed * deltaTime;

  carsprite.move({moveX, moveY});

  sf::FloatRect bounds = carsprite.getGlobalBounds();

  if (bounds.position.x < 0.0f) {
    carsprite.move({-bounds.position.x, 0.0f});
  }

  if (bounds.position.y < 0.0f) {
    carsprite.move({0.0f, -bounds.position.y});
  }

  if (bounds.position.x + bounds.size.x > 1280.0f) {
    float extra = bounds.position.x + bounds.size.x - 1280.0f;

    carsprite.move({-extra, 0.0f});
  }

  if (bounds.position.y + bounds.size.y > 720.0f) {
    float extra = bounds.position.y + bounds.size.y - 720.0f;

    carsprite.move({0.0f, -extra});
  }
}

const sf::Sprite& Car::getSprite() const { return carsprite; }