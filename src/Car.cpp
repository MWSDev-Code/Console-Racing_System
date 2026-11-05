#include "Car.h"
#include<algorithm>

Car::Car() : carsprite(carTexture){}

bool Car::load(){
    if(!carTexture.loadFromFile("assets/cars/Car1.png")){
        return false;
    }
    carsprite.setTexture(carTexture, true);
    carsprite.setScale({0.12f, 0.12f});
    carsprite.setPosition({545.0f, 25.0f});
    carsprite.setRotation(sf::degrees(90));

    return true;
}

void Car::update(float deltaTime){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){   //  We use max here to have the max speed at 0
            speed = std::max(0.0f, speed - braking * deltaTime);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            speed = std::min(max_speed, speed + acceleration * deltaTime);  // We ise min because we want the maximum speed is 450f.
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
         {

             carsprite.rotate(sf::degrees(-turn_speed * deltaTime));
         }

         else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            carsprite.rotate(sf::degrees(turn_speed * deltaTime));
         }
         else {
            speed = std::max(0.0f, speed - drag * deltaTime);   //IF neither is pressed, the car speed gradually decreases 
        }                                                       //We use max beacuse we want to stop it not to reverse it

        carsprite.move({speed * deltaTime, 0.0f});
}

const sf::Sprite& Car::getSprite() const{
    return carsprite;
}
