#include <iostream>
#include <cstdlib>
class X {
public:
int y;
X(): y(7) {
std::cout << "X()\n";
}
X(int z): y(z) {
std::cout << "X(" << z << ")\n";
}
~X() {
std::cout << "~X(" << y << ")\n";
}
X & operator+=(const X & rhs) {
std::cout << "Doing " << y << " += " << rhs.y << "\n";
y += rhs.y;
return *this;
}
};
X f(X & y, X z) {
X ans(y);
ans += z;
y += ans;
z += ans;
return ans;
}
int main(void) {
X a;
X b(3);
X c = f(a, b);
std::cout << a.y << "\n";
std::cout << b.y << "\n";
std::cout << c.y << "\n";
getchar();
return EXIT_SUCCESS;
}