#include "circle.hpp"
#define PI 3.1415926535
void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double compute_x(double r1, double r2, double dist) {
  double y = (r1 * r1 - r2 * r2 + dist * dist) / (2 * dist);  // split the dist
  return y;
}
double Circle::intersectionArea(const Circle & otherCircle) {
  double r2 = otherCircle.r;
  double r1 = r;
  double dist = center.distanceFrom(otherCircle.center);

  //There is no intersection Area
  if ((r1 + r2) <= dist) {
    return 0.0;
  }
  // adjust the order, we choose the larger one as r1
  if (r1 < r2) {
    double temp = r1;
    r1 = r2;
    r2 = temp;
  }
  // if the bigger cirgle include the smaller one
  if ((r2 + dist) <= r1) {
    return PI * r2 * r2;
  }
  //general

  double x1 = compute_x(r1, r2, dist);  // compute the triangle of r1
  double x2 = compute_x(r2, r1, dist);  // compute the triangle of r2
  double alpha1 = std::acos(x1 / r1);   // the angle of the larger circle
  double alpha2 = std::acos(x2 / r2);   // the angle of the smaller one
  double s1 = alpha1 * r1 * r1 - std::sin(2 * alpha1) * r1 * r1 * 0.5;
  double s2 = alpha2 * r2 * r2 - std::sin(2 * alpha2) * r2 * r2 * 0.5;

  return s2 + s1;
}
