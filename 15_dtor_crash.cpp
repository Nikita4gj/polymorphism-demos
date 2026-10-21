#include <cstdio>
#include "shapes.hpp"

struct Printable {
    virtual void print() const = 0;
    ~Printable() = default;   // НЕ virtual
};

struct PrintableCircle : Circle, Printable {
    void print() const override;
};

void PrintableCircle::print() const { std::printf("круг, r = %.2f\n", r); }

int main() {
    auto* c = new PrintableCircle;
    Printable* p = c;
    std::printf("new вернул     %p\n", static_cast<void*>(c));
    std::printf("delete получит %p\n", static_cast<void*>(p));
    delete p;   // падение: адрес не тот, что вернул new
}
