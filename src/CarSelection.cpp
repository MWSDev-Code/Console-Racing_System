#include "projectmenu.h"

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
namespace
{
void centerText(sf::Text& text, sf::Vector2f position)
{
    const auto bounds = text.getLocalBounds();
    text.setOrigin(bounds.position + bounds.size / 2.f);
    text.setPosition(position);
}

void fitCar(sf::Sprite& sprite, sf::Vector2f center, sf::Vector2f available)
{
    const auto bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.position + bounds.size / 2.f);
    const auto rotatedSize = sprite.getGlobalBounds().size;
    const float scale = std::min(available.x / rotatedSize.x, available.y / rotatedSize.y);
    sprite.setScale({scale, scale});
    sprite.setPosition(center);
}

struct CarChoice
{
    sf::Texture previewTexture;
    sf::Texture thumbnailTexture;
    sf::Sprite preview{previewTexture};
    sf::Sprite thumbnail{thumbnailTexture};
    sf::RectangleShape card;
};
}

int selectCar(int selectedCar)
{
    sf::RenderWindow window(
        sf::VideoMode::getDesktopMode(), "Car Selection", sf::State::Fullscreen);
    window.setFramerateLimit(60);
    const sf::Vector2f canvas{1672.f, 941.f};
    sf::View view(sf::FloatRect({0.f, 0.f}, canvas));
    const float aspect = static_cast<float>(window.getSize().x) / window.getSize().y;
    const float canvasAspect = canvas.x / canvas.y;
    const sf::Vector2f viewportSize{
        std::min(1.f, canvasAspect / aspect), std::min(1.f, aspect / canvasAspect)};
    view.setViewport({(sf::Vector2f{1.f, 1.f} - viewportSize) / 2.f, viewportSize});
    window.setView(view);

    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("assets/ui/car-selection-garage.jpg"))
    {
        std::cerr << "Background not found\n";
        return -1;
    }
    bgTexture.setSmooth(true);
    sf::Sprite background(bgTexture);
    background.setScale({canvas.x / bgTexture.getSize().x, canvas.y / bgTexture.getSize().y});

    sf::Font font;
    if (!font.openFromFile("assets/fonts/arial.ttf"))
    {
        std::cerr << "Font not found\n";
        return -1;
    }

    const sf::Color accent(224, 5, 12);
    const sf::Color border(175, 175, 178);
    const sf::Color panelColor(17, 19, 21, 246);
    const auto makePanel = [&](sf::Vector2f size, sf::Vector2f position) {
        sf::RectangleShape panel(size);
        panel.setPosition(position);
        panel.setFillColor(panelColor);
        panel.setOutlineColor(border);
        panel.setOutlineThickness(-1.f);
        return panel;
    };

    sf::Text title(font, "SELECT YOUR CAR", 64);
    title.setStyle(sf::Text::Bold);
    title.setScale({0.79f, 1.f});
    title.setOrigin(title.getLocalBounds().position);
    title.setPosition({120.f, 40.f});

    sf::Text previewLabel(font, "", 26);
    previewLabel.setStyle(sf::Text::Bold);

    std::array<CarChoice, 4> choices;
    std::array<sf::Text, 4> labels{
        sf::Text(font, "CAR 1", 22), sf::Text(font, "CAR 2", 22),
        sf::Text(font, "CAR 3", 22), sf::Text(font, "CAR 4", 22)};
    const std::string carDirectory = "assets/cars/selection/";
    for (std::size_t i = 0; i < choices.size(); ++i)
    {
        auto& choice = choices[i];
        const auto filename = "car" + std::to_string(i + 1) + ".png";
        if (!choice.previewTexture.loadFromFile(carDirectory + "main" + filename) ||
            !choice.thumbnailTexture.loadFromFile(carDirectory + filename))
        {
            return -1;
        }
        choice.previewTexture.setSmooth(true);
        choice.thumbnailTexture.setSmooth(true);
        choice.preview.setTexture(choice.previewTexture, true);
        choice.thumbnail.setTexture(choice.thumbnailTexture, true);

        fitCar(choice.preview, {856.f, 425.f}, {980.f, 540.f});
        const float left = 371.f + 240.f * i;
        choice.card = makePanel({210.f, 131.f}, {left, 654.f});
        choice.thumbnail.setRotation(sf::degrees(-90.f));
        fitCar(choice.thumbnail, {left + 105.f, 708.f}, {117.f, 117.f});
        labels[i].setStyle(sf::Text::Bold);
        centerText(labels[i], {left + 105.f, 758.f});
    }

    const auto previousButton = makePanel({260.f, 62.f}, {171.f, 830.f});
    const auto nextButton = makePanel({260.f, 62.f}, {1241.f, 830.f});
    auto selectButton = makePanel({422.f, 73.f}, {625.f, 823.f});
    selectButton.setFillColor(accent);
    selectButton.setOutlineColor(sf::Color::White);
    const auto backButton = makePanel({136.f, 53.f}, {1470.f, 39.f});

    const auto buttonLabel = [&](const sf::RectangleShape& button, const char* label,
                                 unsigned int size) {
        sf::Text text(font, label, size);
        text.setStyle(sf::Text::Bold);
        centerText(text, button.getPosition() + button.getSize() / 2.f);
        return text;
    };
    auto previousText = buttonLabel(previousButton, "PREVIOUS", 25);
    auto nextText = buttonLabel(nextButton, "NEXT", 25);
    const auto selectText = buttonLabel(selectButton, "SELECT CAR", 37);
    const auto backText = buttonLabel(backButton, "BACK", 25);

    sf::RectangleShape checkmarkShort({14.f, 5.f});
    checkmarkShort.setRotation(sf::degrees(45.f));
    sf::RectangleShape checkmarkLong({22.f, 5.f});
    checkmarkLong.setRotation(sf::degrees(-45.f));

    const int lastCar = static_cast<int>(choices.size()) - 1;
    int carIndex = std::clamp(selectedCar, 0, lastCar);
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
                    return -1;
                if (selectButton.getGlobalBounds().contains(position))
                    return carIndex;
                if (nextButton.getGlobalBounds().contains(position) && carIndex < lastCar)
                    ++carIndex;
                if (previousButton.getGlobalBounds().contains(position) && carIndex > 0)
                    --carIndex;

                for (int i = 0; i <= lastCar; ++i)
                {
                    if (choices[i].card.getGlobalBounds().contains(position))
                        carIndex = i;
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(title);
        window.draw(choices[carIndex].preview);
        previewLabel.setString("CAR " + std::to_string(carIndex + 1));
        centerText(previewLabel, {836.f, 603.f});
        window.draw(previewLabel);

        for (int i = 0; i <= lastCar; ++i)
        {
            auto& choice = choices[i];
            const bool active = i == carIndex;
            choice.card.setOutlineColor(active ? accent : border);
            choice.card.setOutlineThickness(active ? -4.f : -1.f);
            choice.card.setFillColor(active ? sf::Color(43, 19, 21, 243) : panelColor);
            window.draw(choice.card);
            window.draw(choice.thumbnail);
            window.draw(labels[i]);
            if (active)
            {
                const auto corner = choice.card.getPosition() + sf::Vector2f{173.f, 9.f};
                checkmarkShort.setPosition(corner + sf::Vector2f{3.f, 7.f});
                checkmarkLong.setPosition(corner + sf::Vector2f{9.f, 17.f});
                window.draw(checkmarkShort);
                window.draw(checkmarkLong);
            }
        }

        previousText.setFillColor(carIndex > 0 ? sf::Color::White : border);
        nextText.setFillColor(carIndex < lastCar ? sf::Color::White : border);
        window.draw(previousButton);
        window.draw(previousText);
        window.draw(nextButton);
        window.draw(nextText);
        window.draw(selectButton);
        window.draw(selectText);
        window.draw(backButton);
        window.draw(backText);
        window.display();
    }
    return -1;
}
