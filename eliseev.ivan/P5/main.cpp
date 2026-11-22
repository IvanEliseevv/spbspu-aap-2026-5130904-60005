#include <iostream>
#include "shapes.hpp"

namespace eliseev
{
  const double INIT_MIN = 1e9;
  const double INIT_MAX = -1e9;
  const double DEFAULT_0 = 0.0;
  const double DEFAULT_5 = 5.0;
  const double DEFAULT_N5 = -5.0;
  const double RECT_W = 10.0;
  const double RECT_H = 5.0;
  const double ELL_RX = 4.0;
  const double ELL_RY = 2.0;
  const double REG_R = 3.0;
  const int REG_ANGLES = 6;

  void print_shape_info(const Shape* shape, const char* name)
  {
    const rectangle_t frame = shape->getFrameRect();
    std::cout << name << ":\n"
              << "  Area: " << shape->getArea() << "\n"
              << "  FrameRect: pos(" << frame.pos.x << ", " << frame.pos.y << "), w=" << frame.width
              << ", h=" << frame.height << "\n";
  }

  void print_all_shapes(const Shape* const* shapes, size_t count)
  {
    double total_area = DEFAULT_0;
    double min_x = INIT_MIN;
    double min_y = INIT_MIN;
    double max_x = INIT_MAX;
    double max_y = INIT_MAX;

    for (size_t i = 0; i < count; ++i)
    {
      total_area += shapes[i]->getArea();
      const rectangle_t frame = shapes[i]->getFrameRect();

      const double left = frame.pos.x - frame.width / TWO;
      const double right = frame.pos.x + frame.width / TWO;
      const double bottom = frame.pos.y - frame.height / TWO;
      const double top = frame.pos.y + frame.height / TWO;

      if (left < min_x)
      {
        min_x = left;
      }
      if (right > max_x)
      {
        max_x = right;
      }
      if (bottom < min_y)
      {
        min_y = bottom;
      }
      if (top > max_y)
      {
        max_y = top;
      }
    }

    std::cout << "\n--- Summary ---\n"
              << "Total area: " << total_area << "\n"
              << "Overall bounding box: pos(" << (min_x + max_x) / TWO << ", " << (min_y + max_y) / TWO
              << "), w=" << (max_x - min_x) << ", h=" << (max_y - min_y) << "\n\n";
  }

  void scale_shapes(Shape** shapes, size_t count, const point_t& center, double k)
  {
    for (size_t i = 0; i < count; ++i)
    {
      const point_t pos = shapes[i]->getFrameRect().pos;

      shapes[i]->move(center);

      const double dx = (pos.x - center.x) * k - pos.x + center.x;
      const double dy = (pos.y - center.y) * k - pos.y + center.y;

      shapes[i]->scale(k);
      shapes[i]->move(dx, dy);
    }
  }
}

int main()
{
  using namespace eliseev;

  try
  {
    Rectangle rect(RECT_W, RECT_H, {DEFAULT_0, DEFAULT_0});
    Ellipse ellipse(ELL_RX, ELL_RY, {DEFAULT_5, DEFAULT_5});
    Regular hexagon(REG_ANGLES, REG_R, {DEFAULT_N5, DEFAULT_N5});

    Shape* shapes[] = {&rect, &ellipse, &hexagon};
    const size_t count = sizeof(shapes) / sizeof(shapes[0]);

    std::cout << "Before scaling:\n";
    print_shape_info(&rect, "Rectangle");
    print_shape_info(&ellipse, "Ellipse");
    print_shape_info(&hexagon, "Regular");
    print_all_shapes(shapes, count);

    double cx = DEFAULT_0;
    double cy = DEFAULT_0;
    double k = DEFAULT_0;

    std::cout << "Enter scale center and factor (cx cy k): ";
    if (!(std::cin >> cx >> cy >> k) || k <= DEFAULT_0)
    {
      std::cerr << "Error: incorrect scale parameters\n";
      return 1;
    }

    scale_shapes(shapes, count, {cx, cy}, k);

    std::cout << "\nAfter scaling by " << k << " around (" << cx << ", " << cy << "):\n";
    print_shape_info(&rect, "Rectangle");
    print_shape_info(&ellipse, "Ellipse");
    print_shape_info(&hexagon, "Regular");
    print_all_shapes(shapes, count);
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
