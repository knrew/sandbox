#include <chrono>
#include <functional>
#include <optional>
#include <vector>

#include "../quicksort.hpp"

bool Check(const std::vector<int> &sequence, const std::vector<int> &answer) {
  if (sequence.size() != answer.size()) {
    return false;
  }

  for (int i = 0; i < sequence.size(); ++i) {
    if (sequence[i] != answer[i]) {
      return false;
    }
  }
  return true;
}

std::optional<std::chrono::system_clock::duration> MeasureSortingTime(
    std::vector<int> &sequence, const std::vector<int> &answer,
    std::function<void(std::vector<int> &)> sort_func) {
  const auto start = std::chrono::system_clock::now();
  sort_func(sequence);
  const auto sorting_time = std::chrono::system_clock::now() - start;

  if (!Check(sequence, answer)) {
    return std::nullopt;
  }

  return sorting_time;
}
