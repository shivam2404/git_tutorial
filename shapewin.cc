// implementation of ShapeWindow
// author:  Holger Arndt
// version: 17.12.2019

#include <QColor>
#include <QPainter>
#include "pv2d.h"
#include "shapes.h"
#include "shapewin.h"

void ShapeWindow::drawShapes()
{
  theScene->drawMe(*this);
}

void ShapeWindow::dot(const Point2D& p, unsigned char rr, unsigned char gg,
                      unsigned char bb)
{
  QPainter pnt{this};
  pnt.setPen(QColor{rr, gg, bb});
  pnt.drawPoint(static_cast<int>(p.x), static_cast<int>(p.y));
}

void ShapeWindow::line(const Point2D& a, const Point2D& b, unsigned char rr,
                       unsigned char gg, unsigned char bb)
{
  QPainter pnt{this};
  pnt.setPen(QColor{rr, gg, bb});
  pnt.drawLine(static_cast<int>(a.x), static_cast<int>(a.y),
               static_cast<int>(b.x), static_cast<int>(b.y));
}

void ShapeWindow::rect(const Point2D& ul, const Point2D& lr, unsigned char rr,
                       unsigned char gg, unsigned char bb)
{
  QPainter pnt{this};
  pnt.setPen(QColor{rr, gg, bb});
  pnt.drawRect(static_cast<int>(ul.x), static_cast<int>(ul.y),
               static_cast<int>(lr.x - ul.x), static_cast<int>(lr.y - ul.y));
}
