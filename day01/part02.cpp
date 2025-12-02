#include "intutils.hpp"
#include "utils.hpp"
#include <cassert>
#include <numeric>

constexpr int MAX_DIAL = 99;
constexpr int START_DIAL = 50;

int svtoll(std::string_view sv) { return std::stoll(std::string(sv)); }

constexpr int inv_pos(int pos) {
  int inv = MAX_DIAL + 1 - pos;
  return inv == (MAX_DIAL + 1) ? 0 : inv;
}

constexpr std::pair<unsigned, int> rotate(int from, int rotation) {
  if (rotation < 0) {
    const auto [num_zeros, pos] = rotate(inv_pos(from), -rotation);
    return {num_zeros, inv_pos(pos)};
  }

  const int res = from + rotation;

  if (res <= MAX_DIAL)
    return {0, res};

  const int div = res / (MAX_DIAL + 1);
  const int mod = res - div * (MAX_DIAL + 1);
  return {div, mod};
}

// Test input: 6
// Real input: 6412
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
                        const auto [passed_zero, new_pos] =
                            rotate(dial_pos, inst);
                        dial_pos = new_pos;
                        return acc + passed_zero;
                      });

  std::cout << pointing_to_zero << std::endl;

  return 0;
}