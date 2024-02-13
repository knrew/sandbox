#include <iostream>

#include "include/utils/algorithm_selector.hpp"
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
  const auto algorithm = SelectAlgorithm(argc >= 4 ? argv[3] : "quick");
  const bool enable_print =
      argc == 4 ? std::string(argv[3]) == "print"
                : (argc >= 5 and std::string(argv[4]) == "print");

  if (!std::filesystem::exists(sequence_file)) {
    std::cerr << "not exists: " << sequence_file << std::endl;
    return -1;
  }

  if (!std::filesystem::exists(answer_file)) {
    std::cerr << "not exists: " << answer_file << std::endl;
    return -1;
  }

  if (algorithm == Algorithm::kNone) {
    std::cerr << "not implemented: " << argv[3] << std::endl;
    return -1;
  }

  std::cout << "sequence file: " << sequence_file << std::endl;
  std::cout << "answer file: " << answer_file << std::endl;
  std::cout << "algorithm: " << AlgorithmName(algorithm) << std::endl;

  std::cout << "reading files... " << std::flush;
  const auto sequence = ReadSequenceFile(sequence_file);
  const auto answer = ReadSequenceFile(answer_file);
  std::cout << "done." << std::endl;

  auto sorted = sequence;

  std::cout << "sorting... " << std::flush;

  const auto f = GetSortFunction(algorithm);
  const auto result = MeasureSortingTime(sorted, answer, f);

  if (!result) {
    std::cerr << "failed." << std::endl;
    return -1;
  }

  std::cout << "done." << std::endl;

  if (enable_print) {
    std::cout << "original: " << std::endl;
    for (const auto &e : sequence) {
      std::cout << e << " ";
    }
    std::cout << std::endl;

    std::cout << "sorted: " << std::endl;
    for (const auto &e : sorted) {
      std::cout << e << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "sorting time: " << StringForPrettyPrint(result.value())
            << std::endl;

  return 0;
}
