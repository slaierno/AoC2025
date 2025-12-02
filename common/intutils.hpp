#include <string_view>
#include <charconv>
#include <stdexcept>
#include <concepts>

template <std::integral T>
constexpr T svtonum(std::string_view sv)
{
    T value{};
    if (auto ec = std::from_chars(sv.data(), sv.data() + sv.size(), value).ec; ec == std::errc{}) [[likely]]
        return value;
    else if (ec == std::errc::invalid_argument)
        throw std::invalid_argument("Invalid integer: " + std::string(sv));
    else if (ec == std::errc::result_out_of_range)
        throw std::out_of_range("Integer out of range: " + std::string(sv));
    else
        throw std::runtime_error("Unknown error converting integer: " + std::string(sv));
}

#define SVTO(T, SUFFIX)                          \
    constexpr T svt##SUFFIX(std::string_view sv) \
    {                                            \
        return svtonum<T>(sv);                   \
    }
SVTO(int, i)
SVTO(long, l)
SVTO(long long, ll)
SVTO(unsigned long, ul)
SVTO(unsigned long long, ull)
// SVTO(float, f)
// SVTO(double, d)
// SVTO(long double, ld)