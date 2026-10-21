#include <cstdio>
#include "../shapes.hpp"

struct Printable {
    virtual void print() const = 0;
    virtual ~Printable() = default;
};

struct PrintableCircle : Circle, Printable {
    void print() const override;
};

void PrintableCircle::print() const { std::printf("круг, r = %.2f\n", r); }

void show(const Printable& p) { p.print(); }   // вызов через вторую базу
void destroy(Printable* p)    { delete p; }    // удаление через вторую базу
