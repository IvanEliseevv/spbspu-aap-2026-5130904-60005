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
  const long long suk2 = 2;
  const int suk = 1;

  long long max1 = smallch;
  long long max2 = smallch;
  long long count = 0;

  long long prev = 0;
  bool hasPrev = false;
  long long curLen = 0;
  long long bestLen = 0;

  while (true)
  {
    long long a = 0;
    if (dibil(a) != 0)
    {
      std::cerr << "enter a chislo \n";
      return suk;
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

    if (!hasPrev)
    {
      curLen = 1;
      hasPrev = true;
    }
    else if (a >= prev)
    {
      ++curLen;
    }
    else
    {
      curLen = 1;
    }
    prev = a;
    if (curLen > bestLen)
    {
      bestLen = curLen;
    }
  }

  const bool good = (count >= suk2 && max2 != smallch);

  if (good)
  {
    std::cout << max2 << "\n";
  }
  else
  {
    std::cerr << "ERROR: small posledovatelnost\n";
  }

  std::cout << bestLen << "\n";

  return good ? 0 : 2;
}
