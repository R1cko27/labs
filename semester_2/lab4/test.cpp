#include <iostream>
#include <string>
#include "Curriculum.h"

int main() {
    std::cout << "Тест №1" << std::endl;
    std::cout << "Входные данные - (\"09.03.03\", \"Прикладная информатика\", Curriculum::ResponsiblePerson::IVANOV_AV, 240, DegreeLevel::BACHELOR, 8);" << std::endl;
    try {
        Curriculum plan("09.03.03", "Прикладная информатика", 
                        Curriculum::ResponsiblePerson::IVANOV_AV, 240, 
                        DegreeLevel::BACHELOR, 8);
        std::cout << "Вывод: Объект создан, semesterCount = " << plan.getSemesterCount() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Вывод: " << e.what() << std::endl;
    }
    
    std::cout << "\nТест №2" << std::endl;
    std::cout << "Входные данные - (\"09.03.03\", \"Прикладная информатика\", Curriculum::ResponsiblePerson::IVANOV_AV, 240, DegreeLevel::BACHELOR, 0);" << std::endl;
    try {
        Curriculum plan("09.03.03", "Прикладная информатика", 
                        Curriculum::ResponsiblePerson::IVANOV_AV, 240, 
                        DegreeLevel::BACHELOR, 0);
        std::cout << "Вывод: Объект создан, semesterCount = " << plan.getSemesterCount() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Вывод: " << e.what() << std::endl;
    }
    
    std::cout << "\nТест №3" << std::endl;
    std::cout << "Входные данные - Curriculum plan(... 4); Discipline disc(\"Programming\", 6, 64, 32, 64, 32, AttestationType::EXAM); plan.addDiscipline(2, disc);" << std::endl;
    try {
        Curriculum plan("09.03.03", "Прикладная информатика", 
                        Curriculum::ResponsiblePerson::IVANOV_AV, 240, 
                        DegreeLevel::BACHELOR, 4);
        Discipline disc("Programming", 6, 64, 32, 64, 32, AttestationType::EXAM);
        plan.addDiscipline(2, disc);
        std::cout << "Вывод: Дисциплина добавлена во 2-й семестр" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Вывод: " << e.what() << std::endl;
    }
    
    std::cout << "\nТест №4" << std::endl;
    std::cout << "Входные данные - Discipline disc(\"Programming\", 6, 64, 32, 64, 20, AttestationType::EXAM);" << std::endl;
    try {
        Discipline disc("Programming", 6, 64, 32, 64, 20, AttestationType::EXAM);
        std::cout << "Вывод: Дисциплина создана" << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Вывод: " << e.what() << std::endl;
    }
    
    std::cout << "\nТест №5" << std::endl;
    std::cout << "Входные данные - Discipline disc(\"Programming\", 6, 64, -32, 64, 96, AttestationType::EXAM);" << std::endl;
    try {
        Discipline disc("Programming", 6, 64, -32, 64, 96, AttestationType::EXAM);
        std::cout << "Вывод: Дисциплина создана" << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Вывод: " << e.what() << std::endl;
    }
    
    std::cout << "\nТест №6" << std::endl;
    std::cout << "Входные данные - Discipline disc1(\"Databases\", 5, 64, 32, 64, 0, AttestationType::EXAM); Discipline disc2(\"Databases\", 4, 64, 32, 32, 0, AttestationType::EXAM); plan.addDiscipline(1, disc1); plan.addDiscipline(1, disc2);" << std::endl;
    try {
        Curriculum plan("09.03.03", "Прикладная информатика", 
                        Curriculum::ResponsiblePerson::IVANOV_AV, 240, 
                        DegreeLevel::BACHELOR, 4);
        Discipline disc1("Databases", 5, 64, 32, 64, 0, AttestationType::EXAM);
        Discipline disc2("Databases", 4, 64, 32, 32, 0, AttestationType::EXAM);
        plan.addDiscipline(1, disc1);
        plan.addDiscipline(1, disc2);
        std::cout << "Вывод: Дисциплина добавлена" << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Вывод: " << e.what() << std::endl;
    }
    
    std::cout << "\nТест №7" << std::endl;
    std::cout << "Входные данные - plan.addDiscipline(10, disc);" << std::endl;
    try {
        Curriculum plan("09.03.03", "Прикладная информатика", 
                        Curriculum::ResponsiblePerson::IVANOV_AV, 240, 
                        DegreeLevel::BACHELOR, 4);
        Discipline disc("Physics", 4, 64, 32, 32, 0, AttestationType::EXAM);
        plan.addDiscipline(10, disc);
        std::cout << "Вывод: Дисциплина добавлена" << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Вывод: " << e.what() << std::endl;
    }
    
    std::cout << "\nТест №8" << std::endl;
    std::cout << "Входные данные - plan.addDiscipline(3, disc); plan.removeDiscipline(3, \"OOP\");" << std::endl;
    try {
        Curriculum plan("09.03.03", "Прикладная информатика", 
                        Curriculum::ResponsiblePerson::IVANOV_AV, 240, 
                        DegreeLevel::BACHELOR, 4);
        Discipline disc("OOP", 6, 64, 32, 64, 32, AttestationType::EXAM);
        plan.addDiscipline(3, disc);
        plan.removeDiscipline(3, "OOP");
        std::cout << "Вывод: Дисциплина удалена" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Вывод: " << e.what() << std::endl;
    }
    
    std::cout << "\nТест №9" << std::endl;
    std::cout << "Входные данные - plan.removeDiscipline(1, \"NonExistent\");" << std::endl;
    try {
        Curriculum plan("09.03.03", "Прикладная информатика", 
                        Curriculum::ResponsiblePerson::IVANOV_AV, 240, 
                        DegreeLevel::BACHELOR, 4);
        plan.removeDiscipline(1, "NonExistent");
        std::cout << "Вывод: Дисциплина удалена" << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Вывод: " << e.what() << std::endl;
    }
    
    std::cout << "\nТест №10" << std::endl;
    std::cout << "Входные данные - plan.setSemesterCount(4); (было 6 семестров)" << std::endl;
    try {
        Curriculum plan("09.03.03", "Прикладная информатика", 
                        Curriculum::ResponsiblePerson::IVANOV_AV, 240, 
                        DegreeLevel::BACHELOR, 6);
        plan.setSemesterCount(4);
        std::cout << "Вывод: вектор семестров уменьшен до " << plan.getSemesterCount() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Вывод: " << e.what() << std::endl;
    }
    
    std::cout << "\nТест №11" << std::endl;
    std::cout << "Входные данные - plan.addDiscipline(6, disc); plan.setSemesterCount(5);" << std::endl;
    try {
        Curriculum plan("09.03.03", "Прикладная информатика", 
                        Curriculum::ResponsiblePerson::IVANOV_AV, 240, 
                        DegreeLevel::BACHELOR, 6);
        Discipline disc("English", 3, 32, 16, 32, 16, AttestationType::CREDIT);
        plan.addDiscipline(6, disc);
        plan.setSemesterCount(5);
        std::cout << "Вывод: вектор семестров уменьшен до " << plan.getSemesterCount() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Вывод: " << e.what() << std::endl;
    }
    
    std::cout << "\nТест №12" << std::endl;
    std::cout << "Входные данные - plan.addDiscipline(1, Discipline(\"Math\", 15, 160, 80, 160, 80, AttestationType::EXAM)); plan.addDiscipline(2, Discipline(\"Physics\", 15, 160, 80, 160, 80, AttestationType::EXAM)); plan.activate();" << std::endl;
    try {
        Curriculum plan("09.03.03", "Прикладная информатика", 
                        Curriculum::ResponsiblePerson::IVANOV_AV, 30, 
                        DegreeLevel::BACHELOR, 2);
        plan.addDiscipline(1, Discipline("Math", 15, 160, 80, 160, 80, AttestationType::EXAM));
        plan.addDiscipline(2, Discipline("Physics", 15, 160, 80, 160, 80, AttestationType::EXAM));
        bool result = plan.activate();
        if (result) {
            std::cout << "Вывод: result = true, состояние ACTIVE" << std::endl;
        } else {
            std::cout << "Вывод: Активация не удалась" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Вывод: " << e.what() << std::endl;
    }
    
    std::cout << "\nТест №13" << std::endl;
    std::cout << "Входные данные - plan.addDiscipline(1, Discipline(\"Math\", 15, 160, 80, 160, 80, AttestationType::EXAM)); plan.activate(); (2-й семестр пуст)" << std::endl;
    try {
        Curriculum plan("09.03.03", "Прикладная информатика", 
                        Curriculum::ResponsiblePerson::IVANOV_AV, 30, 
                        DegreeLevel::BACHELOR, 2);
        plan.addDiscipline(1, Discipline("Math", 15, 160, 80, 160, 80, AttestationType::EXAM));
        plan.activate();
        std::cout << "Вывод: План активирован" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Вывод: " << e.what() << std::endl;
    }
    
    std::cout << "\nТест №14" << std::endl;
    std::cout << "Входные данные - plan.addDiscipline(1, Discipline(\"Math\", 20, 240, 80, 240, 80, AttestationType::EXAM)); plan.addDiscipline(2, Discipline(\"Physics\", 20, 240, 80, 240, 80, AttestationType::EXAM)); plan.activate(); (сумма ЗЕ 40, целевые 240)" << std::endl;
    try {
        Curriculum plan("09.03.03", "Прикладная информатика", 
                        Curriculum::ResponsiblePerson::IVANOV_AV, 240, 
                        DegreeLevel::BACHELOR, 2);
        plan.addDiscipline(1, Discipline("Math", 20, 240, 80, 240, 80, AttestationType::EXAM));
        plan.addDiscipline(2, Discipline("Physics", 20, 240, 80, 240, 80, AttestationType::EXAM));
        plan.activate();
        std::cout << "Вывод: План активирован" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Вывод: " << e.what() << std::endl;
    }
    
    return 0;
}