
#include "Car.h"

#include <algorithm>
#include <cmath>
#include <string>

namespace {
bool isOnTrack(const sf::Image& trackMask, const sf::Sprite& car) {
  const auto maskSize = trackMask.getSize();
  const sf::FloatRect bounds = car.getLocalBounds();
  const sf::Transform transform = car.getTransform();
  const sf::Vector2f samplePoints[5] = {
      transform.transformPoint(bounds.position + bounds.size / 2.0f),
      transform.transformPoint(bounds.position + bounds.size * 0.2f),
      transform.transformPoint(bounds.position +
                               sf::Vector2f(bounds.size.x * 0.8f,
                                            bounds.size.y * 0.2f)),
      transform.transformPoint(bounds.position +
                               sf::Vector2f(bounds.size.x * 0.2f,
                                            bounds.size.y * 0.8f)),
      transform.transformPoint(bounds.position + bounds.size * 0.8f)};

  for (int i = 0; i < 5; ++i) {
    if (samplePoints[i].x < 0.0f || samplePoints[i].y < 0.0f ||
        samplePoints[i].x >= 1280.0f || samplePoints[i].y >= 720.0f) {
      return false;
    }

    const unsigned int maskX =
        static_cast<unsigned int>(samplePoints[i].x * maskSize.x / 1280.0f);
    const unsigned int maskY =
        static_cast<unsigned int>(samplePoints[i].y * maskSize.y / 720.0f);
    if (trackMask.getPixel({maskX, maskY}).r < 128) {
      return false;
    }
  }
  return true;
}

sf::IntRect visibleBounds(const sf::Image& image) {
  const auto size = image.getSize();
  sf::Vector2u topLeft = size;
  sf::Vector2u bottomRight{};
  for (unsigned int y = 0; y < size.y; ++y) {
    for (unsigned int x = 0; x < size.x; ++x) {
      if (image.getPixel({x, y}).a > 16) {
        topLeft.x = std::min(topLeft.x, x);
        topLeft.y = std::min(topLeft.y, y);
        bottomRight.x = std::max(bottomRight.x, x + 1);
        bottomRight.y = std::max(bottomRight.y, y + 1);
      }
    }
  }
  if (bottomRight.x == 0) {
    return {};
  }
  return {sf::Vector2i(topLeft), sf::Vector2i(bottomRight - topLeft)};
}
}  // namespace

Car::Car() : carsprite(carTexture) {}

bool Car::load(int selectedCar) {
  const int carIndex = selectedCar >= 0 && selectedCar < 4 ? selectedCar : 0;
  const std::string texturePath =
      "assets/cars/selection/car" + std::to_string(carIndex + 1) + ".png";
  sf::Image image;
  if (!image.loadFromFile(texturePath)) {
    return false;
  }
  const auto bounds = visibleBounds(image);
  if (bounds.size.y == 0 || !carTexture.loadFromImage(image, false, bounds)) {
    return false;
  }
  constexpr float redCarLength = 85.0f;
  constexpr float trackCarLength = 90.0f;
  const float scale =
      (carIndex == 0 ? redCarLength : trackCarLength) / bounds.size.y;
  carTexture.setSmooth(true);
  if (!Track_Mask.loadFromFile("assets/track/Track_Mask.png")) {
    return false;
  }

  carsprite.setTexture(carTexture, true);
  carsprite.setScale({scale, scale});
  sf::FloatRect carBounds = carsprite.getLocalBounds();

  carsprite.setOrigin({carBounds.position.x + carBounds.size.x / 2.0f,
                       carBounds.position.y + carBounds.size.y / 2.0f});
  carsprite.setPosition({500.0f, 530.0f});
  carsprite.setRotation(sf::degrees(90));

  return true;
}

void Car::update(float deltaTime, const CarControls& controls) {
  if (!active) {
    return;
  }

  if (sf::Keyboard::isKeyPressed(controls.brake)) {
    speed = std::max(0.0f, speed - braking * deltaTime);
  } else if (sf::Keyboard::isKeyPressed(controls.accelerate)) {
    speed = std::min(
        max_speed,
        speed + acceleration * deltaTime);
  } else {
    speed = std::max(
        0.0f, speed - drag * deltaTime);
  }

  if (speed > 0.0f) {
    if (sf::Keyboard::isKeyPressed(controls.left)) {
      carsprite.rotate(sf::degrees(-turn_speed * deltaTime));
    }

    if (sf::Keyboard::isKeyPressed(controls.right)) {
      carsprite.rotate(sf::degrees(turn_speed * deltaTime));
    }
  }

  const sf::Vector2f oldPosition = carsprite.getPosition();
  const float angle = carsprite.getRotation().asRadians() - 3.14159265f / 2.0f;

  float moveX = std::cos(angle) * speed * deltaTime;
  float moveY = std::sin(angle) * speed * deltaTime;

  carsprite.move({moveX, moveY});

  if (!isOnTrack(Track_Mask, carsprite)) {
    carsprite.setPosition(oldPosition);
    speed = 0.0f;
    if (!offTrack) {
      --lives;
      offTrack = true;
      if (lives == 0) {
        active = false;
      }
    }
  } else {
    offTrack = false;
  }
}

void Car::setPosition(sf::Vector2f position) {
  carsprite.setPosition(position);
}

void Car::setRotation(sf::Angle rotation) { carsprite.setRotation(rotation); }

sf::Vector2f Car::getPosition() const { return carsprite.getPosition(); }

const sf::Sprite& Car::getSprite() const { return carsprite; }

int Car::getLives() const { return lives; }

bool Car::isActive() const { return active; }
