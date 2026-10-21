#include <cstdio>
#include <memory>
#include <vector>
#include "shapes.hpp"

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>());
    shapes.push_back(std::make_unique<Square>());

    for (const auto& s : shapes)
        std::printf("%.2f\n", s->area());   // 3.14, затем 4.00
}
