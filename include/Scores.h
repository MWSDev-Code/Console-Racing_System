#pragma once

#include <fstream>
#include <iomanip>
#include <string>

enum ScoreIndex { Highest, Lowest, Current, ScoreCount };

inline bool loadScores(double (&scores)[ScoreCount]) {
  std::ifstream file("data/scores.txt");
  std::string label;
  return file >> label && label == "Highest:" && file >> scores[Highest] &&
         file >> label && label == "Lowest:" && file >> scores[Lowest] &&
         file >> label && label == "Current:" && file >> scores[Current];
}

inline bool saveRaceTime(double seconds) {
  double scores[ScoreCount]{};
  if (loadScores(scores)) {
    if (seconds > scores[Highest]) {
      scores[Highest] = seconds;
    }
    if (seconds < scores[Lowest]) {
      scores[Lowest] = seconds;
    }
  } else {
    scores[Highest] = seconds;
    scores[Lowest] = seconds;
  }
  scores[Current] = seconds;

  std::ofstream file("data/scores.txt");
  file << std::fixed << std::setprecision(2)
       << "Highest: " << scores[Highest] << '\n'
       << "Lowest: " << scores[Lowest] << '\n'
       << "Current: " << scores[Current] << '\n';
  file.close();
  return static_cast<bool>(file);
}
