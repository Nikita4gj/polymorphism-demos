// Ожидаемая ошибка компиляции: без манглинга две area не различить.
struct Circle { float r; };
struct Square { float a; };

extern "C" float area(const Circle&);
extern "C" float area(const Square&);   // error: conflicting declaration of C function
