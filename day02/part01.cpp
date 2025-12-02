#include "mathutils.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cassert>
#include <numeric>
#include <ranges>

constexpr bool is_invalid_id(uint64_t id) {
  if (id == 0)
    return false;

  const unsigned digits = ulog10(id);
  if (digits % 2 != 0)
    return false;

  const auto [div, mod] = divmod(id, upow10<uint64_t>(digits / 2));
  return div == mod;
}

// Test input: 1227775574
// Real input: 38158151648
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