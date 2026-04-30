#include <iostream>
#include "Curriculum.h"

// void testTable1() {
//     std::cout << "=== Таблица 1: Проверка конструктора ===\n\n";
    
//     // Тест 1
//     std::cout << "1. Входные данные: (\"недействительная_группа\", \"Информатика\", \"Панфилов А.П.\", 240, BACHELOR)\n";
//     try {
//         Curriculum c("недействительная_группа", "Информатика", "Панфилов А.П.", 240, Curriculum::DegreeLevel::BACHELOR);
//         std::cout << "Результат: Ошибок нет\n\n";
//     } catch (const std::invalid_argument& e) {
//         std::cout << "Результат: " << e.what() << "\n\n";
//     }
    
//     // Тест 2
//     std::cout << "2. Входные данные: (\"09.03.03\", \"\", \"Иманкулов С.А.\", 120, MASTER)\n";
//     try {
//         Curriculum c("09.03.03", "", "Иманкулов С.А.", 120, Curriculum::DegreeLevel::MASTER);
//         std::cout << "Результат: Ошибок нет\n\n";
//     } catch (const std::invalid_argument& e) {
//         std::cout << "Результат: " << e.what() << "\n\n";
//     }
    
//     // Тест 3
//     std::cout << "3. Входные данные: (\"09.03.03\", \"Физика!\", \"Иманкулов С.А.\", 245, MASTER)\n";
//     try {
//         Curriculum c("09.03.03", "Физика!", "Иманкулов С.А.", 245, Curriculum::DegreeLevel::MASTER);
//         std::cout << "Результат: Ошибок нет\n\n";
//     } catch (const std::invalid_argument& e) {
//         std::cout << "Результат: " << e.what() << "\n\n";
//     }
    
//     // Тест 4
//     std::cout << "4. Входные данные: (\"09.03.03\", \"Прикладная информатика\", \"\", 245, MASTER)\n";
//     try {
//         Curriculum c("09.03.03", "Прикладная информатика", "", 245, Curriculum::DegreeLevel::MASTER);
//         std::cout << "Результат: Ошибок нет\n\n";
//     } catch (const std::invalid_argument& e) {
//         std::cout << "Результат: " << e.what() << "\n\n";
//     }
    
//     // Тест 5
//     std::cout << "5. Входные данные: (\"09.03.03\", \"Прикладная информатика\", \"Иманкулов С.А.\", -50, MASTER)\n";
//     try {
//         Curriculum c("09.03.03", "Прикладная информатика", "Иманкулов С.А.", -50, Curriculum::DegreeLevel::MASTER);
//         std::cout << "Результат: Ошибок нет\n\n";
//     } catch (const std::invalid_argument& e) {
//         std::cout << "Результат: " << e.what() << "\n\n";
//     }
    
//     // Тест 6
//     std::cout << "6. Входные данные: (\"09.03.03\", \"Прикладная информатика\", \"Иманкулов С.А.\", 0, MASTER)\n";
//     try {
//         Curriculum c("09.03.03", "Прикладная информатика", "Иманкулов С.А.", 0, Curriculum::DegreeLevel::MASTER);
//         std::cout << "Результат: Ошибок нет\n\n";
//     } catch (const std::invalid_argument& e) {
//         std::cout << "Результат: " << e.what() << "\n\n";
//     }
    
//     // Тест 7
//     std::cout << "7. Входные данные: (\"09.03.03\", \"Прикладная информатика\", \"Иманкулов С.А.\", 600, MASTER)\n";
//     try {
//         Curriculum c("09.03.03", "Прикладная информатика", "Иманкулов С.А.", 600, Curriculum::DegreeLevel::MASTER);
//         std::cout << "Результат: Ошибок нет\n\n";
//     } catch (const std::invalid_argument& e) {
//         std::cout << "Результат: " << e.what() << "\n\n";
//     }
    
//     // Тест 8
//     std::cout << "8. Входные данные: (\"09.03.03\", \"Прикладная информатика\", \"Иманкулов С.А.\", 245, MASTER)\n";
//     try {
//         Curriculum c("09.03.03", "Прикладная информатика", "Иманкулов С.А.", 245, Curriculum::DegreeLevel::MASTER);
//         std::cout << "Результат: Ошибок нет, объект создан\n\n";
//     } catch (const std::invalid_argument& e) {
//         std::cout << "Результат: " << e.what() << "\n\n";
//     }
// }

