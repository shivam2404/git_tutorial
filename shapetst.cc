// main program for shapes
// author:  Holger Arndt
// version: 27.09.2018

#include <iostream>
#include <memory>
#include <QApplication>
#include <QPalette>
#include "pv2d.h"
#include "shapes.h"
#include "shapewin.h"

using namespace std;

int main(int argc, char** argv)
{
  QApplication qapp{argc, argv};

  shared_ptr<Scene> sc{make_shared<Scene>()};
  sc->add(make_shared<ColouredDot>(100, 100, 255, 0, 0));
  sc->add(make_shared<ColouredRectangle>(Point2D{50, 50}, 100, 150, 0, 255, 0));
  sc->add(make_shared<ColouredSquare>(Point2D{75, 75}, 50, 255, 128, 0));
  sc->add(make_shared<ColouredLine>(Point2D{10,210}, Point2D{190, 210}, 0, 0,
                                    255));
  vector<Point2D> pvec{ Point2D{250, 200}, Point2D{300, 250}, Point2D{250, 300},
                        Point2D{200, 250} };
  sc->add(make_shared<ColouredPolygon>(Point2D{0, 0}, pvec, 255, 0, 255));

  shared_ptr<Scene> subsc{make_shared<Scene>()};
  for (int i{0}; i < 100; ++i)
    subsc->add(make_shared<ColouredLine>(Point2D(190 + i, 15),
                                         Point2D(190 + i, 115), 50 + 2 * i,
                                         120 + i, 200 - i));
  sc->add(subsc);

  ShapeWindow swin{sc};
  swin.resize(301, 301);
  swin.setMinimumSize(301, 301);
  swin.setPalette(QPalette{"black", "white"});

  swin.show();
   sc->add(subsc);

  ShapeWindow swin{sc};
  swin.resize(301, 301);
  swin.setMinimumSize(301, 301);
  swin.setPalette(QPalette{"black", "white"});

  swin.show();


  return qapp.exec();
}
