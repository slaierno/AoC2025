#include <array>
#include <concepts>

template <typename UInt> constexpr unsigned ulog2(UInt x) {
  if constexpr (sizeof x > 4)
    return x ? 8 * sizeof x - __builtin_clzll(x) : 0;
  else
    return x ? 8 * sizeof x - __builtin_clz(x) : 0;
}

template <typename UInt> constexpr UInt upow10(unsigned exp) {
  return std::array<UInt, 20>{
      UInt(1e0),  UInt(1e1),  UInt(1e2),  UInt(1e3),  UInt(1e4),
      UInt(1e5),  UInt(1e6),  UInt(1e7),  UInt(1e8),  UInt(1e9),
      UInt(1e10), UInt(1e11), UInt(1e12), UInt(1e13), UInt(1e14),
      UInt(1e15), UInt(1e16), UInt(1e17), UInt(1e18), UInt(1e19),
  }[exp];
};

template <typename UInt> constexpr unsigned ulog10(UInt x) {
  constexpr std::array<unsigned, 65> guess = {
      0,  0,  0,  0,  1,  1,  1,  2,  2,  2,  3,  3,  3,  3,  4,  4,  4,
      5,  5,  5,  6,  6,  6,  6,  7,  7,  7,  8,  8,  8,  9,  9,  9,  9,
      10, 10, 10, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15,
      15, 15, 15, 16, 16, 16, 17, 17, 17, 18, 18, 18, 18, 19};
  const auto digits = guess[ulog2(x)];
  return digits + (x >= upow10<UInt>(digits));
}

template <std::integral Dividend, std::integral Divisor>
constexpr auto divmod(Dividend dividend, Divisor divisor) {
  const auto div = dividend / divisor;
  const auto mod = dividend - div * divisor;
  return std::pair{div, mod};
}

namespace test {
using ULL = unsigned long long;
static_assert(ulog10(ULL(0)) == 0);
static_assert(ulog10(ULL(9)) == 1);
static_assert(ulog10(ULL(10)) == 2);
static_assert(ulog10(ULL(101)) == 3);
static_assert(ulog10(ULL(1101)) == 4);

} // namespace test
