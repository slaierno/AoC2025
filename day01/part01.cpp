#include "utils.hpp"
#include <algorithm>
#include <cassert>
#include <numeric>

constexpr int MAX_DIAL = 99;
constexpr int START_DIAL = 50;
int svtoll(std::string_view sv) { return std::stoll(std::string(sv)); }

int rotate(int from, int rotation) {
  int res = from + rotation;
  if (res > MAX_DIAL)
    return res % (MAX_DIAL + 1);
  else if (res < 0)
    return (MAX_DIAL + 1 + res) % (MAX_DIAL + 1);
  else
    return res;
}

// Test input: 3
// Real input: 1078
int main(int argc, char *argv[]) {
  assert(argc == 2);
  const std::string input_filename(argv[1]);

  const auto instructions =
      AoC::get_input(input_filename, "\n", [](std::string_view line) {
        return svtoll(line.substr(1)) * (line[0] == 'R' ? 1 : -1);
      });

  int dial_pos = START_DIAL;
  const auto pointing_to_zero =
      std::accumulate(instructions.begin(), instructions.end(), 0ULL,
                      [&dial_pos](auto acc, const auto inst) {
                        dial_pos = rotate(dial_pos, inst);
                        return acc + (dial_pos == 0);
                      });

  std::cout << pointing_to_zero << std::endl;

  return 0;
}