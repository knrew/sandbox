#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> ReadSequenceFile(const std::filesystem::path &file_name) {
  std::vector<int> result;

  std::ifstream ifs(file_name);

  std::string line;
  while (getline(ifs, line)) {
    result.emplace_back(stoi(line));
  }

  return result;
}

std::vector<std::filesystem::path> GetFileNamesInDirectory(
    const std::filesystem::path &dir) {
  std::vector<std::filesystem::path> result;
  for (const auto &file_name : std::filesystem::directory_iterator(dir)) {
    result.emplace_back(file_name);
  }
  std::sort(result.begin(), result.end());
  return result;
}
