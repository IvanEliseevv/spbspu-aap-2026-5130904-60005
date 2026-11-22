#include <iostream>
#include <limits>
#include <stdexcept>

namespace eliseev
{
  class ISeqProperty
  {
  public:
    virtual ~ISeqProperty() = default;

    size_t operator()() const
    {
      return result();
    }

    void operator()(int i)
    {
      next(i);
    }

  private:
    virtual size_t result() const = 0;
    virtual void next(int i) = 0;
  };

  class SubMax : public ISeqProperty
  {
  public:
    SubMax() : max1_(std::numeric_limits<long long>::min()),
               max2_(std::numeric_limits<long long>::min()),
               count_(0) {}

  private:
    size_t result() const override
    {
      if (count_ < 2 || max2_ == std::numeric_limits<long long>::min())
      {
        throw std::runtime_error("ERROR: small posledovatelnost");
      }
      return static_cast<size_t>(max2_);
    }

    void next(int a) override
    {
      ++count_;
      if (a > max1_)
      {
        max2_ = max1_;
        max1_ = a;
      }
      else if (a < max1_ && a > max2_)
      {
        max2_ = a;
      }
    }

    long long max1_;
    long long max2_;
    size_t count_;
  };

  class CntMax : public ISeqProperty
  {
  public:
    CntMax() : max_(std::numeric_limits<long long>::min()),
               count_(0),
               max_count_(0) {}

  private:
    size_t result() const override
    {
      if (count_ == 0)
      {
        throw std::runtime_error("ERROR: empty sequence");
      }
      return max_count_;
    }

    void next(int a) override
    {
      ++count_;
      if (a > max_)
      {
        max_ = a;
        max_count_ = 1;
      }
      else if (a == max_)
      {
        ++max_count_;
      }
    }

    long long max_;
    size_t count_;
    size_t max_count_;
  };
}

int main()
{
  using namespace eliseev;

  try
  {
    ISeqProperty* props[2];
    props[0] = new SubMax();
    props[1] = new CntMax();

    int value = 0;
    bool input_error = false;

    while (std::cin >> value && value != 0)
    {
      (*props[0])(value);
      (*props[1])(value);
    }

    if (!std::cin)
    {
      input_error = true;
    }

    if (input_error)
    {
      std::cerr << "ERROR: invalid input\n";
      delete props[0];
      delete props[1];
      return 1;
    }

    int exit_code = 0;
    
    try
    {
      std::cout << (*props[0])() << "\n";
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      exit_code = 2;
    }

    try
    {
      std::cout << (*props[1])() << "\n";
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      exit_code = 2;
    }

    delete props[0];
    delete props[1];

    return exit_code;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}