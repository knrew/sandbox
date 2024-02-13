#include <filesystem>
#include <iostream>
#include <ostream>
#include <string>

#include "include/utils/generator.hpp"

int main(const int argc, const char *const *const argv) {
  if (argc < 4) {
    std::cerr << "invalid arguments" << std::endl;
    return -1;
  }

  std::cout << "random sequece generator started!" << std::endl;

  const auto sequence_size = std::stoi(argv[1]);
  const auto sequence_file = std::filesystem::absolute(argv[2]);
  const auto answer_file = std::filesystem::absolute(argv[3]);

  GenerateRandomSequence(sequence_size, sequence_file, answer_file);

  std::cout << "random sequence and answer generating succeeded!" << std::endl;

  return 0;
}
