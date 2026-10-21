#include <cstdio>

template <class Derived>
struct Shape {
    int id = 0;
    float area() const {
        return static_cast<const Derived&>(*this).area_impl();
    }
};

struct Circle : Shape<Circle> {
    float r = 1.0f;
    float area_impl() const { return 3.14159f * r * r; }
};

struct Square : Shape<Square> {
    float a = 2.0f;
    float area_impl() const { return a * a; }
};

template <class D>
void print_area(const Shape<D>& s) {
    std::printf("%.2f\n", s.area());
}

int main() {
    print_area(Circle{});   // 3.14
    print_area(Square{});   // 4.00
    std::printf("sizeof(Circle) = %zu\n", sizeof(Circle));   // 8: vptr нет
}
