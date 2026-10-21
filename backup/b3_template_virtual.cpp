// Ожидаемая ошибка компиляции: член-шаблон не может быть виртуальным.
struct Shape {
    template <class T>
    virtual void scale(T k);   // error: templates may not be 'virtual'
};
