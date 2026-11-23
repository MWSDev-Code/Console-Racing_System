
#include "Car.h"
#include <algorithm>
#include <cmath>
#include <string>

namespace {
sf::IntRect visibleBounds(
    const sf::Image&
        image) {  // IntRect is the return type for rectangles(by coordinates).
                  // Image is the SFML Image and we used & for pass by reference
  const auto size =
      image.getSize();  // It gets the size of the image(auto means the compiler
                        // determines the variable type)
  sf::Vector2u topLeft = size;  // thhs gets the top left corner
  sf::Vector2u bottomRight{};   // This gets the bottom right of the image
  for (unsigned int y = 0; y < size.y; ++y) {    // This goes through the rows
    for (unsigned int x = 0; x < size.x; ++x) {  // This goes through the
                                                 // columns
      if (image.getPixel({x, y}).a >
          16) {  // image.get pixel gets the color of the pixel
        topLeft.x =
            std::min(topLeft.x, x);  // min beacuse it is from the top left and
                                     // we need the minimum value
        topLeft.y = std::min(topLeft.y,
                             y);  // max beacuse it is on the bottom right and
                                  // we need the maximum value of the pixel.
        bottomRight.x = std::max(bottomRight.x, x + 1);
        bottomRight.y = std::max(bottomRight.y, y + 1);
      }
    }
  }
  if (bottomRight.x == 0) {
    return {};
  }
  return {
      sf::Vector2i(topLeft),
      sf::Vector2i(bottomRight - topLeft)};  // we minus beacuse we want the
                                             // height and width of the pixel.
}
}  // namespace

Car::Car()
    : carsprite(carTexture) {
}  // texture makes the iamge editable to move an resize

bool Car::load(int selectedCar) {  // This loads the car
  int carIndex;

  if (selectedCar >= 0 && selectedCar < 4) {
    carIndex = selectedCar;
  } else {
    carIndex = 0;
  }  // this loads the selected car
  const std::string texturePath =
      "assets/cars/selection/car" + std::to_string(carIndex + 1) + ".png";   
  sf::Image image;
  if (!image.loadFromFile(texturePath)) {
    return false;
  }
  const auto bounds = visibleBounds(image);
  if (bounds.size.y == 0 || !carTexture.loadFromImage(image, false, bounds)) {    //It loads the visible pixel
    return false;
  }
  const float redCarLength = 85.0f;  //Resize the red car because it is big.
  const float trackCarLength = 90.0f;
  const float scale =
      (carIndex == 0 ? redCarLength : trackCarLength) / bounds.size.y;
  carTexture.setSmooth(true);  //When resized, it smooths the image.
  if (!Track_Mask.loadFromFile("assets/track/Track_Mask.png")) {
    return false;
  }

  carsprite.setTexture(carTexture, true);  //Sprtites the texture to make it move and true means newly assigned texture
  carsprite.setScale({scale, scale});   //This resize/scale the image(cars) to the same szie
  sf::FloatRect carBounds = carsprite.getLocalBounds();

  carsprite.setOrigin({carBounds.position.x + carBounds.size.x / 2.0f,    /* We did this to get the coordinates of the center of each sprite(car) for real rotation */
                       carBounds.position.y + carBounds.size.y / 2.0f});
  carsprite.setPosition({500.0f, 530.0f});   // This sets the sprite(CAR) origin at the center.
  carsprite.setRotation(sf::degrees(90));    //Car is in vertical position(ORIGINALLY) and this rotates it.

  return true;
}

void Car::update(float deltaTime, const CarControls& controls) {
  if (sf::Keyboard::isKeyPressed(
          controls.brake)) {  //  We use max here to have the max speed at
                              //  0
    speed = std::max(0.0f, speed - braking * deltaTime);
  } else if (sf::Keyboard::isKeyPressed(controls.accelerate)) {
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
    if (sf::Keyboard::isKeyPressed(controls.left)) {
      carsprite.rotate(sf::degrees(-turn_speed * deltaTime));  //It turns the car anticlockwise(with -)
    }

    if (sf::Keyboard::isKeyPressed(controls.right)) {
      carsprite.rotate(sf::degrees(turn_speed * deltaTime));  //It turns the car clockwise
    }
  }

  float angle = carsprite.getRotation().asRadians() - 3.14159265f / 2.0f; //This gets the current rotation, convert in to radians
                                                      //we subtract 90 degree beacuse we make the upward car look original
  float moveX = std::cos(angle) * speed * deltaTime;  //cos makes the car move horizontal
  float moveY = std::sin(angle) * speed * deltaTime;  //sin makes the car vertical

  carsprite.move({moveX, moveY});  //It moves acccording to the given coordinates.

  sf::FloatRect bounds = carsprite.getGlobalBounds();  //Bounds get the cars bounding rectangle

  if (bounds.position.x < 0.0f) {     //this checks if the car has passed the left edge of the game(bounds.position.x gives the x-coordinate of the car window  )
    carsprite.move({-bounds.position.x, 0.0f});
  }

  if (bounds.position.y < 0.0f) {     //this checks if the car has passed the top edge of the game(bounds.position.y gives the y-coordinate of the car window  )
    carsprite.move({0.0f, -bounds.position.y}); //move actually moves the car away by the value
  }

  if (bounds.position.x + bounds.size.x > 1280.0f) {     //this checks if the car has passed the right edge of the game(bounds.position.x gives the x-coordinate of the car window  )
    float extra = bounds.position.x + bounds.size.x - 1280.0f;  //position.x + size.x(width of the car sprite) adds to give the total value.

    carsprite.move({-extra, 0.0f});
  }

  if (bounds.position.y + bounds.size.y > 720.0f) {
    float extra = bounds.position.y + bounds.size.y - 720.0f;

    carsprite.move({0.0f, -extra});
  }
  sf::Vector2f carPosition = carsprite.getPosition();  //This gets the position of the car sprite(we set the origin to the center of the car)

  sf::Vector2u maskSize = Track_Mask.getSize();   //This gets the width and height of the track_Mask

  unsigned int maskX =  //This part actually calculates the coordinates of the pixel IF SIZE OF THE TRACK AND MASK DIFFER
      static_cast<unsigned int>(carPosition.x * maskSize.x / 1280.0f);

  unsigned int maskY =
      static_cast<unsigned int>(carPosition.y * maskSize.y / 720.0f);

  if (maskX < maskSize.x && maskY < maskSize.y) {   //A check to see if the pixel exists in the size of the track mask
    sf::Color pixel = Track_Mask.getPixel({maskX, maskY});  //This gets the color of the pixel.

    if (pixel.r < 128) {    //For black, red is 0, so the condition becomes true and the car slows down.
      speed = std::min(speed, 40.0f);
    }
  }
}

void Car::setPosition(sf::Vector2f position) {
  carsprite.setPosition(position);
}

sf::Vector2f Car::getPosition() const { return carsprite.getPosition(); }

const sf::Sprite& Car::getSprite() const { return carsprite; }
