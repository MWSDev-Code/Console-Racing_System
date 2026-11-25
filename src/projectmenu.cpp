#include "projectmenu.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <sstream>

#include "Game.h"
#include "Scores.h"

int runMenu() {
  sf::Texture background;
  sf::Font font;
  if (!background.loadFromFile("assets/ui/menupic.png") ||
      !font.openFromFile("assets/fonts/arial.ttf")) {
    return 1;
  }

  sf::RenderWindow menu(sf::VideoMode({950, 700}), "2D RACING GAME_MENU");
  menu.setFramerateLimit(60);
  sf::Sprite menuSprite(background);
  menuSprite.setScale(
      {950.f / background.getSize().x, 700.f / background.getSize().y});

  sf::Music music;
  const bool musicLoaded = music.openFromFile("assets/sounds/menu_sound.mp3");
  bool soundOn = musicLoaded;
  if (soundOn) {
    music.play();
  }

  const sf::Color red(195, 25, 25);
  const sf::Color gray(55, 55, 55);
  const sf::Color soundColor(35, 35, 35, 220);

  const auto makeBox = [](sf::Vector2f size, sf::Vector2f position,
                          sf::Color color) {
    sf::RectangleShape box(size);
    box.setPosition(position);
    box.setFillColor(color);
    return box;
  };
  const auto makeText = [&font](const char* label, unsigned int size,
                                sf::Vector2f position,
                                sf::Color color = sf::Color::White) {
    sf::Text text(font, label, size);
    text.setPosition(position);
    text.setFillColor(color);
    text.setStyle(sf::Text::Bold);
    return text;
  };

  auto soundBox = makeBox({145, 42}, {790, 18}, soundColor);
  soundBox.setOutlineThickness(2.f);
  soundBox.setOutlineColor(sf::Color::White);

  const auto startBox = makeBox({205, 55}, {15, 230}, red);
  const auto carBox = makeBox({205, 48}, {15, 305}, gray);
  const auto recordsBox = makeBox({205, 48}, {15, 370}, gray);
  const auto exitBox = makeBox({205, 48}, {15, 435}, gray);

  auto records = makeBox({450, 350}, {250, 150}, sf::Color(25, 25, 28, 235));
  records.setOutlineThickness(3.f);
  records.setOutlineColor(red);
  auto back = makeBox({220, 45}, {365, 435}, red);
  back.setOutlineThickness(2.f);
  back.setOutlineColor(sf::Color::White);

  auto soundTitle = makeText(soundOn ? "SOUND ON" : "SOUND OFF", 18, {810, 28});
  const auto heading = makeText("CONSOLE\nRACING", 42, {22, 45});
  const auto startTitle = makeText("START RACE", 23, {38, 243});
  const auto carTitle = makeText("SELECT CAR", 20, {32, 317});
  const auto recordsTitle = makeText("SHOW RECORDS", 18, {32, 384});
  const auto exitTitle = makeText("EXIT", 20, {32, 447});
  const auto recordHeading = makeText("RECORDS OF PLAYERS", 26, {320, 175});
  auto highScore =
      makeText("", 22, {300, 245}, sf::Color(255, 200, 0));
  auto currentScore = makeText("", 22, {300, 295});
  auto lowScore =
      makeText("", 22, {300, 345}, sf::Color(175, 175, 180));
  const auto backTitle = makeText("BACK TO MENU", 18, {395, 447});

  bool showingRecords = false;
  int selectedCar = -1;
  while (menu.isOpen()) {
    while (const auto event = menu.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        return 0;
      }
      const auto* click = event->getIf<sf::Event::MouseButtonPressed>();
      if (!click || click->button != sf::Mouse::Button::Left) {
        continue;
      }

      const auto mousePosition = menu.mapPixelToCoords(click->position);
      if (soundBox.getGlobalBounds().contains(mousePosition)) {
        if (!musicLoaded) {
          continue;
        }
        soundOn = !soundOn;
        if (soundOn) {
          music.play();
        } else {
          music.pause();
        }
        soundTitle.setString(soundOn ? "SOUND ON" : "SOUND OFF");
        soundBox.setFillColor(soundOn ? soundColor : sf::Color(180, 0, 0));
      } else if (showingRecords) {
        if (back.getGlobalBounds().contains(mousePosition)) {
          showingRecords = false;
        }
      } else if (startBox.getGlobalBounds().contains(mousePosition)) {
        if (soundOn) {
          music.pause();
        }
        menu.setVisible(false);
        Game game;
        const int result = game.run(selectedCar, soundOn);
        if (result != 0) {
          return result;
        }
        menu.setVisible(true);
        menu.requestFocus();
        if (soundOn) {
          music.play();
        }
      } else if (carBox.getGlobalBounds().contains(mousePosition)) {
        menu.setVisible(false);
        const int choice = selectCar(selectedCar);
        if (choice >= 0) {
          selectedCar = choice;
        }
        menu.setVisible(true);
        menu.requestFocus();
      } else if (recordsBox.getGlobalBounds().contains(mousePosition)) {
        double scores[ScoreCount]{};
        const bool hasRecord = loadScores(scores);
        const auto formatTime = [hasRecord](double seconds) {
          if (!hasRecord) {
            return std::string("No race yet");
          }
          std::ostringstream text;
          text << std::fixed << std::setprecision(2) << seconds << " s";
          return text.str();
        };
        highScore.setString("HIGHEST SCORE  " + formatTime(scores[Highest]));
        currentScore.setString("CURRENT SCORE  " + formatTime(scores[Current]));
        lowScore.setString("LOWEST SCORE  " + formatTime(scores[Lowest]));
        showingRecords = true;
      } else if (exitBox.getGlobalBounds().contains(mousePosition)) {
        return 0;
      }
    }

    menu.clear();
    menu.draw(menuSprite);
    menu.draw(soundBox);
    menu.draw(soundTitle);
    if (showingRecords) {
      menu.draw(records);
      menu.draw(recordHeading);
      menu.draw(highScore);
      menu.draw(currentScore);
      menu.draw(lowScore);
      menu.draw(back);
      menu.draw(backTitle);
    } else {
      menu.draw(heading);
      menu.draw(startBox);
      menu.draw(carBox);
      menu.draw(recordsBox);
      menu.draw(exitBox);
      menu.draw(startTitle);
      menu.draw(carTitle);
      menu.draw(recordsTitle);
      menu.draw(exitTitle);
    }
    menu.display();
  }
  return 0;
}
