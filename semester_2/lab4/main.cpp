#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <memory>
#include "Curriculum.h"


int main() {
    try {
        Curriculum invalidPlan("недействительная_группа", "", Curriculum::ResponsiblePerson::TOMILOV_IN, -1, Curriculum::DegreeLevel::BACHELOR, 1);
    } catch (const std::invalid_argument& e) {
        std::cout << "Перехваченное исключение:\n" << e.what() << std::endl;
    }

    try {
        Curriculum plan0;
        plan0.print();

        Curriculum plan("10.03.01", "Информационная безопасность", Curriculum::ResponsiblePerson::TOMILOV_IN, 240, Curriculum::DegreeLevel::BACHELOR, 2);
        plan.print();

        plan.setCode("2.22.02");
        plan.setTitle("Сварочное производство");
        plan.setResponsiblePerson(Curriculum::ResponsiblePerson::PAVLOV_AV);
        plan.addDiscipline(1, Discipline("Математический анализ", 30, Curriculum::DegreeLevel::BACHELOR));
        plan.addDiscipline(1, Discipline("Физика", 30, Curriculum::DegreeLevel::BACHELOR));
        plan.addDiscipline(1, Discipline("Дискретная математика", 30, Curriculum::DegreeLevel::BACHELOR));
        plan.addDiscipline(1, Discipline("Программирование", 30, Curriculum::DegreeLevel::BACHELOR));
        plan.addDiscipline(2, Discipline("Информационная безопасность", 30, Curriculum::DegreeLevel::BACHELOR));
        plan.addDiscipline(2, Discipline("Операционные системы", 30, Curriculum::DegreeLevel::BACHELOR));
        plan.addDiscipline(2, Discipline("Сети", 30, Curriculum::DegreeLevel::BACHELOR));
        plan.addDiscipline(2, Discipline("Алгоритмы", 30, Curriculum::DegreeLevel::BACHELOR));

        if (plan.activate()) {
            std::cout << "\nПлан активирован\n" << std::endl;
        } else {
            std::cout << "\nОшибка активации\n" << std::endl;
        }

        plan.print();

        Curriculum plan2("09.03.03", "Прикладная информатика", Curriculum::ResponsiblePerson::IVANOV_AV, 245, Curriculum::DegreeLevel::MASTER, 2);
        if (!plan2.activate()) {
            std::cout << "\nplan2 не активирован, потому что семестры пустые." << std::endl;
        }

        plan2.addDiscipline(1, Discipline("Алгоритмы", 49, Curriculum::DegreeLevel::MASTER));
        plan2.addDiscipline(1, Discipline("Теория баз данных", 49, Curriculum::DegreeLevel::MASTER));
        plan2.addDiscipline(2, Discipline("Машинное обучение", 49, Curriculum::DegreeLevel::MASTER));
        plan2.addDiscipline(2, Discipline("Большие данные", 49, Curriculum::DegreeLevel::MASTER));
        plan2.addDiscipline(2, Discipline("Компьютерная безопасность", 49, Curriculum::DegreeLevel::MASTER));

        try {
            plan2.addDiscipline(1, Discipline("Алгоритмы", 8, Curriculum::DegreeLevel::MASTER));
        } catch (const std::invalid_argument& e) {
            std::cout << "\nПерехваченное исключение при добавлении дисциплины: " << e.what() << std::endl;
        }

        if (plan2.activate()) {
            std::cout << "\nplan2 активирован\n" << std::endl;
        }

        Curriculum* plan3 = new Curriculum("09.03.03", "Прикладная информатика", Curriculum::ResponsiblePerson::IVANOV_AV, 245, Curriculum::DegreeLevel::MASTER, 2);
        plan3->addDiscipline(1, Discipline("Теория вероятностей", 8, Curriculum::DegreeLevel::MASTER));
        plan3->addDiscipline(2, Discipline("Программная инженерия", 10, Curriculum::DegreeLevel::MASTER));
        plan3->print();
        delete plan3;

        std::cout << "\nКонтейнер vector<Curriculum>\n" << std::endl;
        std::vector<Curriculum> curricula(3);
        for (auto& curriculum : curricula) {
            curriculum.print();
        }

        std::cout << "\nКонтейнер vector<unique_ptr<Curriculum>>\n" << std::endl;
        std::vector<std::unique_ptr<Curriculum>> curriculumPtrs;
        curriculumPtrs.reserve(3);
        for (int i = 0; i < 3; ++i) {
            curriculumPtrs.push_back(std::make_unique<Curriculum>());
            curriculumPtrs[i]->print();
        }


    } catch (const std::exception& e) {
        std::cerr << "Непредвиденная ошибка:\n" << e.what() << std::endl;
        return 1;
    }

    return 0;
}
