// Patterns: Composite
// author:  Holger Arndt
// version: 18.07.2018

#ifndef SHAPES_H
#define SHAPES_H

class Scene;

#include <memory>
#include <vector>
#include "pv2d.h"
#include "shapewin.h"

class SceneElement
{
protected:
  virtual void drawMe(ShapeWindow& swin) const = 0;
public:
  virtual ~SceneElement() {}
  virtual void shift(const Vector2D& v) = 0;
  friend class Scene;
  friend class ShapeWindow;
};

class Shape : public SceneElement
{
protected:
  Point2D ref;
public:
  Shape(const Point2D& r) : ref{r} {}
  virtual void moveto(const Point2D& p) { ref = p; }
  virtual void shift(const Vector2D& v) override { ref += v; }
  virtual double area() const = 0;
};

class Dot : virtual public Shape
{
protected:
  virtual void drawMe(ShapeWindow& swin) const override;
public:
  Dot(const Point2D& p) : Shape{p} {}
  Dot(double x, double y) : Shape{Point2D{x, y}} {}
  virtual double area() const override { return 0.0; }
};

class Line : virtual public Shape
{
protected:
  Vector2D end;
  virtual void drawMe(ShapeWindow& swin) const override;
public:
  Line(const Point2D& a, const Point2D& b) : Shape{a}, end{b - a} {}
  virtual double area() const override { return 0.0; }
};

class Rectangle : virtual public Shape
{
protected:
  Vector2D lr;  // vector from the ref point to the lower right corner
  virtual void drawMe(ShapeWindow& swin) const override;
public:
  Rectangle(const Point2D& ul, double w, double h) : Shape{ul}, lr{w, h} {}
  virtual double area() const override { return lr.x * lr.y; }
};

class Square : public Rectangle
{
public:
  Square(const Point2D& ul, double w) : Shape{ul}, Rectangle{ul, w, w} {}
};

class Polygon : virtual public Shape
{
protected:
  std::vector<Vector2D> corners;  // vectors from the ref point to ALL corners
  virtual void drawMe(ShapeWindow& swin) const override;
public:
  Polygon(const Point2D& r, const std::vector<Point2D>& c);
  virtual double area() const override;
};

class ColouredShape : virtual public Shape
{
protected:
  unsigned char red;   // 0..255
  unsigned char green;
  unsigned char blue;
public:
  ColouredShape(const Point2D& r, unsigned char rr, unsigned char gg,
                unsigned char bb)
    : Shape{r}, red{rr}, green{gg}, blue{bb} {}
};

class ColouredDot : public ColouredShape, public Dot
{
protected:
  virtual void drawMe(ShapeWindow& swin) const override;
public:
  ColouredDot(const Point2D& p, unsigned char rr, unsigned char gg,
              unsigned char bb)
    : Shape{p}, ColouredShape{p, rr, gg, bb}, Dot{p} {}
  ColouredDot(double x, double y, unsigned char rr, unsigned char gg,
              unsigned char bb)
    : Shape{Point2D{x, y}}, ColouredShape{Point2D{x, y}, rr, gg, bb}, Dot{x, y}
  {}
};

class ColouredLine : public ColouredShape, public Line
{
protected:
  virtual void drawMe(ShapeWindow& swin) const override;
public:
  ColouredLine(const Point2D& a, const Point2D& b, unsigned char rr,
               unsigned char gg, unsigned char bb)
    : Shape{a}, ColouredShape{a, rr, gg, bb}, Line{a, b} {}
};

class ColouredRectangle : public ColouredShape, public Rectangle
{
protected:
  virtual void drawMe(ShapeWindow& swin) const override;
public:
  ColouredRectangle(const Point2D& ul, double w, double h, unsigned char rr,
                    unsigned char gg, unsigned char bb)
    : Shape{ul}, ColouredShape{ul, rr, gg, bb}, Rectangle{ul, w, h} {}
};

class ColouredSquare : public ColouredRectangle
{
public:
  ColouredSquare(const Point2D& ul, double w, unsigned char rr,
                 unsigned char gg, unsigned char bb)
    : Shape{ul}, ColouredRectangle{ul, w, w, rr, gg, bb} {}
};

class ColouredPolygon : public ColouredShape, public Polygon
{
protected:
  virtual void drawMe(ShapeWindow& swin) const override;
public:
  ColouredPolygon(const Point2D& r, const std::vector<Point2D>& c,
                  unsigned char rr, unsigned char gg, unsigned char bb)
    : Shape{r}, ColouredShape{r, rr, gg, bb}, Polygon{r, c} {}
};

class Scene : public SceneElement
{
protected:
  std::vector<std::shared_ptr<SceneElement>> elements;
  virtual void drawMe(ShapeWindow& swin) const override;
public:
  void add(std::shared_ptr<SceneElement> el) { elements.push_back(el); }
  virtual void shift(const Vector2D& v) override;
  friend class ShapeWindow;
};

#endif
