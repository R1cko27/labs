#include <iostream>
#include <string>
#include "Curriculum.h"
#include "Discipline.h"

void printTestHeader(int testNumber, const std::string& description) {
    std::cout << "Тест №" << testNumber << std::endl;
    std::cout << "Входные данные - " << description << std::endl;
    std::cout << "Вывод: ";
}

int main() {
    int testNum = 1;

    // Тест №1
    {
        printTestHeader(testNum++, "(\"09.03.03\", \"Прикладная информатика\", Curriculum::ResponsiblePerson::IVANOV_AV, 240, DegreeLevel::BACHELOR, 8);");
        try {
            Curriculum plan("09.03.03", "Прикладная информатика", 
                           Curriculum::ResponsiblePerson::IVANOV_AV, 
                           240, DegreeLevel::BACHELOR, 8);
            std::cout << "Объект создан, semesterCount = " << plan.getSemesterCount() << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    // Тест №2
    {
        printTestHeader(testNum++, "(\"09.03.03\", \"Прикладная информатика\", Curriculum::ResponsiblePerson::IVANOV_AV, 240, DegreeLevel::BACHELOR, 0);");
        try {
            Curriculum plan("09.03.03", "Прикладная информатика", 
                           Curriculum::ResponsiblePerson::IVANOV_AV, 
                           240, DegreeLevel::BACHELOR, 0);
            std::cout << "Объект создан, semesterCount = " << plan.getSemesterCount() << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    // Тест №3 - Добавление корректной дисциплины в семестр
    {
        printTestHeader(testNum++, "Curriculum plan(... 4);\nDiscipline disc(\"Программирование\", 6, DegreeLevel::BACHELOR);\nplan.addDiscipline(2, disc);");
        try {
            Curriculum plan("09.03.03", "Прикладная информатика", 
                           Curriculum::ResponsiblePerson::IVANOV_AV, 
                           240, DegreeLevel::BACHELOR, 4);
            Discipline disc("Программирование", 6, DegreeLevel::BACHELOR);
            plan.addDiscipline(2, disc);
            std::cout << "Дисциплина добавлена во 2-й семестр" << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    // Тест №4 - Добавление дисциплины с несовпадающей ступенью
    {
        printTestHeader(testNum++, "Curriculum plan(... 4);\nDiscipline disc(\"Высшая математика\", 8, DegreeLevel::MASTER);\nplan.addDiscipline(1, disc);");
        try {
            Curriculum plan("09.03.03", "Прикладная информатика", 
                           Curriculum::ResponsiblePerson::IVANOV_AV, 
                           240, DegreeLevel::BACHELOR, 4);
            Discipline disc("Высшая математика", 8, DegreeLevel::MASTER);
            plan.addDiscipline(1, disc);
            std::cout << "Дисциплина добавлена в 1-й семестр" << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    // Тест №5 - Добавление дублирующейся дисциплины в тот же семестр
    {
        printTestHeader(testNum++, "Curriculum plan(... 4);\nDiscipline disc1(\"Базы данных\", 5, DegreeLevel::BACHELOR);\nDiscipline disc2(\"Базы данных\", 4, DegreeLevel::BACHELOR);\nplan.addDiscipline(1, disc1);\nplan.addDiscipline(1, disc2);");
        try {
            Curriculum plan("09.03.03", "Прикладная информатика", 
                           Curriculum::ResponsiblePerson::IVANOV_AV, 
                           240, DegreeLevel::BACHELOR, 4);
            Discipline disc1("Базы данных", 5, DegreeLevel::BACHELOR);
            Discipline disc2("Базы данных", 4, DegreeLevel::BACHELOR);
            plan.addDiscipline(1, disc1);
            std::cout << "Первое добавление успешно. ";
            plan.addDiscipline(1, disc2);
            std::cout << "Второе добавление успешно" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Второе с ошибкой - " << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    // Тест №6 - Добавление дисциплины в несуществующий семестр
    {
        printTestHeader(testNum++, "Curriculum plan(... 4);\nDiscipline disc(\"Физика\", 4, DegreeLevel::BACHELOR);\nplan.addDiscipline(10, disc);");
        try {
            Curriculum plan("09.03.03", "Прикладная информатика", 
                           Curriculum::ResponsiblePerson::IVANOV_AV, 
                           240, DegreeLevel::BACHELOR, 4);
            Discipline disc("Физика", 4, DegreeLevel::BACHELOR);
            plan.addDiscipline(10, disc);
            std::cout << "Дисциплина добавлена в 10-й семестр" << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    // Тест №7 - Удаление существующей дисциплины
    {
        printTestHeader(testNum++, "Curriculum plan(... 4);\nDiscipline disc(\"ООП\", 6, DegreeLevel::BACHELOR);\nplan.addDiscipline(3, disc);\nplan.removeDiscipline(3, \"ООП\");");
        try {
            Curriculum plan("09.03.03", "Прикладная информатика", 
                           Curriculum::ResponsiblePerson::IVANOV_AV, 
                           240, DegreeLevel::BACHELOR, 4);
            Discipline disc("ООП", 6, DegreeLevel::BACHELOR);
            plan.addDiscipline(3, disc);
            plan.removeDiscipline(3, "ООП");
            std::cout << "Дисциплина удалена" << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    // Тест №8 - Удаление несуществующей дисциплины
    {
        printTestHeader(testNum++, "Curriculum plan(... 4);\nplan.removeDiscipline(1, \"Несуществующая дисциплина\");");
        try {
            Curriculum plan("09.03.03", "Прикладная информатика", 
                           Curriculum::ResponsiblePerson::IVANOV_AV, 
                           240, DegreeLevel::BACHELOR, 4);
            plan.removeDiscipline(1, "Несуществующая дисциплина");
            std::cout << "Дисциплина удалена" << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    // Тест №9 - Уменьшение количества семестров (без дисциплин в удаляемых)
    {
        printTestHeader(testNum++, "Curriculum plan(... 6);\nplan.setSemesterCount(4);");
        try {
            Curriculum plan("09.03.03", "Прикладная информатика", 
                           Curriculum::ResponsiblePerson::IVANOV_AV, 
                           240, DegreeLevel::BACHELOR, 6);
            plan.setSemesterCount(4);
            std::cout << "вектор семестров уменьшен до " << plan.getSemesterCount() << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    // Тест №10 - Уменьшение количества семестров (с дисциплинами в удаляемых)
    {
        printTestHeader(testNum++, "Curriculum plan(... 6);\nDiscipline disc(\"Английский язык\", 3, DegreeLevel::BACHELOR);\nplan.addDiscipline(6, disc);\nplan.setSemesterCount(5);");
        try {
            Curriculum plan("09.03.03", "Прикладная информатика", 
                           Curriculum::ResponsiblePerson::IVANOV_AV, 
                           240, DegreeLevel::BACHELOR, 6);
            Discipline disc("Английский язык", 3, DegreeLevel::BACHELOR);
            plan.addDiscipline(6, disc);
            plan.setSemesterCount(5);
            std::cout << "Количество семестров уменьшено до " << plan.getSemesterCount() << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    // Тест №11 - Активация плана с полностью заполненными семестрами и суммой ЗЕ
    {
        printTestHeader(testNum++, "Curriculum plan(... 2);\nDiscipline d1(\"Math\", 15, DegreeLevel::BACHELOR);\nDiscipline d2(\"Physics\", 15, DegreeLevel::BACHELOR);\nplan.addDiscipline(1, d1);\nplan.addDiscipline(2, d2);\nbool result = plan.activate();");
        try {
            Curriculum plan("09.03.03", "Прикладная информатика", 
                           Curriculum::ResponsiblePerson::IVANOV_AV, 
                           240, DegreeLevel::BACHELOR, 6);
            Discipline d1("Math", 15, DegreeLevel::BACHELOR);
            Discipline d2("Physics", 15, DegreeLevel::BACHELOR);
            plan.addDiscipline(1, d1);
            plan.addDiscipline(2, d2);
            bool result = plan.activate();
            std::cout << "result = " << (result ? "true" : "false") 
                      << ", состояние " << plan.getStateString();
            
            // Проверка, что после активации добавление вызывает исключение
            try {
                Discipline d3("NewDisc", 5, DegreeLevel::BACHELOR);
                plan.addDiscipline(1, d3);
            } catch (const std::logic_error& e) {
                std::cout << ", после этого добавление/удаление дисциплин вызывает std::logic_error";
            }
            std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    // Тест №12 - Активация плана с пустым семестром
    {
        printTestHeader(testNum++, "Curriculum plan(... 2);\nDiscipline d1(\"Math\", 15, DegreeLevel::BACHELOR);\nplan.addDiscipline(1, d1);\nbool result = plan.activate();");
        try {
            Curriculum plan("09.03.03", "Прикладная информатика", 
                           Curriculum::ResponsiblePerson::IVANOV_AV, 
                           240, DegreeLevel::BACHELOR, 6);
            Discipline d1("Math", 15, DegreeLevel::BACHELOR);
            plan.addDiscipline(1, d1);
            bool result = plan.activate();
            std::cout << "result = " << (result ? "true" : "false") << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    // Тест №13 - Активация плана, где сумма ЗЕ дисциплин не равна целевым
    {
        printTestHeader(testNum++, "Curriculum plan(\"09.03.03\", \"Прикладная информатика\", Curriculum::ResponsiblePerson::IVANOV_AV, 50, DegreeLevel::BACHELOR, 2);\nDiscipline d1(\"Math\", 20, DegreeLevel::BACHELOR);\nDiscipline d2(\"Physics\", 20, DegreeLevel::BACHELOR);\nplan.addDiscipline(1, d1);\nplan.addDiscipline(2, d2);\nbool result = plan.activate();");
        try {
            Curriculum plan("09.03.03", "Прикладная информатика", 
                           Curriculum::ResponsiblePerson::IVANOV_AV, 
                           240, DegreeLevel::BACHELOR, 6);
            Discipline d1("Math", 20, DegreeLevel::BACHELOR);
            Discipline d2("Physics", 20, DegreeLevel::BACHELOR);
            plan.addDiscipline(1, d1);
            plan.addDiscipline(2, d2);
            bool result = plan.activate();
            std::cout << "result = " << (result ? "true" : "false") << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}