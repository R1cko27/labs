// Композиция — отношение «часть-целое», где время жизни части полностью управляется целым. 
//Без целого часть не существует.

class Engine {
public:
    Engine() { std::cout << "Engine created\n"; }
    ~Engine() { std::cout << "Engine destroyed\n"; }
};

class Car {
private:
    Engine engine; // Композиция (непосредственное вложение)
public:
    Car() { std::cout << "Car created\n"; }
    ~Car() { std::cout << "Car destroyed\n"; }
};

int main() {
    Car myCar; // Engine создается внутри Car, уничтожается вместе с Car
}
// Вывод: Engine created, Car created, Car destroyed, Engine destroyed