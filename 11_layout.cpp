#include "shapes.hpp"

static_assert(sizeof(Shape)  == 16);
static_assert(sizeof(Circle) == 16);   // поле r легло в хвост Shape

Circle c;   // чтобы компилятор построил vtable Circle
