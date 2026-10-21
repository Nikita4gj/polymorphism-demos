#include <cstdio>

struct Shape {
    virtual float area() const { return 0.0f; }
    ~Shape() { std::puts("~Shape"); }            // деструктор НЕ virtual
};

struct Circle : Shape {
    float r = 1.0f;
    float area() const override { return 3.14159f * r * r; }
    ~Circle() { std::puts("~Circle"); }
};

int main() {
    Shape* s = new Circle;
    delete s;   // печатает только ~Shape
}
