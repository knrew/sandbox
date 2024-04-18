#include <algorithm>
#include <array>
#include <iostream>

template <std::size_t TSIZE>
class string {
 public:
  static constexpr auto SIZE = TSIZE;

  using Data = std::array<char, SIZE>;

  constexpr string() = default;

  constexpr string(const Data &a) : data(a) {}

  constexpr string(const char s[]) : data() {
    for (auto i = 0uz; i < SIZE; ++i) {
      data[i] = s[i];
      if (s[i] == '\0') {
        break;
      }
    }
  }

  constexpr auto operator<=>(const string &) const = default;

  friend std::ostream &operator<<(std::ostream &os, const string &s) {
    os << s.data.data();
    return os;
  }

 protected:
  Data data;
};

template <std::size_t TSIZE, class TData = string<TSIZE>::Data>
constexpr string<TSIZE> to_string(const auto &n) {
  TData data;

  auto m = n;
  auto i = 0ll;
  do {
    const char y = m % 10 + '0';
    data[i] = y;
    i++;
    m /= 10;
  } while (m != 0);

  data[i] = '\0';

  std::reverse(data.begin(), data.begin() + i);

  return string<TSIZE>(data);
}

template <long long N>
class FizzBuzz {
 protected:
  static constexpr auto MAX_DIGIT = 20uz;

 public:
  using result_type = std::array<string<MAX_DIGIT>, N>;

  static constexpr result_type get() {
    std::array<string<MAX_DIGIT>, N> res;

    for (auto n = 1ll; n <= N; ++n) {
      auto &str = res[n - 1];

      if (n % 15 == 0) {
        str = "FizzBuzz";
      } else if (n % 3 == 0) {
        str = "Fizz";
      } else if (n % 5 == 0) {
        str = "Buzz";
      } else {
        str = to_string<MAX_DIGIT>(n);
      }
    }

    return res;
  }
};

int main() {
  {
    constexpr auto TESTN = 40ll;

    constexpr auto result = FizzBuzz<TESTN>::get();

    constexpr FizzBuzz<TESTN>::result_type answer = {
        "1",    "2",    "Fizz", "4",    "Buzz", "Fizz",     "7",        "8",
        "Fizz", "Buzz", "11",   "Fizz", "13",   "14",       "FizzBuzz", "16",
        "17",   "Fizz", "19",   "Buzz", "Fizz", "22",       "23",       "Fizz",
        "Buzz", "26",   "Fizz", "28",   "29",   "FizzBuzz", "31",       "32",
        "Fizz", "34",   "Buzz", "Fizz", "37",   "38",       "Fizz",     "Buzz"};

    static_assert(result == answer);
  }

  constexpr auto result = FizzBuzz<100>::get();

  for (const auto &e : result) {
    std::cout << e << ", ";
  }
  std::cout << std::endl;

  return 0;
}
