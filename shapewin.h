// Patterns: Composite
// author:  Holger Arndt
// version: 17.12.2019

#ifndef SHAPEWIN_H
#define SHAPEWIN_H

class ShapeWindow;

#include <memory>
#include <QPaintEvent>
#include <QWidget>
#include "pv2d.h"
#include "shapes.h"

class ShapeWindow : public QWidget
{
private:
  std::shared_ptr<Scene> theScene;
public:
  ShapeWindow(std::shared_ptr<Scene>& sc) : theScene{sc} {}
  void paintEvent(QPaintEvent* qpe [[maybe_unused]]) override { drawShapes(); }
  void drawShapes();
  void dot(const Point2D& p, unsigned char rr = 0, unsigned char gg = 0,
           unsigned char bb = 0);
  void line(const Point2D& a, const Point2D& b, unsigned char rr = 0,
            unsigned char gg = 0, unsigned char bb = 0);
  void rect(const Point2D& ul, const Point2D& lr, unsigned char rr = 0,
            unsigned char gg = 0, unsigned char bb = 0);
};

#endif
