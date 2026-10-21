#include "shapes.hpp"

Circle c;
Shape* s = &c;

float via_object()  { return c.area(); }   // тип известен компилятору
float via_pointer() { return s->area(); }  // тип узнаём во время работы
