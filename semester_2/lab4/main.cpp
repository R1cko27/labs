#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <memory>
#include "Curriculum.h"

Curriculum testfunc(Curriculum c) {
    std::cout << "Вызвана функция testfunc" << std::endl;
    (void)c;
    Curriculum plan("10.03.01", "Информационная безопасность", 
                    Curriculum::ResponsiblePerson::TOMILOV_IN, 240, 
                    Curriculum::DegreeLevel::BACHELOR, 2);
    return plan;
}

int main() {
    try {
        Curriculum invalidPlan("недействительная_группа", "",  Curriculum::ResponsiblePerson::TOMILOV_IN, -1, Curriculum::DegreeLevel::BACHELOR, 1);
    } catch (const std::invalid_argument& e) {
        std::cout << "Перехваченное исключение:\n" << e.what() << std::endl;
    }
    try {
        Curriculum plan0;
        plan0.print();

        Curriculum plan("10.03.01", "Информационная безопасность", 
                        Curriculum::ResponsiblePerson::TOMILOV_IN, 240, 
                        Curriculum::DegreeLevel::BACHELOR, 2);
        plan.print();

        plan.setCode("09.03.03");
        plan.setTitle("Прикладная информатика");
        plan.setResponsiblePerson(Curriculum::ResponsiblePerson::PAVLOV_AV);

        plan.addDiscipline(1, Discipline("Calculus", 7, 72, 0, 72, 80, AttestationType::EXAM));
        plan.addDiscipline(1, Discipline("Computer Science", 5, 18, 18, 36, 88, AttestationType::EXAM));
        plan.addDiscipline(1, Discipline("Linear Algebra", 4, 36, 0, 36, 56, AttestationType::EXAM));
        plan.addDiscipline(1, Discipline("Russian History", 4, 72, 0, 36, 20, AttestationType::EXAM));

        plan.addDiscipline(2, Discipline("Discrete Mathematics", 4, 18, 0, 36, 74, AttestationType::CREDIT));
        plan.addDiscipline(2, Discipline("Calculus", 6, 72, 0, 72, 48, AttestationType::EXAM));
        plan.addDiscipline(2, Discipline("Programming", 5, 36, 18, 18, 88, AttestationType::EXAM));
        plan.addDiscipline(2, Discipline("Probability Theory and Mathematical Statistics", 4, 36, 0, 18, 74, AttestationType::EXAM));

            
        if (plan.activate())
            std::cout << "\nПлан активирован\n" << std::endl;
        else 
            std::cout << "\nОшибка активации: сумма ЗЕ дисциплин не соответствует целевым ЗЕ\n" << std::endl;

        plan.print();

        Curriculum plan2("10.03.01", "Программная инженерия", 
                        Curriculum::ResponsiblePerson::IVANOV_AV, 39, 
                        Curriculum::DegreeLevel::MASTER, 2);
        
        if (!plan2.activate()) {
            std::cout << "\nplan2 не активирован, потому что семестры пустые." << std::endl;
        }

        plan2.addDiscipline(1, Discipline("Calculus", 7, 72, 0, 72, 80, AttestationType::EXAM));
        plan2.addDiscipline(1, Discipline("Programming", 5, 36, 18, 18, 88, AttestationType::EXAM));
        plan2.addDiscipline(1, Discipline("Linear Algebra", 4, 36, 0, 36, 56, AttestationType::EXAM));
        plan2.addDiscipline(1, Discipline("Discrete Mathematics", 4, 18, 0, 36, 74, AttestationType::EXAM));

        plan2.addDiscipline(2, Discipline("Calculus", 6, 72, 0, 72, 48, AttestationType::EXAM));
        plan2.addDiscipline(2, Discipline("Russian History", 4, 72, 0, 36, 20, AttestationType::EXAM));
        plan2.addDiscipline(2, Discipline("Computer Science", 5, 18, 18, 36, 88, AttestationType::EXAM));
        plan2.addDiscipline(2, Discipline("Probability Theory and Mathematical Statistics", 4, 36, 0, 18, 74, AttestationType::CREDIT));

        try {
            plan2.addDiscipline(1, Discipline("Calculus", 7, 72, 0, 72, 80, AttestationType::EXAM));
        } catch (const std::invalid_argument& e) {
            std::cout << "\nПерехваченное ОЖИДАЕМОЕ исключение при добавлении дисциплины: " << e.what() << std::endl;
        }

        if (plan2.activate()) {
            std::cout << "\nplan2 активирован\n" << std::endl;
        }

        plan2.print();

        plan.printSemesterDetails(1);
        plan2.printSemesterDetails(1);

        // Демонстрация работы с контейнерами по указателю
        Curriculum* plan3 = new Curriculum("09.03.03", "Прикладная информатика", Curriculum::ResponsiblePerson::IVANOV_AV, 18, Curriculum::DegreeLevel::MASTER, 2);
        plan3->addDiscipline(1, Discipline("Теория вероятностей", 8, 96, 64, 96, 0, AttestationType::EXAM));
        plan3->addDiscipline(2, Discipline("Программная инженерия", 10, 128, 96, 96, 0, AttestationType::EXAM));
        // plan3->print();
        delete plan3;

        // Демонстрация работы с контейнерами по значению
        std::vector<Curriculum> curricula(3);
        for (auto& curriculum : curricula) {
            // curriculum.print();
        }
        
        // Демонстрация работы с контейнерами по указателю
        std::vector<Curriculum*> curricularPtrs(3);
        for (int i = 0; i < 3; ++i) {
            curricularPtrs[i] = new Curriculum();
            // curricularPtrs[i]->print();
            delete curricularPtrs[i];
        }

        // Демонстрация работы с контейнерами по умному указателю
        std::vector<std::unique_ptr<Curriculum>> curriculumPtrs;
        curriculumPtrs.reserve(3);
        for (int i = 0; i < 3; ++i) {
            curriculumPtrs.push_back(std::make_unique<Curriculum>());
            // curriculumPtrs[i]->print();
        }

    } catch (const std::exception& e) {
        std::cerr << "Непредвиденная ошибка:\n" << e.what() << std::endl;
        return 1;
    }
    return 0;
}