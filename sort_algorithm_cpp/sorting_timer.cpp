#include <filesystem>
#include <iostream>

#include "include/quicksort.hpp"
#include "include/utils/io.hpp"
#include "include/utils/measure.hpp"
#include "include/utils/time.hpp"

int main(const int argc, const char *const *const argv) {
  if (argc < 3) {
    std::cerr << "arguments: sequence_file answer_file" << std::endl;
    return -1;
  }

  const auto sequence_file = std::filesystem::absolute(argv[1]);
  const auto answer_file = std::filesystem::absolute(argv[2]);

  std::cout << "sequence file: " << sequence_file << std::endl;
  std::cout << "answer file: " << answer_file << std::endl;

  if (!std::filesystem::exists(sequence_file)) {
    std::cerr << "not exists: " << sequence_file << std::endl;
    return -1;
  }

  if (!std::filesystem::exists(answer_file)) {
    std::cerr << "not exists: " << answer_file << std::endl;
    return -1;
  }

  const auto sequence = ReadSequenceFile(sequence_file);
  const auto answer = ReadSequenceFile(answer_file);

  auto sorted = sequence;
  const auto result = MeasureSortingTime(sorted, answer, QuickSort);

  if (!result) {
    std::cerr << "ng" << std::endl;
    return -1;
  }

  std::cout << "time: " << StringForPrettyPrint(result.value()) << std::endl;

  return 0;
}
