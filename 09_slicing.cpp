#include <cstdio>
#include "shapes.hpp"

float by_value(Shape s)      { return s.area(); }
float by_ref(const Shape& s) { return s.area(); }

int main() {
    Circle c;
    std::printf("по значению: %.2f\n", by_value(c));   // 0.00
    std::printf("по ссылке:   %.2f\n", by_ref(c));     // 3.14
}
