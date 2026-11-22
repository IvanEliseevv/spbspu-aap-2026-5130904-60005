#include <iostream>
#include "shapes.hpp"

namespace eliseev
{
  void printShapeInfo(const Shape* shape, const char* name)
  {
    const rectangle_t frame = shape->getFrameRect();
    std::cout << name << ":\n"
              << "  Area: " << shape->getArea() << "\n"
              << "  FrameRect: pos(" << frame.pos.x << ", " << frame.pos.y 
              << "), w=" << frame.width << ", h=" << frame.height << "\n";
  }

  void printAllShapes(const Shape* const* shapes, size_t count)
  {
    double totalArea = 0.0;
    double minX = 1e9, minY = 1e9, maxX = -1e9, maxY = -1e9;

    for (size_t i = 0; i < count; ++i)
    {
      totalArea += shapes[i]->getArea();
      const rectangle_t frame = shapes[i]->getFrameRect();
      
      const double left = frame.pos.x - frame.width / 2.0;
      const double right = frame.pos.x + frame.width / 2.0;
      const double bottom = frame.pos.y - frame.height / 2.0;
      const double top = frame.pos.y + frame.height / 2.0;

      if (left < minX) minX = left;
      if (right > maxX) maxX = right;
      if (bottom < minY) minY = bottom;
      if (top > maxY) maxY = top;
    }

    std::cout << "\n--- Summary ---\n"
              << "Total area: " << totalArea << "\n"
              << "Overall bounding box: pos(" << (minX + maxX) / 2.0 << ", " << (minY + maxY) / 2.0
              << "), w=" << (maxX - minX) << ", h=" << (maxY - minY) << "\n\n";
  }
}

int main()
{
  using namespace eliseev;

  try
  {
    Rectangle rect(10.0, 5.0, {0.0, 0.0});
    Ellipse ellipse(4.0, 2.0, {5.0, 5.0});
    Regular hexagon(6, 3.0, {-5.0, -5.0});

    Shape* shapes[] = { &rect, &ellipse, &hexagon };
    const size_t count = sizeof(shapes) / sizeof(shapes[0]);

    std::cout << "Before scaling:\n";
    printShapeInfo(&rect, "Rectangle");
    printShapeInfo(&ellipse, "Ellipse");
    printShapeInfo(&hexagon, "Regular");
    printAllShapes(shapes, count);

    std::cout << "Enter scale factor: ";
    double k;
    if (!(std::cin >> k) || k <= 0.0)
    {
      std::cerr << "Error: incorrect scale factor\n";
      return 1;
    }

    for (size_t i = 0; i < count; ++i)
    {
      shapes[i]->scale(k);
    }

    std::cout << "\nAfter scaling by " << k << ":\n";
    printShapeInfo(&rect, "Rectangle");
    printShapeInfo(&ellipse, "Ellipse");
    printShapeInfo(&hexagon, "Regular");
    printAllShapes(shapes, count);
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}