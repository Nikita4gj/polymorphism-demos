#pragma once

// Иерархия для динамической части лекции.
struct Shape {
    int id = 0;
    virtual float area() const { return 0.0f; }
    virtual ~Shape() = default;
};

struct Circle : Shape {
    float r = 1.0f;
    float area() const override { return 3.14159f * r * r; }
};

struct Square : Shape {
    float a = 2.0f;
    float area() const override { return a * a; }
};
