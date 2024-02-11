cmake_minimum_required(VERSION 3.28)
project(z3_sudoku_solver)

set(CMAKE_CXX_STANDARD 23)

add_definitions(-DDEFAULT_SUDOKU_FILE="${CMAKE_CURRENT_SOURCE_DIR}/sudoku/sudoku1.txt")

find_package(Z3 REQUIRED CONFIG)

add_executable(sudoku_solver main.cpp)
target_include_directories(sudoku_solver PRIVATE ${Z3_CXX_INCLUDE_DIRS})
target_link_libraries(sudoku_solver PRIVATE ${Z3_LIBRARIES})