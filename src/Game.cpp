
#include "Game.h"

#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

#include "Car.h"
#include "checkpoint.h"

int Game::run(int selectedCar) {
  sf::RenderWindow window(
      sf::VideoMode({1280, 720}),
      "Console Racing");  // This means add a SFML window of this size

  sf::Texture
      trackTexture;  // Create a texture for thetrack image kind of a variable
                     // to hold the image in the program for every frame.

  if (!trackTexture.loadFromFile(
          "assets/track/Track1.png")) {  // It loads the track image from the
                                         // folder and also if there is a issue
                                         // it stops the program.
    return 1;
  }
  sf::Sprite tracksprite(trackTexture);
  tracksprite.setScale(
      {1280.0f / trackTexture.getSize().x, 720.0f / trackTexture.getSize().y});
  Car car;
  if (!car.load(selectedCar)) {
    return 1;
  }
  // Store checkpoint areas for collision detection
  const std::array<sf::FloatRect, 4> checkpointAreas = {{
      {{1050.f, 290.f}, {170.f, 35.f}},  // CP1 - Right
      {{1080.f, 50.f}, {35.f, 145.f}},   // CP2 - Top right
      {{600.f, 270.f}, {35.f, 170.f}},   // CP3 - Middle
      {{45.f, 300.f}, {160.f, 35.f}}     // CP4 - Left
  }};

  // Create the four checkpoints
  std::array<Checkpoint, 4> checkpoints = {
      {{checkpointAreas[0].position, checkpointAreas[0].size},
       {checkpointAreas[1].position, checkpointAreas[1].size},
       {checkpointAreas[2].position, checkpointAreas[2].size},
       {checkpointAreas[3].position, checkpointAreas[3].size}}};
  std::size_t nextCheckpoint = 0;

  std::array<bool, 4> wasInsideCheckpoint = {false, false, false, false};

  constexpr unsigned int totalLaps = 3;
  unsigned int completedLaps = 0;
  bool raceFinished = false;

  // finish-line zone.
  const sf::FloatRect finishLineArea{{620.f, 535.f}, {40.f, 130.f}};

  bool wasInsideFinishLine = finishLineArea.contains(car.getPosition());

  // Load font
  sf::Font font;

  if (!font.openFromFile("assets/fonts/Roboto.ttf")) {
    std::cerr << "Failed to load font!" << std::endl;
    return 1;
  }

  // Checkpoint counter
  sf::Text checkpointCounter(font, "Checkpoints: 0/4", 26);
  checkpointCounter.setPosition({20.f, 20.f});
  checkpointCounter.setFillColor(sf::Color::White);
  checkpointCounter.setOutlineColor(sf::Color::Black);
  checkpointCounter.setOutlineThickness(2.f);

  // Checkpoint message
  sf::Text checkpointMessage(font, "Reach checkpoint 1", 22);
  checkpointMessage.setPosition({20.f, 60.f});
  checkpointMessage.setFillColor(sf::Color::Yellow);
  checkpointMessage.setOutlineColor(sf::Color::Black);
  checkpointMessage.setOutlineThickness(2.f);
  sf::Text lapCounter(font, "Lap: 1/3", 26);
  lapCounter.setPosition({20.f, 100.f});
  lapCounter.setFillColor(sf::Color::White);
  lapCounter.setOutlineColor(sf::Color::Black);
  lapCounter.setOutlineThickness(2.f);

  sf::Text timerText(font, "Time: 0.00 s", 26);
  timerText.setPosition({20.f, 140.f});
  timerText.setFillColor(sf::Color::White);
  timerText.setOutlineColor(sf::Color::Black);
  timerText.setOutlineThickness(2.f);

  // Show checkpoint rectangles for testing
  constexpr bool showDebugCheckpoints = true;

  sf::Clock raceClock;

  sf::Clock
      frameClock;  // It is kind of a stopwatch.              / Thing is we use
                   // this clock to measure the time from 1 frame to another  /

  // Main Game Loop
  while (window.isOpen()) {
    // Limit long frames so a pause does not cause a large movement jump. Delta
    // is actually the frame to frame time in seconds       We could also have
    // use setframe limit but this approcah is better
    const float deltaTime = std::min(
        frameClock.restart().asSeconds(),
        0.05f);  // We use min here to have the minimum delta time
                 // if the frame second gets higher, it only takes 0.05f
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {  // Close the Window if X is
                                             // pressed.
        window.close();
      }
    }

    car.update(deltaTime);
    if (!raceFinished) {
      const float elapsedSeconds = raceClock.getElapsedTime().asSeconds();

      std::ostringstream timerStream;
      timerStream << "Time: " << std::fixed << std::setprecision(2)
                  << elapsedSeconds << " s";

      timerText.setString(timerStream.str());

      car.update(deltaTime);
    }

    // Check if the car enters a checkpoint
    for (std::size_t i = 0; i < checkpoints.size(); i++) {
      bool isInsideCheckpoint = checkpoints[i].contains(car.getPosition());

      if (!raceFinished && isInsideCheckpoint && !wasInsideCheckpoint[i] &&
          i == nextCheckpoint) {
        nextCheckpoint++;

        std::cout << "Checkpoint " << nextCheckpoint << " reached!"
                  << std::endl;

        // Update the checkpoint counter
        checkpointCounter.setString(
            "Checkpoints: " + std::to_string(nextCheckpoint) + "/4");

        // Update checkpoint message
        checkpointMessage.setString(
            "Checkpoint " + std::to_string(nextCheckpoint) + " reached!");

        if (nextCheckpoint == checkpoints.size()) {
          if (completedLaps + 1 == totalLaps) {
            checkpointMessage.setString(
                "All checkpoints reached! Cross the finish line.");
          } else {
            checkpointMessage.setString("Checkpoint 4 reached!");
          }
        }
      }

      wasInsideCheckpoint[i] = isInsideCheckpoint;
    }
    const bool isInsideFinishLine = finishLineArea.contains(car.getPosition());

    if (!raceFinished && isInsideFinishLine && !wasInsideFinishLine &&
        nextCheckpoint == checkpoints.size()) {
      ++completedLaps;

      std::cout << "Lap " << completedLaps << " completed!" << std::endl;

      if (completedLaps == totalLaps) {
        raceFinished = true;

        lapCounter.setString("Laps completed: 3/3");
        checkpointMessage.setString("Race finished! All 3 laps completed.");
      } else {
        nextCheckpoint = 0;

        checkpointCounter.setString("Checkpoints: 0/4");

        lapCounter.setString("Lap: " + std::to_string(completedLaps + 1) +
                             "/3");

        checkpointMessage.setString("Reach checkpoint 1");
      }
    }

    wasInsideFinishLine = isInsideFinishLine;

    window.clear();  // It clears the previous frame
    window.draw(tracksprite);

    // Draw checkpoint rectangles for testing
    if (showDebugCheckpoints) {
      for (const auto& area : checkpointAreas) {
        sf::RectangleShape shape(area.size);
        shape.setPosition(area.position);
        shape.setFillColor(sf::Color(255, 255, 0, 70));
        shape.setOutlineColor(sf::Color::Yellow);
        shape.setOutlineThickness(2.f);

        window.draw(shape);
      }
    }
    if (showDebugCheckpoints) {
      sf::RectangleShape finishShape(finishLineArea.size);

      finishShape.setPosition(finishLineArea.position);
      finishShape.setFillColor(sf::Color(0, 255, 255, 70));
      finishShape.setOutlineColor(sf::Color::Cyan);
      finishShape.setOutlineThickness(2.f);

      window.draw(finishShape);
    }

    window.draw(car.getSprite());

    // Draw checkpoint information
    window.draw(checkpointCounter);
    window.draw(checkpointMessage);
    window.draw(lapCounter);
    window.draw(timerText);
    window.display();  // Shows the new frame
  }

  return 0;
}
