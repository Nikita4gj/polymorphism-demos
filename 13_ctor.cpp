#include <cstdio>

struct Shape {
    Shape() { std::printf("в Shape():  %.2f\n", area()); }
    virtual float area() const { return 0.0f; }
    virtual ~Shape() = default;
};

struct Circle : Shape {
    float r = 1.0f;
    Circle() { std::printf("в Circle(): %.2f\n", area()); }
    float area() const override { return 3.14159f * r * r; }
};

int main() { Circle c; }