void testTable2() {
    std::cout << "=== Таблица 2: Тестирование активации ===\n\n";
    
    // Тест 1
    std::cout << "1. disciplineCount=0, totalDisciplineCredits=0, targetCredits=245\n";
    Curriculum c1("10.01.01", "Тест", "Иванов И.И.", 245, Curriculum::DegreeLevel::BACHELOR);
    c1.setDisciplinesInfo(0, 0);
    bool result = c1.activate();
    std::cout << "Результат: " << (result ? "true" : "false") << "\n\n";
    
    // Тест 2
    std::cout << "2. disciplineCount=50, totalDisciplineCredits=100, targetCredits=245\n";
    Curriculum c2("10.01.01", "Тест", "Иванов И.И.", 245, Curriculum::DegreeLevel::BACHELOR);
    c2.setDisciplinesInfo(50, 100);
    result = c2.activate();
    std::cout << "Результат: " << (result ? "true" : "false") << "\n\n";
    
    // Тест 3
    std::cout << "3. disciplineCount=0, totalDisciplineCredits=50, targetCredits=245\n";
    Curriculum c3("10.01.01", "Тест", "Иванов И.И.", 245, Curriculum::DegreeLevel::BACHELOR);
    try {
        c3.setDisciplinesInfo(0, 50);
    } catch (const std::invalid_argument& e) {
        std::cout << "Ошибка при setDisciplinesInfo: " << e.what() << "\n";
    }
    result = c3.activate();
    std::cout << "Результат активации: " << (result ? "true" : "false") << "\n\n";
    
    // Тест 4
    std::cout << "4. disciplineCount=50, totalDisciplineCredits=245, targetCredits=245\n";
    Curriculum c4("10.01.01", "Тест", "Иванов И.И.", 245, Curriculum::DegreeLevel::BACHELOR);
    c4.setDisciplinesInfo(50, 245);
    result = c4.activate();
    std::cout << "Результат: " << (result ? "true" : "false") << "\n\n";
    
    // Тест 5
    std::cout << "5. disciplineCount=0, totalDisciplineCredits=0, targetCredits=0\n";
    Curriculum c5("10.01.01", "Тест", "Иванов И.И.", 0, Curriculum::DegreeLevel::BACHELOR);
    c5.setDisciplinesInfo(0, 0);
    result = c5.activate();
    std::cout << "Результат: " << (result ? "true" : "false") << "\n\n";
}

void testTable3() {
    std::cout << "=== Таблица 3: Тестирование сеттеров ===\n\n";
    
    Curriculum c;
    
    // Тест 1
    std::cout << "1. setCode(\"090303\")\n";
    try {
        c.setCode("090303");
        std::cout << "Результат: Ошибок нет\n\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Результат: " << e.what() << "\n\n";
    }
    
    // Тест 2
    std::cout << "2. setTitle(\"\")\n";
    try {
        c.setTitle("");
        std::cout << "Результат: Ошибок нет\n\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Результат: " << e.what() << "\n\n";
    }
    
    // Тест 3
    std::cout << "3. setResponsiblePerson(\"\")\n";
    try {
        c.setResponsiblePerson("");
        std::cout << "Результат: Ошибок нет\n\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Результат: " << e.what() << "\n\n";
    }
    
    // Тест 4
    std::cout << "4. setTargetCredits(-10)\n";
    try {
        c.setTargetCredits(-10);
        std::cout << "Результат: Ошибок нет\n\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Результат: " << e.what() << "\n\n";
    }
    
    // Тест 5
    std::cout << "5. setTargetCredits(600)\n";
    try {
        c.setTargetCredits(600);
        std::cout << "Результат: Ошибок нет\n\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Результат: " << e.what() << "\n\n";
    }
    
    // Тест 6
    std::cout << "6. setDisciplinesInfo(0, 245)\n";
    try {
        c.setDisciplinesInfo(0, 245);
        std::cout << "Результат: Ошибок нет\n\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Результат: " << e.what() << "\n\n";
    }
    
    // Тест 7
    std::cout << "7. setDisciplinesInfo(5, 0)\n";
    try {
        c.setDisciplinesInfo(5, 0);
        std::cout << "Результат: Ошибок нет\n\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Результат: " << e.what() << "\n\n";
    }
    
    // Тест 8
    std::cout << "8. setDisciplinesInfo(-3, 245)\n";
    try {
        c.setDisciplinesInfo(-3, 245);
        std::cout << "Результат: Ошибок нет\n\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Результат: " << e.what() << "\n\n";
    }
    
    // Тест 9
    std::cout << "9. setDisciplinesInfo(30, -10)\n";
    try {
        c.setDisciplinesInfo(30, -10);
        std::cout << "Результат: Ошибок нет\n\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Результат: " << e.what() << "\n\n";
    }
}

int main() {
    // testTable1();
    testTable2();
    testTable3();
    return 0;
}