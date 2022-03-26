/* write your class interface in this file
   write function definitions only if they are very short
 */
#include <stdio.h>

#include <cmath>
#include <iostream>
using namespace std;

class Vector2D {
 private:
  double x;
  double y;

 public:
  void initVector(double init_x, double init_y) {
    x = init_x;
    y = init_y;
  }

  double getMagnitude() const { return sqrt(x * x + y * y); }

  Vector2D operator+(const Vector2D & rhs) const;
  Vector2D & operator+=(const Vector2D & rhs);

  double dot(const Vector2D & rhs) const { return x * rhs.x + y * rhs.y; }

  void print() const { printf("<%.2f, %.2f>", x, y); }
};
