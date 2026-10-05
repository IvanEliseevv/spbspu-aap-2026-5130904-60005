#include <iostream>
int debil(long long& a)
{
  if (!(std::cin >> a))
  {
    return 1;
  }
  return 0;
}
int main()
{
  long long count = 0, max1 = -1234567812345, max2 = -1234567812345;
  while (true)
  {
    long long a;
    if (debil(a) != 0)
    {
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
  if (count < 2)
  {
    return 2;
  }
  std::cout << max2 << "\n";
  return 0;
}
