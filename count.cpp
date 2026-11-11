#include<SFML/Graphics.hpp>
#include<iostream>
int main()
{
    sf::RenderWindow countdown(sf::VideoMode(1000,700),"COUNTDOWN");
    countdown.setFramerateLimit(60);
    sf::Texture tom ;
    tom.loadFromFile("wow.png");
    sf::Sprite jerry ;
    jerry.setTexture(tom);
    jerry.setScale({1000.0f,700.0f});
    sf::Font count ;
    count.loadFromFile("arial.ttf");
    sf::Text cd ;
    cd.setFont(count);
    cd.setStyle(sf::Text::Bold);
    cd.setCharacterSize(100);
    cd.setOutlineThickness(3.0f);
    cd.setOutlineColor(sf::Color::Black);
    sf::Clock timer ;
    while(countdown.isOpen())
    {
        sf::Event z ;
        while(countdown.pollEvent(z))
        {
            if(z.type==sf::Event::Closed)
            {
                countdown.close();
            }
        }
        float counting = timer.getElapsedTime().asSeconds();
          if(counting<1.0f)
          {
            cd.setString("3");
            cd.setFillColor(sf::Color::Red);
          }
          else if(counting<2.0f)
          {
            cd.setString("2");
            cd.setFillColor(sf::Color::Yellow);
          }
          else if(counting<3.0f)
          {
            cd.setString("1");
            cd.setFillColor(sf::Color::Cyan);
          }
          else if(counting<4.0f)
          {
            cd.setString("GO!");
            cd.setFillColor(sf::Color::Magenta);
          }
          else 
          countdown.close();
          float scaleX = 1000.0f / tom.getSize().x;
float scaleY = 700.0f  / tom.getSize().y;
jerry.setScale(scaleX, scaleY);

          cd.setPosition({450.f,280.f});
          countdown.clear();
          countdown.draw(jerry);
          if(counting<4.0f)
          {
            countdown.draw(cd);
          }
          countdown.display();

    }
    return 0 ; 

}