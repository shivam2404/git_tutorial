// classes for points and vectors in 2D
// author:  Holger Arndt
// version: 17.12.2019

#ifndef PV2D_H
#define PV2D_H

#include <cmath>
#include <iostream>

class Vector2D;

class Point2D
{
public:
  double x;
  double y;
  Point2D() : x{0}, y{0} {}
  Point2D(double xx, double yy) : x{xx}, y{yy} {}
  Point2D& operator+=(const Vector2D& v);
};

class Vector2D
{
public:
  double x;
  double y;
  Vector2D() : x{0}, y{0} {}
  Vector2D(double xx, double yy) : x{xx}, y{yy} {}
};

inline Point2D& Point2D::operator+=(const Vector2D& v)
{
  x += v.x;
  y += v.y;
  return *this;
}

inline const Point2D operator+(const Point2D& p, const Vector2D& v)
{
  return Point2D(p.x + v.x, p.y + v.y);
}

inline const Vector2D operator-(const Point2D& p, const Point2D& v)
{
  return Vector2D(p.x - v.x, p.y - v.y);
}

inline std::ostream& operator<<(std::ostream& os, const Point2D& p)
{
  os << '(' << p.x << ',' << p.y << ')';
  return os;
}

#endif
