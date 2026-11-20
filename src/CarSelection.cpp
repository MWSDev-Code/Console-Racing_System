#include "projectmenu.h"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
int selectCar(int selectedCar)
{
    sf::RenderWindow window(
        sf::VideoMode::getDesktopMode(), "Car Selection", sf::State::Fullscreen);
    window.setFramerateLimit(60);
    window.setView(sf::View(sf::FloatRect({0.f, 0.f}, {1920.f, 1180.f})));
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("assets/ui/bg.png"))
    {
        cout << "Background not found";
        return -1;
    }
    sf::Sprite background(bgTexture);
    background.setScale({
        1920.f / bgTexture.getSize().x,
        1180.f / bgTexture.getSize().y
        });
    sf::RectangleShape previousButton({ 200.f, 75.f });
    previousButton.setPosition({ 500.f, 950.f });
    previousButton.setFillColor(sf::Color::Transparent);
    sf::RectangleShape nextButton({ 200.f, 75.f });
    nextButton.setPosition({ 1220.f, 950.f });
    nextButton.setFillColor(sf::Color::Transparent);
    sf::RectangleShape selectButton({ 300.f, 90.f });
    selectButton.setPosition({ 810.f, 940.f });
    selectButton.setFillColor(sf::Color(210, 15, 25));
    sf::RectangleShape backButton({ 160.f, 65.f });
    backButton.setPosition({ 70.f, 1060.f });
    backButton.setFillColor(sf::Color::Transparent);
    previousButton.setOutlineThickness(2.f);
    previousButton.setOutlineColor(sf::Color::White);
    nextButton.setOutlineThickness(2.f);
    nextButton.setOutlineColor(sf::Color::White);
    selectButton.setOutlineThickness(7.f);
    selectButton.setOutlineColor(sf::Color::White);
    backButton.setOutlineThickness(2.f);
    backButton.setOutlineColor(sf::Color::White);
    sf::Font font;
    if (font.openFromFile("assets/fonts/arial.ttf") == false)
    {
        cout << "Font not found!";
        return -1;
    }
    sf::Texture carTexture1;
    sf::Texture carTexture2;
    sf::Texture carTexture3;
    sf::Texture carTexture4;
    sf::Text title(font, "SELECT YOUR CAR", 50);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold | sf::Text::Italic);
    sf::RectangleShape leftline({ 110.f, 4.f });
    leftline.setFillColor(sf::Color(210, 20, 30));
    leftline.setPosition({ 580.f, 110.f });
    sf::RectangleShape rightline({ 110.f, 4.f });
    rightline.setFillColor(sf::Color(210, 20, 30));
    rightline.setPosition({ 1245.f, 110.f });
    sf::FloatRect textBounds = title.getLocalBounds();
    title.setOrigin({
        textBounds.size.x / 2.f,
        textBounds.size.y / 2.f
        });
    title.setPosition({ 960.f, 100.f });
    if (carTexture1.loadFromFile("assets/cars/selection/maincar1.png") == false)
    {
        cout << "Unable to load car 1";
        return -1;
    }
    if (carTexture2.loadFromFile("assets/cars/selection/maincar2.png") == false)
    {
        cout << "Unable to load car 2";
        return -1;
    }

    if (carTexture3.loadFromFile("assets/cars/selection/maincar3.png") == false)
    {
        cout << "Unable to load car 3";
        return -1;
    }

    if (carTexture4.loadFromFile("assets/cars/selection/maincar4.png") == false)
    {
        cout << "Unable to load car 4";
        return -1;
    }
    sf::Sprite carsprite1(carTexture1);
    sf::Sprite carsprite2(carTexture2);
    sf::Sprite carsprite3(carTexture3);
    sf::Sprite carsprite4(carTexture4);
    carsprite1.setScale({ 1.0f, 1.0f });
    carsprite2.setScale({ 1.0f, 1.0f });
    carsprite3.setScale({ 1.0f, 1.0f });
    carsprite4.setScale({ 1.0f, 1.0f });
    sf::FloatRect car1Bounds = carsprite1.getGlobalBounds();
    carsprite1.setPosition({
        960.f - car1Bounds.size.x / 2.f - car1Bounds.position.x,
        590.f - car1Bounds.size.y / 2.f - car1Bounds.position.y
        });
    sf::FloatRect car2Bounds = carsprite2.getGlobalBounds();
    carsprite2.setPosition({
         960.f - car2Bounds.size.x / 2.f - car2Bounds.position.x,
         590.f - car2Bounds.size.y / 2.f - car2Bounds.position.y
        });

    sf::FloatRect car3Bounds = carsprite3.getGlobalBounds();

    carsprite3.setPosition({
        960.f - car3Bounds.size.x / 2.f - car3Bounds.position.x,
        590.f - car3Bounds.size.y / 2.f - car3Bounds.position.y
        });

    sf::FloatRect car4Bounds = carsprite4.getGlobalBounds();
    carsprite4.setPosition({
        960.f - car4Bounds.size.x / 2.f - car4Bounds.position.x,
        590.f - car4Bounds.size.y / 2.f - car4Bounds.position.y
        });

    sf::Text previousText(font, "PREVIOUS", 25);
    sf::Text nextText(font, "NEXT", 25);
    sf::Text selectText(font, "SELECT", 45);
    sf::Text backText(font, "BACK", 25);

    previousText.setFillColor(sf::Color::White);
    nextText.setFillColor(sf::Color::White);
    selectText.setFillColor(sf::Color::White);
    backText.setFillColor(sf::Color::White);
    previousText.setPosition({ 530.f, 975.f });
    nextText.setPosition({ 1280.f, 975.f });
    selectText.setPosition({ 895.f, 970.f });
    backText.setPosition({ 115.f, 1080.f });
    previousText.setStyle(sf::Text::Bold);
    nextText.setStyle(sf::Text::Bold);
    backText.setStyle(sf::Text::Bold);
    selectText.setStyle(sf::Text::Bold);
    selectText.setCharacterSize(35);
    sf::RectangleShape box1({ 140,65 });
    sf::RectangleShape box2({ 140,65 });
    sf::RectangleShape box3({ 140,65 });
    sf::RectangleShape box4({ 140,65 });
    box1.setSize({ 170,90 });
    box2.setSize({ 170,90 });
    box3.setSize({ 170,90 });
    box4.setSize({ 170,90 });
    box1.setPosition({ 550 , 780 });
    box1.setOutlineThickness(2);
    box1.setOutlineColor(sf::Color::Red);
    box2.setPosition({ 750 , 780 });
    box2.setOutlineThickness(2);
    box2.setOutlineColor(sf::Color::Red);
    box3.setPosition({ 950 , 780 });
    box3.setOutlineThickness(2);
    box3.setOutlineColor(sf::Color::Red);
    box4.setPosition({ 1150 ,780 });
    box4.setOutlineThickness(2);
    box4.setOutlineColor(sf::Color::Red);
    box1.setFillColor(sf::Color::Transparent);
    box2.setFillColor(sf::Color::Transparent);
    box3.setFillColor(sf::Color::Transparent);
    box4.setFillColor(sf::Color::Transparent);
    sf::Texture car1;
    sf::Texture car2;
    sf::Texture car3;
    sf::Texture car4;
    if (!car1.loadFromFile("assets/cars/selection/car1.png") ||
        !car2.loadFromFile("assets/cars/selection/car2.png") ||
        !car3.loadFromFile("assets/cars/selection/car3.png") ||
        !car4.loadFromFile("assets/cars/selection/car4.png"))
    {
        return -1;
    }
    sf::Sprite scar1(car1);
    sf::Sprite scar2(car2);
    sf::Sprite scar3(car3);
    sf::Sprite scar4(car4);
    scar1.setPosition({ 625 , 825 });
    scar2.setPosition({ 825 , 825 });
    scar3.setPosition({ 1025 , 825 });
    scar4.setPosition({ 1225 ,825 });
    scar1.setScale({ 0.30f, 0.30f });
    scar2.setScale({ 0.30f, 0.30f });
    scar3.setScale({ 0.30f, 0.30f });
    scar4.setScale({ 0.30f, 0.30f });
    scar1.setRotation(sf::degrees(-90));
    scar2.setRotation(sf::degrees(-90));
    scar3.setRotation(sf::degrees(-90));
    scar4.setRotation(sf::degrees(-90));
    scar1.setOrigin({ scar1.getLocalBounds().size.x / 2 , scar1.getLocalBounds().size.y / 2 });
    scar2.setOrigin({ scar2.getLocalBounds().size.x / 2 , scar2.getLocalBounds().size.y / 2 });
    scar3.setOrigin({ scar3.getLocalBounds().size.x / 2 , scar3.getLocalBounds().size.y / 2 });
    scar4.setOrigin({ scar4.getLocalBounds().size.x / 2 , scar4.getLocalBounds().size.y / 2 });



    int carindex = selectedCar < 0 ? 0 : selectedCar;
    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                return -1;
            }

            if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>();
                click && click->button == sf::Mouse::Button::Left)
            {
                const auto position = window.mapPixelToCoords(click->position);
                if (backButton.getGlobalBounds().contains(position))
                {
                    return -1;
                }
                if (nextButton.getGlobalBounds().contains(position) && carindex < 3)
                {
                    ++carindex;
                }
                if (previousButton.getGlobalBounds().contains(position) && carindex > 0)
                {
                    --carindex;
                }
                if (selectButton.getGlobalBounds().contains(position))
                {
                    return carindex;
                }
            }
        }

        if (carindex == 0)
        {
            previousButton.setFillColor(sf::Color::Transparent);
            nextText.setFillColor(sf::Color::White);
            previousButton.setOutlineColor(sf::Color::Transparent);
            previousText.setFillColor(sf::Color::Transparent);
            nextButton.setOutlineColor(sf::Color::White);
            nextButton.setFillColor(sf::Color::White);
            nextText.setFillColor(sf::Color::White);
            previousButton.setFillColor(sf::Color::Transparent);
            nextButton.setFillColor(sf::Color::Transparent);
            box1.setOutlineColor(sf::Color::Green);   box1.setOutlineThickness(5);
            box2.setOutlineColor(sf::Color::White);
            box2.setOutlineThickness(2);
            box3.setOutlineColor(sf::Color::White);
            box3.setOutlineThickness(2);
            box4.setOutlineColor(sf::Color::White);
            box4.setOutlineThickness(2);


        }
        else if (carindex == 3)
        {
            nextText.setFillColor(sf::Color::Transparent);
            previousText.setFillColor(sf::Color::White);
            nextButton.setFillColor(sf::Color::Transparent);
            nextButton.setOutlineColor(sf::Color::Transparent);
            previousButton.setOutlineColor(sf::Color::White);
            previousButton.setFillColor(sf::Color::White);
            nextButton.setFillColor(sf::Color::Transparent);
            previousButton.setFillColor(sf::Color::Transparent);
            box4.setOutlineColor(sf::Color::Green);
            box4.setOutlineThickness(5);
            box1.setOutlineColor(sf::Color::White);
            box1.setOutlineThickness(2);
            box2.setOutlineColor(sf::Color::White);
            box2.setOutlineThickness(2);
            box3.setOutlineColor(sf::Color::White);
            box3.setOutlineThickness(2);
        }
        else
        {
            previousText.setFillColor(sf::Color::White);
            nextText.setFillColor(sf::Color::White);
            previousButton.setOutlineColor(sf::Color::White);
            nextButton.setOutlineColor(sf::Color::White);
            previousButton.setFillColor(sf::Color::Transparent);
            nextButton.setFillColor(sf::Color::Transparent);
            previousButton.setOutlineColor(sf::Color::White);
            nextButton.setOutlineColor(sf::Color::White);
            box4.setOutlineColor(sf::Color::Green);
            box4.setOutlineThickness(5);
            if (carindex == 1)
            {
                box1.setOutlineColor(sf::Color::White);
                box1.setOutlineThickness(2);
                box2.setOutlineColor(sf::Color::Green);
                box2.setOutlineThickness(5);
                box3.setOutlineColor(sf::Color::White);
                box3.setOutlineThickness(2);
                box4.setOutlineColor(sf::Color::White);
                box4.setOutlineThickness(2);
            }
            else
            {
                box1.setOutlineColor(sf::Color::White);
                box1.setOutlineThickness(2);
                box3.setOutlineColor(sf::Color::Green);
                box3.setOutlineThickness(5);
                box2.setOutlineColor(sf::Color::White);
                box2.setOutlineThickness(2);
                box4.setOutlineColor(sf::Color::White);
                box4.setOutlineThickness(2);
            }
        }


        window.clear();

        window.draw(background);
        window.draw(title);

        if (carindex == 0)
        {
            window.draw(carsprite1);
        }
        else if (carindex == 1)
        {
            window.draw(carsprite2);
        }
        else if (carindex == 2)
        {
            window.draw(carsprite3);
        }
        else if (carindex == 3)
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
        window.draw(leftline);
        window.draw(rightline);
        window.draw(box1);
        window.draw(box2);
        window.draw(box3);
        window.draw(box4);
        window.draw(scar1);
        window.draw(scar2);
        window.draw(scar3);
        window.draw(scar4);
        window.display();

    }
    return -1;
}