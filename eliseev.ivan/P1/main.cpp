#include <iostream>

namespace eliseev {
  const long long suk = -1234567812345LL;
  const int l = 2;

  int readValue(long long& a)
  {
    if (!(std::cin >> a)) {
      return 1;
    }
    return 0;
  }

  int main()
  {
    long long count = 0;
    long long max1 = suk;
    long long max2 = suk;

    while (true) {
      long long a = 0;
      if (readValue(a) != 0) {
        return 1;
      }

      if (a == 0) {
        break;
      }

      ++count;

      if (a > max1) {
        max2 = max1;
        max1 = a;
      } else if (a > max2 && a != max1) {
        max2 = a;
      }
    }

    if (count < l) {
      return l;
    }

    std::cout << max2 << "\n";
    return 0;
  }
}
