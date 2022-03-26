#include <cmath>
#include <cstdio>

#include "point.hpp"
using namespace std;

class Circle {
  Point center;
  const double r;

 public:
  Circle(Point ini_center, double ini_r) : center(ini_center), r(ini_r) {}
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
