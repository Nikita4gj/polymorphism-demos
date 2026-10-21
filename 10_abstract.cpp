// Ожидаемая ошибка компиляции: абстрактную базу нельзя передать по значению.
struct Shape {
    virtual float area() const = 0;
    virtual ~Shape() = default;
};

void by_value(Shape s) {}   // error: cannot declare parameter 's' to be of abstract type 'Shape'
