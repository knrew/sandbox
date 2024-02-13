#pragma once

#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

void GenerateRandomSequence(const int size,
                            const std::filesystem::path &sequence_file,
                            const std::filesystem::path &answer_file) {
  std::cout << "sequence size: " << size << std::endl;
  std::cout << "output file: " << sequence_file << std::endl;
  std::cout << "answer file: " << answer_file << std::endl;

  std::vector<int> answer;

  std::random_device seed_gen;
  std::default_random_engine engine(seed_gen());
  std::uniform_int_distribution<> dist(std::numeric_limits<int>::min(),
                                       std::numeric_limits<int>::max());

  {
    std::ofstream ofs(sequence_file);

    for (int i = 0; i < size; ++i) {
      if (i == 0 or i == size - 1 or (i + 1) % 1000 == 0) {
        std::cout << std::format("generating... {}/{}\r", i + 1, size)
                  << std::flush;
      }
      const int n = dist(engine);

      ofs << n << std::endl;
      answer.emplace_back(n);
    }
  }
  std::cout << std::endl;

  std::cout << "sorting... " << std::flush;

  std::sort(answer.begin(), answer.end());

  std::cout << "done." << std::endl;

  std::ofstream ofs(answer_file);
  for (int i = 0; i < size; ++i) {
    if (i == 0 or i == size - 1 or (i + 1) % 1000 == 0) {
      std::cout << std::format("answer writing... {}/{}\r", i + 1, size)
                << std::flush;
    }
    ofs << answer[i] << std::endl;
  }
  std::cout << std::endl;
}
