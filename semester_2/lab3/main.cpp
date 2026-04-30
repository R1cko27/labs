#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Curriculum.h"

void printCurriculumInfo(const Curriculum& c) {
    std::cout << "Шифр: " << c.getCode() << std::endl;
    std::cout << "Название: " << c.getTitle() << std::endl;
    std::cout << "Ответственный: " << c.getResponsiblePerson() << std::endl;
    std::cout << "Целевое количество ЗЕ: " << c.getTargetCredits() << std::endl;
    std::cout << "Ступень образования: " << c.getDegreeLevelString() << std::endl;
    std::cout << "Количество дисциплин: " << c.getDisciplineCount() << std::endl;
    std::cout << "Суммарное количество ЗЕ: " << c.getTotalDisciplineCredits() << std::endl;
    std::cout << "Состояние: " << c.getStateString() << std::endl;
}

int main() {
    try {
        Curriculum invalidPlan("недействительная_группа", "", "Панфилов А.П..", -1, Curriculum::DegreeLevel::BACHELOR);
    } catch (const std::invalid_argument& e) {
        std::cout << "Перехваченное исключение:\n" << e.what() << std::endl;
    }
    try {
        Curriculum plan0;
        printCurriculumInfo(plan0);

        Curriculum plan("10.03.01", "Информационная безопасность", "Панфилов А.П.", 240, Curriculum::DegreeLevel::BACHELOR);
        printCurriculumInfo(plan);

        plan.setCode("2.22.02");
        plan.setTitle("Сварочное производство");
        plan.setResponsiblePerson("Петров Н.И.");
        plan.setDisciplinesInfo(50, 240);

        if (plan.activate()) {
            std::cout << "\nПлан активирован\n" << std::endl;
        } else {
            std::cout << "\nОшибка активации\n" << std::endl;
        }

        printCurriculumInfo(plan);

        Curriculum plan2("09.03.03", "Прикладная информатика", "Имнакулов С.А.", 245, Curriculum::DegreeLevel::MASTER);
        plan2.activate();

        // Проверка правила "могут быть равны 0 только одновременно"
        try {
            plan2.setDisciplinesInfo(0, 245);
        } catch (const std::invalid_argument& e) {
            std::cout << "\nПерехваченное исключение при установки дисциплин: " << e.what() << std::endl;
        }   

        plan2.setDisciplinesInfo(30, 245);
        plan2.activate();

        printCurriculumInfo(plan2);

    } catch (const std::exception& e) {
        std::cerr << "Непредвиденная ошибка:\n" << e.what() << std::endl;
        return 1;
    }

    return 0;
}