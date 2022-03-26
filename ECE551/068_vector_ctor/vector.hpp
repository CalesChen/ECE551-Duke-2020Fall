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
  Vector2D():x(0),y(0){}
  Vector2D(double ini_x, double ini_y):x(ini_x),y(ini_y){}

  double getMagnitude() const { return sqrt(x * x + y * y); }

  Vector2D operator+(const Vector2D & rhs) const;
  Vector2D & operator+=(const Vector2D & rhs);

  double dot(const Vector2D & rhs) const { return x * rhs.x + y * rhs.y; }

  void print() const { printf("<%.2f, %.2f>", x, y); }
};
