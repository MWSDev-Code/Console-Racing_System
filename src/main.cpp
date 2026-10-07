#include<SFML/Graphics.hpp>
#include<iostream>
int main(){

    sf::RenderWindow window(sf::VideoMode({1000,700}),"Console Racing");  //This means add a SFML window of this size

    while(window.isOpen()){

        while(const std::optional event = window.pollEvent()){

            if(event->is<sf::event::closed>() ){
                wndow.close();
            }
        }
        windiw.clear();
        window.display();


    }



    
}
