#include <cstdio>

struct Circle { float r; };
struct Square { float a; };

float area(const Circle& c) { return 3.14159f * c.r * c.r; }
float area(const Square& s) { return s.a * s.a; }

int main() {
    std::printf("%.2f\n", area(Circle{1.0f}));   // 3.14
    std::printf("%.2f\n", area(Square{2.0f}));   // 4.00
}
