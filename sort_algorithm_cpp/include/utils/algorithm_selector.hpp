#pragma once

#include <algorithm>
#include <functional>
#include <string>

#include "../quicksort.hpp"

enum class Algorithm : int {
  kNone,
  kStandard,
  kQuick,
};

Algorithm SelectAlgorithm(const std::string &algorithm) {
  auto algorithm_lower = algorithm;
  std::transform(algorithm_lower.begin(), algorithm_lower.end(),
                 algorithm_lower.begin(), ::tolower);

  if (algorithm_lower == "standard") {
    return Algorithm::kStandard;
  }

  if (algorithm_lower == "quick") {
    return Algorithm::kQuick;
  }

  return Algorithm::kNone;
}

std::function<void(std::vector<int> &)> GetSortFunction(
    const Algorithm algorithm) {
  if (algorithm == Algorithm::kStandard) {
    return [](std::vector<int> &v) { return std::sort(v.begin(), v.end()); };
  }

  if (algorithm == Algorithm::kQuick) {
    return QuickSort;
  }

  return std::function<void(std::vector<int> &)>();
}

std::string AlgorithmName(const Algorithm algorithm) {
  switch (algorithm) {
    case Algorithm::kNone:
      return "none";
    case Algorithm::kStandard:
      return "standard";
    case Algorithm::kQuick:
      return "quicksort";
  }
  return "";
}
