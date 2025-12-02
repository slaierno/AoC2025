#include "mathutils.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cassert>
#include <numeric>
#include <ranges>

constexpr bool is_invalid_id(const uint64_t id) {
  if (id == 0)
    return false;

  const uint64_t digits = ulog10(id);
  for (uint64_t divisor = 2; divisor <= digits; divisor++) {
    uint64_t temp_id = id;
    const auto [div, mod] = divmod(digits, divisor);
    if (mod != 0)
      continue;
    const uint64_t pattern = temp_id % upow10<uint64_t>(div);
    temp_id /= upow10<uint64_t>(div);
    while (temp_id > 0) {
      const uint64_t new_pattern = temp_id % upow10<uint64_t>(div);
      if (new_pattern != pattern)
        break;
      temp_id /= upow10<uint64_t>(div);
    }
    if (temp_id == 0)
      return true;
  }
  return false;
}

// Test input: 4174379265
// Real input: 45283684555
int main(int argc, char *argv[]) {
  assert(argc == 2);
  const std::string input_filename(argv[1]);

  const auto id_ranges =
      AoC::get_input(input_filename, ",", [](std::string line) {
        return AoC::split(line, '-',
                          [](const auto &str) { return std::stoull(str); });
      });

  const auto res = std::accumulate(
      id_ranges.begin(), id_ranges.end(), 0ULL,
      [](const auto acc, const auto range) {
        return acc + std::ranges::fold_left(
                         std::views::iota(range[0], range[1] + 1), 0ULL,
                         [](const uint64_t acc, const uint64_t id) {
                           return acc + (is_invalid_id(id) ? id : 0ULL);
                         });
      });
  std::cout << res << "\n";
  return 0;
}