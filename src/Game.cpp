#include "Game.h"
#include "Car.h"
#include<iostream>
#include<algorithm>
int Game::run(){

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
    Car car;
    if(!car.load()){
        return 1;
    }
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
        car.update(deltaTime);
        window.clear(); //It clears the previous frame
        window.draw(tracksprite);
        window.draw(car.getSprite());
        window.display(); //Shows the new frame


    }



    
    return 0;
}
