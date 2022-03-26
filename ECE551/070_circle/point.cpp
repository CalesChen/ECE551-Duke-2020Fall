#include "point.hpp"

double Point::distanceFrom(const Point & p) {
  double diff1 = p.x - x;
  double diff2 = p.y - y;

  return sqrt(diff1 * diff1 + diff2 * diff2);
}
