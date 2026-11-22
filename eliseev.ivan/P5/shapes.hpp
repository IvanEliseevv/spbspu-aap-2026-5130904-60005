#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "shape.hpp"
#include <cmath>
#include <stdexcept>

namespace eliseev
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(double width, double height, const point_t& pos)
      : width_(width), height_(height), pos_(pos)
    {
      if (width_ <= 0.0 || height_ <= 0.0) throw std::invalid_argument("Invalid dimensions");
    }

    double getArea() const override { return width_ * height_; }
    rectangle_t getFrameRect() const override { return { width_, height_, pos_ }; }
    void move(double dx, double dy) override { pos_.x += dx; pos_.y += dy; }
    void move(const point_t& pos) override { pos_ = pos; }
    void scale(double k) override
    {
      if (k <= 0.0) throw std::invalid_argument("Invalid scale");
      width_ *= k;
      height_ *= k;
    }

  private:
    double width_, height_;
    point_t pos_;
  };

  class Ellipse : public Shape
  {
  public:
    Ellipse(double rx, double ry, const point_t& pos)
      : rx_(rx), ry_(ry), pos_(pos)
    {
      if (rx_ <= 0.0 || ry_ <= 0.0) throw std::invalid_argument("Invalid radii");
    }

    double getArea() const override { return M_PI * rx_ * ry_; }
    rectangle_t getFrameRect() const override { return { 2.0 * rx_, 2.0 * ry_, pos_ }; }
    void move(double dx, double dy) override { pos_.x += dx; pos_.y += dy; }
    void move(const point_t& pos) override { pos_ = pos; }
    void scale(double k) override
    {
      if (k <= 0.0) throw std::invalid_argument("Invalid scale");
      rx_ *= k;
      ry_ *= k;
    }

  private:
    double rx_, ry_;
    point_t pos_;
  };

  class Regular : public Shape
  {
  public:
    Regular(int angles, double radius, const point_t& pos)
      : angles_(angles), radius_(radius), pos_(pos)
    {
      if (angles_ < 3 || radius_ <= 0.0) throw std::invalid_argument("Invalid polygon");
    }

    double getArea() const override { return 0.5 * angles_ * radius_ * radius_ * std::sin(2.0 * M_PI / angles_); }
    rectangle_t getFrameRect() const override { return { 2.0 * radius_, 2.0 * radius_, pos_ }; }
    void move(double dx, double dy) override { pos_.x += dx; pos_.y += dy; }
    void move(const point_t& pos) override { pos_ = pos; }
    void scale(double k) override
    {
      if (k <= 0.0) throw std::invalid_argument("Invalid scale");
      radius_ *= k;
    }

  private:
    int angles_;
    double radius_;
    point_t pos_;
  };
}

#endif