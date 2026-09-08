#include <iostream>
class Shape {
public:
    virtual void draw() { std::cout << "Drawing Shape\n"; }
    virtual ~Shape() = default; // Виртуальный деструктор
};

class Circle : public Shape {
public:
    void draw() override { std::cout << "Drawing Circle\n"; }
};

void render(Shape* s) {
    s->draw(); // Вызовется Circle::draw, т.к. функция виртуальная
}

int main() {
    Circle c;
    render(&c); // Drawing Circle, иначе Drawing Shape
}