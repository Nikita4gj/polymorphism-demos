// Ожидаемая ошибка компиляции: перегрузить только по типу возврата нельзя.
struct Circle { float r; };

float  area(const Circle& c);
double area(const Circle& c);   // error: ambiguating new declaration
