#include "shapes.hpp"

struct FinalCircle final : Shape {
    float r = 1.0f;
    float area() const override { return 3.14159f * r * r; }
};

namespace crtp {
template <class Derived>
struct Shape {
    int id = 0;
    float area() const { return static_cast<const Derived&>(*this).area_impl(); }
};

struct Circle : Shape<Circle> {
    float r = 1.0f;
    float area_impl() const { return 3.14159f * r * r; }
};
}  // namespace crtp

float via_virtual(const Shape& s)      { return s.area(); }
float via_final(const FinalCircle& c)  { return c.area(); }
float via_crtp(const crtp::Circle& c)  { return c.area(); }
