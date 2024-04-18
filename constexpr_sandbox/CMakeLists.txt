cmake_minimum_required(VERSION 3.28)
project(constexpr_sandbox)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(-Wall -Wextra)

# find_package(Boost REQUIRED)
# include_directories(${Boost_INCLUDE_DIR})
# link_directories(${Boost_LIBRARY_DIR})

add_executable(newton src/newton.cpp)
add_executable(fizzbuzz src/fizzbuzz.cpp)
