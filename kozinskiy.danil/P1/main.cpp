#include <cstddef>
#include <iostream>
#include <limits>

int main()
{
    const size_t maxsize = std::numeric_limits<size_t>::max();
    int left = 0;
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
    int middle = 0;
    if (!(std::cin >> middle))
    {
        std::cerr << "Error: Incorrect data\n";
        return 1;
    }
    size_t locmaxcount = 0;
    size_t eqrunlen = 1;
    size_t maxeqrunlen = 1;

    bool eql_overflow = false;
    bool loc_overflow = false;

    if (middle != 0)
    {
        int right = 0;
        while (std::cin >> right)
        {
            if (left == middle)
            {
                if (eqrunlen == maxsize)
                {
                    eql_overflow = true;
                }
                else
                {
                    eqrunlen++;
                }
            }
            else
            {
                if (maxeqrunlen < eqrunlen)
                {
                    maxeqrunlen = eqrunlen;
                }
                eqrunlen = 1;
            }
            if (right == 0)
            {
                break;
            }
            if (left < middle && middle > right)
            {
                if (locmaxcount == maxsize)
                {
                    loc_overflow = true;
                }
                else
                {
                    locmaxcount++;
                }
            }
            left = middle;
            middle = right;
        }
    }
    
    if (std::cin.fail())
    {
        std::cerr << "Error: Incorrect data\n";
        return 1;
    }
    
    if (maxeqrunlen < eqrunlen)
    {
        maxeqrunlen = eqrunlen;
    }

    if (!eql_overflow)
    {
        std::cout << "[EQL-SEQ] = " << maxeqrunlen << '\n';
    }
    else
    {
        std::cerr << "Error: Overflow in [EQL-SEQ]\n";
    }

    if (!loc_overflow)
    {
        std::cout << "[LOC-MAX] = " << locmaxcount << '\n';
    }
    else
    {
        std::cerr << "Error: Overflow in [LOC-MAX]\n";
    }

    if (eql_overflow || loc_overflow)
    {
        return 2;
    }

    return 0;
}
