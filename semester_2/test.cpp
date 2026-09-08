#include <ctime>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>


class Student{
    private:
        std::string name;
        int age;
    public:
        Student(std::string n, int a) : name(n), age(a) {
            if (a < 0 || n.size() < 1){
                throw std::invalid_argument("Ошибка входных данных");
            };
        }
        Student() : name("No name"), age(25){}
        Student(const Student& other) : name(other.name), age(other.age){}
        Student& operator=(const Student& other){
            age = other.age;
            return *this;
        }
        ~Student(){}

        void print(){
            std::cout << "Name : " << name << '\n' << "Age : " << age << std::endl;
        }
        bool operator==(const Student& other){
            return (age == other.age);
        }
        void setAge(int a){
            if (a > 0){age = a;}
        }
        void setName(std::string n){
            name = n;
        }
        Student& BirthDay(){
            age++;
            return *this;
        }
        friend Student& happyday(Student& a, int age);
};

Student& happyday(Student& a, int age){
    a.age+= age;
    return a;
}
Student* createStudent(){
    Student* s = new Student("Michail", 19);
    return s;
}

Student createStudent2(){
    Student a;
    return a;
}

int main(){

    // Student* aptr = new Student();
    // Student* bptr = new Student("Artem", 18);
    // aptr->print();
    // bptr->print();

    // Student* arr[10];
    // for (int age=18, i = 0; i < 10; i++, age++){
    //     arr[i] = new Student();
    //     arr[i]->setAge(age);
    // }
    // for (int i = 0; i < 10; i++){
    //     arr[i]->print();
    // }
    // delete aptr;
    // delete bptr;
    // for (int i = 0; i < 10; i++) {
    //     delete arr[i];
    // }

    Student a;
    Student* aptr = &a;
    aptr->print();
    // a.print();
    // a.BirthDay().BirthDay().BirthDay().BirthDay().BirthDay();
    // a.print();
    // Student* a = createStudent();
    // Student b = createStudent2();
    happyday(a, 10);
    a.print();
}