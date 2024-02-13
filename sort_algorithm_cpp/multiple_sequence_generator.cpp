#include <filesystem>
#include <iostream>
#include <string>

#include "include/utils/generator.hpp"

int main(const int argc, const char* const* const argv) {
  if (argc < 5) {
    std::cout << "arguments: sequence_size num_files sequences_dir answers_dir "
                 "sequence_file_prefix answers_file_prefix"
              << std::endl;
    return -1;
  }

  const auto sequence_size = std::stoi(argv[1]);
  const auto num_files = std::stoi(argv[2]);
  const auto sequences_dir = std::filesystem::absolute(argv[3]);
  const auto answers_dir = std::filesystem::absolute(argv[4]);
  const auto sequence_file_prefix = std::string(argc < 6 ? "s" : argv[5]);
  const auto answers_file_prefix = std::string(argc < 7 ? "a" : argv[6]);

  for (int i = 0; i < num_files; ++i) {
    const auto sequence_file =
        sequences_dir / (sequence_file_prefix + std::to_string(i) + ".txt");

    const auto answers_file =
        answers_dir / (answers_file_prefix + std::to_string(i) + ".txt");

    GenerateRandomSequence(sequence_size, sequence_file, answers_file);
  }

  return 0;
}
