// Patterns: Composite
// author:  Holger Arndt
// version: 18.07.2018

#include <cmath>
#include <vector>
#include "shapes.h"
#include "shapewin.h"

using namespace std;

void Dot::drawMe(ShapeWindow& swin) const
{
  swin.dot(ref);
}
void Dot::drawMe // changed 03_08_2020

void Line::drawMe(ShapeWindow& swin) const
{
  swin.line(ref, ref + end);
}

void Rectangle::drawMe(ShapeWindow& swin) const
{
  swin.rect(ref, ref + lr);
}

void Polygon::drawMe(ShapeWindow& swin) const
{
  for (unsigned int i{0}; i < corners.size() - 1; ++i)
    swin.line(ref + corners[i], ref + corners[i + 1]);
  swin.line(ref + corners.back(), ref + corners.front());
}

Polygon::Polygon(const Point2D& r, const vector<Point2D>& c) : Shape(r)
{
  corners.reserve(c.size());
  for (const auto& ci : c)
    corners.push_back(ci - ref);
}

double Polygon::area() const
{
  double a{0};
  for (unsigned int i{0}; i < corners.size() - 1; ++i)
    a += (corners[i].y + corners[i + 1].y) * (corners[i].x - corners[i + 1].x);
  a += (corners.back().y + corners.front().y)
    * (corners.back().x - corners.front().x);
  a = abs(a / 2);
  return a;
}

void ColouredDot::drawMe(ShapeWindow& swin) const
{
  swin.dot(ref, red, green, blue);
}

void ColouredLine::drawMe(ShapeWindow& swin) const
{
  swin.line(ref, ref + end, red, green, blue);
}

void ColouredRectangle::drawMe(ShapeWindow& swin) const
{
  swin.rect(ref, ref + lr, red, green, blue);
}

void ColouredPolygon::drawMe(ShapeWindow& swin) const
{
  for (unsigned int i{0}; i < corners.size() - 1; ++i)
    swin.line(ref + corners[i], ref + corners[i + 1], red, green, blue);
  swin.line(ref + corners.back(), ref + corners.front(), red, green, blue);
}

void Scene::drawMe(ShapeWindow& swin) const
{
  for (const auto& e : elements)
    e->drawMe(swin);
}

void Scene::shift(const Vector2D& v)
{
  for (const auto& e : elements)
    e->shift(v);
}
