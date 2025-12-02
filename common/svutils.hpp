#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>

namespace AoC {
std::ostringstream get_input_stream(std::string_view file_path) {
  std::ifstream file{file_path.data()};
  std::ostringstream oss{};
  oss << file.rdbuf();
  // Use std::ostringstream::view to avoid a string copy
  // But remember that std::string_view does not own the memory!
  return oss;
}
} // namespace AoC