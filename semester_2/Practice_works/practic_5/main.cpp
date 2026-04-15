#include "study_group.h"

int main() {
    // Создаем группу 1 с заданными значениями
    StudentGroup group1("AP-526", PI, 2025, BACHELOR);
    
    // Проверяем и выводим информацию о группе
    if (StudentGroup::validate_group(group1)) {
        group1.print();
    } else {
        std::cout << "Некорректные данные для группы 1" << std::endl;
    }

    // Создаем группу 2 с другими значениями
    StudentGroup group2("AB-420", IS, 2024, MASTER);

    // Проверяем и выводим информацию о группе
    if (StudentGroup::validate_group(group2)) {
        group2.print();
    } else {
        std::cout << "Некорректные данные для группы 2" << std::endl;
    }

    // Копируем группу 1 в группу 3
    StudentGroup group3 = group1;
    group3.print();

    // Переименовываем группу 1
    group1.rename("AP-527");
    group1.print();

    return 0;
}