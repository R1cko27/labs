//Наследование — отношение «является» (is-a), когда производный класс расширяет или изменяет поведение базового.

class Animal {
public:
    void breathe() { std::cout << "Breathing\n"; }
};

class Dog : public Animal {
public:
    void bark() { std::cout << "Woof!\n"; }
};

int main() {
    Dog d;
    d.breathe(); // Унаследовано
    d.bark();    // Свое
}