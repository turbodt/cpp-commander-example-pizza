#include "./utils.hpp"

std::string to_lower(std::string const &str) {
  std::string s = str;
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return s;
}

std::string capitalize(std::string const &str) {
  std::string s = to_lower(str);
  s[0] = std::toupper(s[0]);
  return s;
}
