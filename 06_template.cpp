#include <cstdio>

struct Circle { float r; };
struct Square { float a; };

float area(const Circle& c) { return 3.14159f * c.r * c.r; }
float area(const Square& s) { return s.a * s.a; }

template <class S>
void print_area(const S& s) {
    std::printf("%.2f\n", area(s));
}

int main() {
    print_area(Circle{1.0f});   // print_area<Circle>
    print_area(Square{2.0f});   // print_area<Square>
}
