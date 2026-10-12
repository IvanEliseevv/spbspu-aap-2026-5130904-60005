#include <iostream>
#include <limits>

namespace kozinskiy
{
  int EQL_SEQ(long long int left, long long int middle,
              unsigned long long int& eq_run_len,
              unsigned long long int& max_eq_run_len)
  {
    if (left == middle)
    {
      if (eq_run_len == std::numeric_limits<unsigned long long int>::max())
      {
        std::cerr << "Error: Overflow\n";
        return 2;
      }
      eq_run_len++;
    }
    else
    {
      if (max_eq_run_len < eq_run_len)
      {
        max_eq_run_len = eq_run_len;
      }
      eq_run_len = 1;
    }
    return 0;
  }

  int LOC_MAX(long long int left, long long int middle, long long int right,
              unsigned long long int& loc_max_count)
  {
    if (left < middle && middle > right)
    {
      if (loc_max_count == std::numeric_limits<unsigned long long int>::max())
      {
        std::cerr << "Error: Overflow\n";
        return 2;
      }
      loc_max_count++;
    }
    return 0;
  }
}

int main()
{
  const int ok = 0;

  long long int left = -1;

  if (!(std::cin >> left))
  {
    std::cerr << "Error: Incorrect data\n";
    return 1;
  }

  if (left == 0)
  {
    std::cout << "[EQL-SEQ] = " << 0 << '\n';
    std::cerr << "Error: sequence is too short to [LOC-MAX]\n";
    return 2;
  }

  long long int middle = -1;

  if (!(std::cin >> middle))
  {
    std::cerr << "Error: Incorrect data\n";
    return 1;
  }

  unsigned long long int loc_max_count = 0;
  unsigned long long int eq_run_len = 1;
  unsigned long long int max_eq_run_len = 1;

  if (middle != 0)
  {
    long long int right = -1;
    while (std::cin >> right)
    {
      int eql_res =
          kozinskiy::EQL_SEQ(left, middle, eq_run_len, max_eq_run_len);
      if (eql_res != ok)
      {
        return eql_res;
      }

      if (right == 0)
      {
        break;
      }

      int loc_res = kozinskiy::LOC_MAX(left, middle, right, loc_max_count);
      if (loc_res != ok)
      {
        return loc_res;
      }

      left = middle;
      middle = right;
    }

    if (std::cin.fail())
    {
      std::cerr << "Error: Incorrect data\n";
      return 1;
    }
  }

  if (max_eq_run_len < eq_run_len)
  {
    max_eq_run_len = eq_run_len;
  }

  std::cout << "[EQL-SEQ] = " << max_eq_run_len << '\n';
  std::cout << "[LOC-MAX] = " << loc_max_count << '\n';
  return 0;
}
