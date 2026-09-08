class Base {
public:
    Base(int x) { std::cout << "Base " << x << "\n"; }
};

class Member {
public:
    Member(int x) { std::cout << "Member " << x << "\n"; }
};

class Derived : public Base {
    Member m;
public:
    Derived(int a, int b) : Base(a), m(b) {
        std::cout << "Derived\n";
    }
};

int main() {
    Derived d(1, 2);
}
// Вывод: Base 1, Member 2, Derived