#include <format>
#include <iostream>

constexpr auto NUM_ITERATIONS = 100uz;

// f(x)=x^2-3
constexpr auto Function(const auto &x) { return x * x - 3.0; }

// f'(x)=2x
constexpr auto Derivative(const auto &x) { return 2.0 * x; }

constexpr auto Newton(const auto &init) {
  auto x = init;
  for (auto i = 0uz; i < NUM_ITERATIONS; ++i) {
    x = x - Function(x) / Derivative(x);
  }
  return x;
}

int main() {
  constexpr auto result = Newton(100.0);
  std::cout << std::format("sqrt(3) = {}\n", result);
  return 0;
}
