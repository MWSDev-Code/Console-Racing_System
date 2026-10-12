#include<SFML/Graphics.hpp>
#include<iostream>
#include<algorithm>
int main(){

    sf::RenderWindow window(sf::VideoMode({1280,720}),"Console Racing");  //This means add a SFML window of this size


    sf::Texture trackTexture; //Create a texture for thetrack image kind of a variable to hold the image in the program for every frame.

    if(!trackTexture.loadFromFile("assets/track/Track1.png")){ //It loads the track image from the folder and also if there is a issue it stops the program.
        return 1;
    }
    sf::Sprite tracksprite(trackTexture);

    tracksprite.setScale(
    {
        1280.0f / trackTexture.getSize().x,
        720.0f / trackTexture.getSize().y
    }
    );
    sf::Texture carTexture;
    if(!carTexture.loadFromFile("assets/cars/Car1.png")){
        return 1;
    }
    sf::Sprite carsprite(carTexture);
    carsprite.setScale({0.12f, 0.12f});
    carsprite.setPosition({545.0f, 25.0f});
    carsprite.setRotation(sf::degrees(90));

    float speed = 0.0f; // Keep the speed between frames (pixels per second).
    const float acceleration = 180.0f; // Pixels per second gained each second.
    const float max_speed = 450.0f;
    const float braking = 300.0f;  // We use const to keep it a fixed value.
    const float drag = 60.0f;  //Drag means the car gradually slows down when we are not pressing anything.
    const float turn_speed = 120.0f;
    sf::Clock frameClock;   //It is kind of a stopwatch.              / Thing is we use this clock to measure the time from 1 frame to another  /

//Main Game Loop
    while(window.isOpen()){
        // Limit long frames so a pause does not cause a large movement jump.      Delta is actually the frame to frame time in seconds       We could also have use setframe limit but this approcah is better
        const float deltaTime = std::min(frameClock.restart().asSeconds(), 0.05f);  //We use min here to have the minimum delta time
                                                                                    //if the frame second gets higher, it only takes 0.05f
        while(const std::optional event = window.pollEvent()){

            if(event->is<sf::Event::Closed>() ){ //Close the Window if X is pressed.
                window.close();
            }

        }
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
        window.clear(); //It clears the previous frame
        window.draw(tracksprite);
        window.draw(carsprite);
        window.display(); //Shows the new frame


    }



    
}
