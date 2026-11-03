#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <limits>
#include <cctype>
#include <stdexcept>

namespace eliseev {

  size_t length(const char* s)
  {
    size_t n = 0;
    while (s[n] != '\0') {
      ++n;
    }
    return n;
  }

  char* remove_digits(char* dst, const char* src)
  {
    size_t j = 0;
    for (size_t i = 0; src[i] != '\0'; ++i) {
      if (!isdigit(static_cast<unsigned char>(src[i]))) {
        dst[j++] = src[i];
      }
    }
    dst[j] = '\0';
    return dst;
  }

  char* remove_latin(char* dst, const char* src)
  {
    size_t j = 0;
    for (size_t i = 0; src[i] != '\0'; ++i) {
      if (!isalpha(static_cast<unsigned char>(src[i]))) {
        dst[j++] = src[i];
      }
    }
    dst[j] = '\0';
    return dst;
  }

  char* read_line(std::istream& in)
  {
    const size_t max_size = std::numeric_limits<size_t>::max();
    size_t capacity = 16;
    size_t len = 0;

    char* buf = static_cast<char*>(malloc(capacity));
    if (buf == nullptr) {
      throw std::bad_alloc();
    }

    char c = 0;
    while (in.get(c) && c != '\n') {
      if (len + 1 == capacity) {
        if (capacity > max_size / 2) {
          free(buf);
          throw std::bad_alloc();
        }
        size_t new_capacity = capacity * 2;
        char* bigger = static_cast<char*>(malloc(new_capacity));
        if (bigger == nullptr) {
          free(buf);
          throw std::bad_alloc();
        }
        for (size_t i = 0; i < len; ++i) {
          bigger[i] = buf[i];
        }
        free(buf);
        buf = bigger;
        capacity = new_capacity;
      }
      buf[len++] = c;
    }
    buf[len] = '\0';
    return buf;
  }
}

int main()
{
  try {
    char* input = eliseev::read_line(std::cin);
    const size_t len = eliseev::length(input);

    char* result = static_cast<char*>(malloc(len + 1));
    if (result == nullptr) {
      free(input);
      throw std::bad_alloc();
    }

    std::cout << eliseev::remove_digits(result, input) << "\n";
    std::cout << eliseev::remove_latin(result, input) << "\n";

    free(result);
    free(input);
  }
  catch (const std::bad_alloc& e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }

  return 0;
}