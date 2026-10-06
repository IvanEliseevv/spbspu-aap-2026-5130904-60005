#include <iostream>

namespace eliseev
{
  int dibil(long long& a)
  {
    if (!(std::cin >> a))
    {
      return 1;
    }
    return 0;
  }
}

int main()
{
  using namespace eliseev;
  const long long smallch = -9223372036854775807LL - 1;
  long long max1 = smallch;
  long long max2 = smallch;
  long long count = 0;
  while (true)
  {
    long long a = 0;
    if (dibil(a) != 0)
    {
      std::cerr << "enter a chislo \n";
      return 1;
    }
    if (a == 0)
    {
      break;
    }
    ++count;
    if (a > max1)
    {
      max2 = max1;
      max1 = a;
    }
    else if (a > max2 && a != max1)
    {
      max2 = a;
    }
  }

  if (count < 2 || max2 == smallch)
  {
    std::cerr << "ERROR: small posledovatelnost\n";
    return 2;
  }
  std::cout << max2 << "\n";
  return 0;
}
