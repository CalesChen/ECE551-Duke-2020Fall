#include <cstdio>
#include <cstdlib>
class A {
int x;
public:
A() : x(0) { printf("A default\n"); }
explicit A(int x_in) : x(x_in) { printf("A with %d\n", x); }
A(const A & rhs) : x(rhs.x) { printf("A copy ctor\n"); }
A & operator=(const A & rhs) {
printf("A op=, %d->%d\n", x, rhs.x);
if (this != &rhs) {
x = rhs.x;
}
return *this;
}
};
class B1 {
A y;
public:
B1() : y(A(1)) { printf("B1 default\n"); }
B1(const B1 & rhs) : y(rhs.y) { printf("B1 copy ctor\n"); }
};
class B2 {
A y;
public:
B2() {
printf("B2 default\n");
y = A(2);
}
B2(const B2 & rhs) {
printf("B2 copy ctor\n");
y = rhs.y;
}
};
int main(void) {
B1 b1;
B2 b2;
B1 b3(b1);
B2 b4(b2);
getchar();
return EXIT_SUCCESS;
}