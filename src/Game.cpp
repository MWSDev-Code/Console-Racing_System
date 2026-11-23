#include "Game.h"
#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "Car.h"
#include "Scores.h"
#include "checkpoint.h"
int Game::run(int selectedCar) {
  sf::RenderWindow window(
      sf::VideoMode({1280, 720}), "Console Racing");

  sf::Texture trackTexture;

  if (!trackTexture.loadFromFile("assets/track/Track1.png")) {
    return 1;
  }

  sf::Sprite tracksprite(trackTexture);
  tracksprite.setScale(
      {1280.0f / trackTexture.getSize().x, 720.0f / trackTexture.getSize().y});

  Car player1;
  Car player2;

  if (!player1.load(selectedCar)) {
    return 1;
  }

  const int player2Selection =
      selectedCar >= 0 && selectedCar < 4 ? (selectedCar + 1) % 4 : 1;

  if (!player2.load(player2Selection)) {
    return 1;
  }

  // Align both cars with the painted grid rows behind the start line.
  constexpr float startingGridX = 555.0f;
  player1.setPosition({startingGridX, 565.0f});
  player2.setPosition({startingGridX, 623.0f});

  CarControls player1Controls{sf::Keyboard::Key::W, sf::Keyboard::Key::S,
                              sf::Keyboard::Key::A, sf::Keyboard::Key::D};

  CarControls player2Controls{sf::Keyboard::Key::Up, sf::Keyboard::Key::Down,
                              sf::Keyboard::Key::Left,
                              sf::Keyboard::Key::Right};

  const std::array<sf::FloatRect, 4> checkpointAreas = {{
      {{1050.f, 290.f}, {170.f, 35.f}},  // CP1 - Right
      {{1080.f, 50.f}, {35.f, 145.f}},   // CP2 - Top right
      {{600.f, 270.f}, {35.f, 170.f}},   // CP3 - Middle
      {{45.f, 300.f}, {160.f, 35.f}}     // CP4 - Left
  }};

  std::array<Checkpoint, 4> checkpoints = {
      {{checkpointAreas[0].position, checkpointAreas[0].size},
       {checkpointAreas[1].position, checkpointAreas[1].size},
       {checkpointAreas[2].position, checkpointAreas[2].size},
       {checkpointAreas[3].position, checkpointAreas[3].size}}};

  constexpr unsigned int totalLaps = 3;

  struct PlayerProgress {
    std::size_t nextCheckpoint = 0;
    std::array<bool, 4> wasInsideCheckpoint = {false, false, false, false};
    unsigned int completedLaps = 0;
    bool wasInsideFinishLine = false;
  };

  PlayerProgress progress1;
  PlayerProgress progress2;

  bool raceFinished = false;
  int winner = 0;

  const sf::FloatRect finishLineArea{{620.f, 535.f}, {40.f, 130.f}};

  progress1.wasInsideFinishLine =
      finishLineArea.contains(player1.getPosition());

  progress2.wasInsideFinishLine =
      finishLineArea.contains(player2.getPosition());

  // Load font
  sf::Font font;

  if (!font.openFromFile("assets/fonts/Roboto.ttf")) {
    std::cerr << "Failed to load font!" << std::endl;
    return 1;
  }

  const sf::Color hudAccent(224, 5, 12);
  const sf::Color hudMuted(185, 190, 199);

  sf::RectangleShape progressPanel({304.f, 132.f});
  progressPanel.setFillColor(sf::Color(16, 18, 22, 235));
  progressPanel.setOutlineColor(sf::Color(105, 109, 118));
  progressPanel.setOutlineThickness(-1.f);

  sf::RectangleShape progressAccent({304.f, 3.f});
  progressAccent.setFillColor(hudAccent);

  sf::RectangleShape progressDivider({1.f, 45.f});
  progressDivider.setFillColor(sf::Color(78, 82, 91));

  sf::Text lapLabel(font, "LAP", 13);
  lapLabel.setFillColor(hudMuted);
  lapLabel.setStyle(sf::Text::Bold);

  sf::Text checkpointLabel(font, "CHECKPOINTS", 13);
  checkpointLabel.setFillColor(hudMuted);
  checkpointLabel.setStyle(sf::Text::Bold);

  sf::Text lapCounter(font, "", 28);
  lapCounter.setStyle(sf::Text::Bold);

  sf::Text checkpointCounter(font, "", 28);
  checkpointCounter.setStyle(sf::Text::Bold);

  std::array<sf::RectangleShape, 4> checkpointSegments;

  for (auto& segment : checkpointSegments) {
    segment.setSize({23.f, 5.f});
  }

  sf::Text checkpointMessage(font, "", 17);
  checkpointMessage.setFillColor(hudMuted);

  sf::Text playerLabel(font, "", 16);
  playerLabel.setStyle(sf::Text::Bold);

  sf::Text timerText(font, "Time: 0.00 s", 26);
  timerText.setPosition({20.f, 164.f});
  timerText.setFillColor(sf::Color::White);
  timerText.setOutlineColor(sf::Color::Black);
  timerText.setOutlineThickness(2.f);

  sf::Text livesText(font, "", 18);
  livesText.setFillColor(sf::Color::White);
  livesText.setStyle(sf::Text::Bold);

  constexpr bool showDebugCheckpoints = false;

  sf::Clock raceClock;

  sf::Clock frameClock;

  auto updateProgress = [&](Car& car, PlayerProgress& progress,
                            int playerNumber) {
    // Check if the car enters a checkpoint
    for (std::size_t i = 0; i < checkpoints.size(); i++) {
      bool isInsideCheckpoint = checkpoints[i].contains(car.getPosition());

      if (!raceFinished && isInsideCheckpoint &&
          !progress.wasInsideCheckpoint[i] && i == progress.nextCheckpoint) {
        progress.nextCheckpoint++;

        std::cout << "Player " << playerNumber << " Checkpoint "
                  << progress.nextCheckpoint << " reached!" << std::endl;
      }

      progress.wasInsideCheckpoint[i] = isInsideCheckpoint;
    }

    const bool isInsideFinishLine = finishLineArea.contains(car.getPosition());

    if (!raceFinished && isInsideFinishLine && !progress.wasInsideFinishLine &&
        progress.nextCheckpoint == checkpoints.size()) {
      ++progress.completedLaps;

      std::cout << "Player " << playerNumber << " Lap "
                << progress.completedLaps << " completed!" << std::endl;

      if (progress.completedLaps == totalLaps) {
        raceFinished = true;
        winner = playerNumber;
        if (!saveRaceTime(raceClock.getElapsedTime().asSeconds())) {
          std::cerr << "Could not save the race time to data/scores.txt.\n";
        }
      } else {
        progress.nextCheckpoint = 0;
      }
    }

    progress.wasInsideFinishLine = isInsideFinishLine;
  };

  auto drawProgress = [&](const PlayerProgress& progress, int playerNumber,
                          float panelX) {
    progressPanel.setPosition({panelX, 16.f});
    progressAccent.setPosition({panelX, 16.f});
    progressDivider.setPosition({panelX + 93.f, 42.f});

    lapLabel.setPosition({panelX + 13.f, 43.f});
    checkpointLabel.setPosition({panelX + 108.f, 43.f});

    lapCounter.setPosition({panelX + 13.f, 59.f});
    checkpointCounter.setPosition({panelX + 108.f, 59.f});

    const auto currentLap = std::min(progress.completedLaps + 1, totalLaps);

    lapCounter.setString(std::to_string(currentLap) + "/" +
                         std::to_string(totalLaps));

    checkpointCounter.setString(std::to_string(progress.nextCheckpoint) + "/" +
                                std::to_string(checkpoints.size()));

    playerLabel.setString("PLAYER " + std::to_string(playerNumber));
    playerLabel.setPosition({panelX + 13.f, 20.f});

    if (playerNumber == 1) {
      playerLabel.setFillColor(hudAccent);
    } else {
      playerLabel.setFillColor(sf::Color(70, 160, 255));
    }

    if (raceFinished && winner == playerNumber) {
      checkpointMessage.setString("Race finished");
    } else if (progress.nextCheckpoint == checkpoints.size()) {
      checkpointMessage.setString("Cross the finish line");
    } else {
      checkpointMessage.setString("Reach checkpoint " +
                                  std::to_string(progress.nextCheckpoint + 1));
    }

    checkpointMessage.setPosition({panelX + 13.f, 96.f});
    livesText.setString("LIVES: " + std::to_string(
        playerNumber == 1 ? player1.getLives() : player2.getLives()));
    livesText.setPosition({panelX + 13.f, 119.f});

    window.draw(progressPanel);
    window.draw(progressAccent);
    window.draw(progressDivider);
    window.draw(playerLabel);
    window.draw(lapLabel);
    window.draw(lapCounter);
    window.draw(checkpointLabel);
    window.draw(checkpointCounter);

    for (std::size_t i = 0; i < checkpointSegments.size(); ++i) {
      auto& segment = checkpointSegments[i];

      segment.setPosition({panelX + 179.f + 27.f * i, 74.f});

      segment.setFillColor(i < progress.nextCheckpoint ? hudAccent
                                                       : sf::Color(78, 82, 91));

      window.draw(segment);
    }

    window.draw(checkpointMessage);
    window.draw(livesText);
  };

  while (window.isOpen()) {
    const float deltaTime = std::min(
        frameClock.restart().asSeconds(), 0.05f);

    while (const auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    if (window.isOpen() && !raceFinished) {
      const float elapsedSeconds = raceClock.getElapsedTime().asSeconds();

      std::ostringstream timerStream;
      timerStream << "Time: " << std::fixed << std::setprecision(2)
                  << elapsedSeconds << " s";

      timerText.setString(timerStream.str());

      const sf::Vector2f player1OldPosition = player1.getPosition();
      const sf::Vector2f player2OldPosition = player2.getPosition();
      const sf::Angle player1OldRotation = player1.getSprite().getRotation();
      const sf::Angle player2OldRotation = player2.getSprite().getRotation();
      player1.update(deltaTime, player1Controls);
      player2.update(deltaTime, player2Controls);

      if (player1.getSprite().getGlobalBounds().findIntersection(
              player2.getSprite().getGlobalBounds())) {
        player1.setPosition(player1OldPosition);
        player2.setPosition(player2OldPosition);
        player1.setRotation(player1OldRotation);
        player2.setRotation(player2OldRotation);
      }

      if (!player1.isActive() || !player2.isActive()) {
        raceFinished = true;
        winner = player1.isActive() ? 1 : 2;
      }

      if (!raceFinished && player1.isActive()) {
        updateProgress(player1, progress1, 1);
      }
      if (!raceFinished) {
        if (player2.isActive()) {
          updateProgress(player2, progress2, 2);
        }
      }
    }

    window.clear();
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

    window.draw(player1.getSprite());
    window.draw(player2.getSprite());

    drawProgress(progress1, 1, 18.f);
    drawProgress(progress2, 2, 958.f);

    window.draw(timerText);

    window.display();
    if (raceFinished) {
      window.close();
    }
  }

  if (raceFinished) {
    sf::RenderWindow resultWindow(sf::VideoMode({640, 360}), "Race Results");
    sf::Text resultTitle(font, "PLAYER " + std::to_string(winner) + " WINS!", 42);
    resultTitle.setStyle(sf::Text::Bold);
    resultTitle.setFillColor(sf::Color::White);
    resultTitle.setPosition({80.f, 105.f});

    sf::Text closeMessage(font, "Close this window to return to the menu", 18);
    closeMessage.setFillColor(hudMuted);
    closeMessage.setPosition({95.f, 220.f});

    while (resultWindow.isOpen()) {
      while (const auto event = resultWindow.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
          resultWindow.close();
        }
      }
      resultWindow.clear(sf::Color(22, 25, 32));
      resultWindow.draw(resultTitle);
      resultWindow.draw(closeMessage);
      resultWindow.display();
    }
  }

  return 0;
}
