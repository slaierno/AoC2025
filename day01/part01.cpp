#include "utils.hpp"
#include <cassert>
#include <algorithm>
#include <numeric>

constexpr int MIN_DIAL = 0;
constexpr int MAX_DIAL = 99;
constexpr int START_DIAL = 50;
int svtoll(std::string_view sv)
{
    return std::stoll(std::string(sv));
}

int rotate(int from, int rotation)
{
    int res = from + rotation;
    if (res > MAX_DIAL)
    {
        return res % (MAX_DIAL + 1);
    }
    else if (res >= 0)
    {
        return res;
    }
    else
    {
        return (MAX_DIAL + 1 + res) % (MAX_DIAL + 1);
    }
}

// Test input: 3
// Real input: 1078
int main(int argc, char *argv[])
{
    assert(argc == 2);
    const std::string input_filename(argv[1]);

    const auto instructions = AoC::get_input(input_filename, "\n", [](std::string_view line)
                                             { return svtoll(line.substr(1)) * (line[0] == 'R' ? 1 : -1); });

    int dial_pos = 50;
    const auto pointing_to_zero =
        std::accumulate(instructions.begin(), instructions.end(), 0ULL,
                        [&dial_pos](auto acc, const auto inst)
                        {
                            dial_pos = rotate(dial_pos, inst);
                            return acc + (dial_pos == 0);
                        });

    std::cout << pointing_to_zero << std::endl;

    return 0;
}