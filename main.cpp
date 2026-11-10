#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({ 1000, 700 }),
        "Car Selection" );
    window.setFramerateLimit(60);
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("assets/bg.png"))
    {
        cout << "Background not found";
        return 1;
    }
    sf::Sprite background(bgTexture);
    background.setScale({ 0.7f , 0.7f });
    sf::RectangleShape heading({ 900.f, 90.f });
    heading.setPosition({ 50.f, 30.f });
    heading.setFillColor(sf::Color(135, 77, 100));
    sf::RectangleShape carPanel({ 700.f, 350.f });
    carPanel.setPosition({ 150.f, 150.f });
    carPanel.setFillColor(sf::Color(40, 36, 67));
    sf::RectangleShape previousButton({ 120.f, 55.f });
    previousButton.setPosition({ 180.f, 550.f });
    previousButton.setFillColor(sf::Color(65, 85, 115));
    sf::RectangleShape nextButton({ 120.f, 55.f });
    nextButton.setPosition({ 700.f, 550.f });
    nextButton.setFillColor(sf::Color(65, 85, 115));
    sf::RectangleShape selectButton({ 220.f, 55.f });
    selectButton.setPosition({ 390.f, 550.f });
    selectButton.setFillColor(sf::Color(20, 150, 100));
    sf::RectangleShape backButton({ 120.f, 45.f });
    backButton.setPosition({ 50.f, 630.f });
    backButton.setFillColor(sf::Color(100, 65, 65));
    sf::Font font;

    if (font.openFromFile("Assets/arial.ttf") == false)
    {
        cout << "Font not found!";
        return 1;
    }
    sf::Texture carTexture1;
    sf::Texture carTexture2;
    sf::Texture carTexture3;
    sf::Texture carTexture4;
    sf::Text title(font, "SELECT YOUR CAR", 40);

    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);
    sf::FloatRect textBounds = title.getLocalBounds();

    title.setOrigin({ textBounds.size.x / 2.f ,  textBounds.size.y / 2.f
        });
   title.setPosition({ 500.f, 75.f });
    sf::Image car;
  
    if (carTexture1.loadFromFile("assets/cars/car1.png") == false)
    {
        std::cout << "Unable to load car 1";
        return 1;
    }

    if (carTexture2.loadFromFile("assets/cars/car2.png") == false)
    {
        std::cout << "Unable to load car 2";
        return 1;
    }

    if (carTexture3.loadFromFile("assets/cars/car3.png") == false)
    {
        std::cout << "Unable to load car 3";
        return 1;
    }

    if (carTexture4.loadFromFile("assets/cars/car4.png") == false)
    {
        std::cout << "Unable to load car 4";
        return 1;
    }
    sf::Sprite carsprite1(carTexture1);
    sf::Sprite carsprite2(carTexture2);
    sf::Sprite carsprite3(carTexture3);
    sf::Sprite carsprite4(carTexture4);
    carsprite1.setScale({ 0.5f , 0.5f });
    carsprite2.setScale({ 0.5f , 0.5f });
    carsprite3.setScale({ 0.5f , 0.5f });
    carsprite4.setScale({ 0.5f , 0.5f });
    carsprite1.setPosition({ 300.f , 260.f });
    carsprite2.setPosition({ 300.f , 260.f });
    carsprite3.setPosition({ 300.f , 260.f });
    carsprite4.setPosition({ 300.f , 260.f });
    sf::Text previousText(font, "PREVIOUS", 20);
    sf::Text nextText(font, "NEXT", 20);
    sf::Text selectText(font, "SELECT", 20);
    sf::Text backText(font, "BACK", 20);
    previousText.setFillColor(sf::Color::White);
    nextText.setFillColor(sf::Color::White);
    selectText.setFillColor(sf::Color::White);
    backText.setFillColor(sf::Color::White);
    previousText.setPosition({ 195.f, 565.f });
    nextText.setPosition({ 735.f, 565.f });
    selectText.setPosition({ 465.f, 565.f });
    backText.setPosition({ 85.f, 642.f });
    {
        std::cout << "FONT NOT FOUND" << std::endl;
    }
    int carindex = 0;
    int selectedcar = 5;
    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                    if (backButton.getGlobalBounds().contains(
                        sf::Vector2f(mousePosition)))
                    {
                        window.close();
                    }
                    if (nextButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
                    {
                        if (carindex < 3)
                        {
                            carindex++;
                        }
                    }
                    if (previousButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
                    {
                        if (carindex > 0)
                        {
                            carindex--;
                        }
                    }
                    if (selectButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
                    {
                        selectedcar = carindex;
                        window.close();
                    }
                }
            }
        }

        if (carindex == 0)
        {
            previousText.setFillColor(sf::Color::Transparent);
            nextText.setFillColor(sf::Color::White);
        }
        else if (carindex == 3)
        {
            nextText.setFillColor(sf::Color::Transparent);
            previousText.setFillColor(sf::Color::White);
        }
        else
        {
            previousText.setFillColor(sf::Color::White);
            nextText.setFillColor(sf::Color::White);
        }
        if (carindex == 0)
        {
            previousButton.setFillColor(sf::Color::Transparent);
            nextButton.setFillColor(sf::Color(65, 85, 115));
        }
        else if (carindex == 3)
        {
            nextButton.setFillColor(sf::Color::Transparent);
            previousButton.setFillColor(sf::Color(65, 85, 115));
        }
        else
        {
            previousButton.setFillColor(sf::Color(65, 85, 115));
            nextButton.setFillColor(sf::Color(65, 85, 115));
        }
        window.clear();

        window.draw(background);


        window.draw(heading);
        window.draw(title);
        window.draw(carPanel);
        if (carindex == 0)
        {
            window.draw(carsprite1);
        }
        else  if (carindex == 1)
        {
            window.draw(carsprite2);
        }
        else  if (carindex == 2)
        {
            window.draw(carsprite3);
        }
        else  if (carindex == 3)
        {
            window.draw(carsprite4);

        }

        window.draw(previousButton);
        window.draw(nextButton);
        window.draw(selectButton);
        window.draw(backButton);
        window.draw(previousText);
        window.draw(nextText);
        window.draw(selectText);
        window.draw(backText);

        window.display();
    }
        return 0;
    }
    

  
