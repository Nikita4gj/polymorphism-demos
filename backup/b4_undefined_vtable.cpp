// Ожидаемая ошибка линковки: undefined reference to `vtable for Shape'.
struct Shape {
    virtual float area() const;   // тела нет нигде
    virtual ~Shape() = default;
};

int main() { Shape s; }
