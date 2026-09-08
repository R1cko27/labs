class PartA { public: PartA() { std::cout << "A "; } };
class PartB { public: PartB() { std::cout << "B "; } };

class Composite {
    PartB b; // Объявлен первым
    PartA a; // Объявлен вторым
public:
    Composite() : a(), b() { // Порядок вызовов НЕ зависит от списка инициализации
        std::cout << "Composite ";
    }
};

int main() {
    Composite c; // Вывод: B A Composite
}