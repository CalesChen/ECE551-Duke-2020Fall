#include <cmath>
#include <cstdio>

using namespace std;

class Point {
  double x;
  double y;

 public:
  Point() : x(0), y(0) {}
  void move(double dx, double dy) {
    x += dx;
    y += dy;
  }
  double distanceFrom(const Point & p);
};
