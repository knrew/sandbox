#pragma once

#include <chrono>
#include <string>

std::string StringForPrettyPrint(const auto &duration) {
  using namespace std::chrono;

  std::string str = "";

  auto count = duration_cast<milliseconds>(duration).count();

  const auto mins = count / 1000 / 60;
  count -= mins * 1000 * 60;
  str += mins != 0 ? std::to_string(mins) + "[min]" : "";

  const auto secs = count / 1000;
  count -= secs * 1000;
  str += secs != 0 ? std::to_string(secs) + "[sec]" : "";

  const auto ms = count;
  str += std::to_string(ms) + "[ms]";

  return str;
}

std::pair<long, std::string> AboutTime(const auto &passed) {
  using namespace std::chrono;

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
