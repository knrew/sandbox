#include <chrono>
#include <cmath>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <optional>

#include "z3++.h"

std::optional<std::vector<std::vector<int>>> ParseSudoku(
    const std::filesystem::path &sudoku_file) {
  if (!std::filesystem::exists(sudoku_file)) {
    return std::nullopt;
  }

  auto ifs = std::ifstream(sudoku_file);

  if (!ifs) {
    return std::nullopt;
  }

  std::vector<std::vector<int>> sudoku;

  std::optional<std::size_t> sudoku_size = std::nullopt;

  std::string line;
  while (std::getline(ifs, line)) {
    std::vector<int> row;

    for (const char c : line) {
      const int n = c - '0';

      if (n < 0 or 9 < n) {
        return std::nullopt;
      }

      row.emplace_back(n);
    }

    if (!sudoku_size) {
      sudoku_size = row.size();
    } else if (row.size() != sudoku_size) {
      return std::nullopt;
    }

    sudoku.emplace_back(row);
  }

  if (sudoku.size() != sudoku_size) {
    return std::nullopt;
  }

  return sudoku;
}

int BlockSize(const int sudoku_size) {
  return static_cast<int>(std::sqrt(static_cast<double>(sudoku_size)));
}

void PrintSudoku(const std::vector<std::vector<int>> &sudoku) {
  for (const auto &e : sudoku) {
    for (const auto &f : e) {
      std::cout << f;
    }
    std::cout << std::endl;
  }
}

std::optional<std::vector<std::vector<int>>> SolveSudoku(
    const std::vector<std::vector<int>> &sudoku_problem) {
  const int sudoku_size = sudoku_problem.size();
  const int block_size = BlockSize(sudoku_size);

  z3::context context;
  z3::solver solver(context);
  std::vector<std::vector<z3::expr>> sudoku_exprs(sudoku_size);

  // 変数定義
  for (int r = 0; r < sudoku_size; ++r) {
    for (int c = 0; c < sudoku_size; ++c) {
      auto name = std::to_string(r) + std::to_string(c);
      sudoku_exprs[r].emplace_back(context.int_const(name.c_str()));
    }
  }

  // 各マス1-9
  for (int r = 0; r < sudoku_size; ++r) {
    for (int c = 0; c < sudoku_size; ++c) {
      solver.add(1 <= sudoku_exprs[r][c] and sudoku_exprs[r][c] <= sudoku_size);
    }
  }

  // 各列
  for (int r = 0; r < sudoku_size; ++r) {
    z3::expr_vector d(context);
    for (int c = 0; c < sudoku_size; ++c) {
      d.push_back(sudoku_exprs[r][c]);
    }
    solver.add(z3::distinct(d));
  }

  // 各行
  for (int c = 0; c < sudoku_size; ++c) {
    z3::expr_vector d(context);
    for (int r = 0; r < sudoku_size; ++r) {
      d.push_back(sudoku_exprs[r][c]);
    }
    solver.add(z3::distinct(d));
  }

  // 各ブロック
  for (int block_r = 0; block_r < block_size; ++block_r) {
    for (int block_c = 0; block_c < block_size; ++block_c) {
      z3::expr_vector d(context);
      for (int r = 0; r < block_size; ++r) {
        for (int c = 0; c < block_size; ++c) {
          d.push_back(
              sudoku_exprs[block_size * block_r + r][block_size * block_c + c]);
        }
      }
      solver.add(z3::distinct(d));
    }
  }

  for (int r = 0; r < sudoku_size; ++r) {
    for (int c = 0; c < sudoku_size; ++c) {
      if (sudoku_problem[r][c] != 0) {
        solver.add(sudoku_exprs[r][c] == sudoku_problem[r][c]);
      }
    }
  }

  if (solver.check() == z3::unsat) {
    return std::nullopt;
  }

  auto answer = std::vector<std::vector<int>>(9, std::vector<int>(9, -1));

  const auto model = solver.get_model();
  for (int i = 0; i < model.size(); ++i) {
    const auto d = model[i];
    const auto name = d.name().str();
    const auto value = model.get_const_interp(d).as_uint64();
    answer[name[0] - '0'][name[1] - '0'] = value;
  }

  return answer;
}

std::pair<long, std::string> AboutTime(const auto &start) {
  using namespace std::chrono;

  const auto passed = system_clock::now() - start;
  if (auto count = duration_cast<hours>(passed).count(); count > 0) {
    return {count, "hour"};
  }

  if (auto count = duration_cast<minutes>(passed).count(); count > 0) {
    return {count, "min"};
  }

  if (auto count = duration_cast<seconds>(passed).count(); count > 0) {
    return {count, "sec"};
  }

  if (auto count = duration_cast<milliseconds>(passed).count(); count > 0) {
    return {count, "ms"};
  }

  if (auto count = duration_cast<nanoseconds>(passed).count(); count > 0) {
    return {count, "ns"};
  }

  return {-1l, "unmeasurable"};
}

int main(const int argc, const char *const *const argv) {
  std::cout << "z3 sudoku solver started." << std::endl;

  const auto start = std::chrono::system_clock::now();

  const auto sudoku_file =
      std::filesystem::absolute(argc == 1 ? DEFAULT_SUDOKU_FILE : argv[1]);

  std::cout << "sudoku file: " << sudoku_file << std::endl;

  const auto sudoku_problem = ParseSudoku(sudoku_file).value();

  const auto result = SolveSudoku(sudoku_problem);

  std::cout << (result ? "SOLVED" : "UNSOLVABLE") << std::endl;

  std::cout << "input:" << std::endl;
  PrintSudoku(sudoku_problem);

  if (result) {
    const auto sudoku_answer = result.value();

    std::cout << "output:" << std::endl;
    PrintSudoku(sudoku_answer);
  }

  const auto [time, unit] = AboutTime(start);
  std::cout << std::format("time: {}[{}]", time, unit) << std::endl;

  return 0;
}