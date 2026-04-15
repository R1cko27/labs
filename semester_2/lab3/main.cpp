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
        Curriculum invalidPlan("недействительная_группа", "План", "Панфилов А.П.", 250, Curriculum::DegreeLevel::BACHELOR);
    } catch (const std::invalid_argument& e) {
        std::cout << "Перехваченное исключение:\n" << e.what() << std::endl;
    }
    try {
        Curriculum plan("10.03.01", "Информационная Безопасность", "Панфилов А.П.", 240, Curriculum::DegreeLevel::BACHELOR);
        printCurriculumInfo(plan);

        // Установка дисциплин
        plan.setDisciplinesInfo(50, 240);
        printCurriculumInfo(plan);

        // Попытка ввода в действие
        if (plan.activate()) {
            std::cout << "План активирован" << std::endl;
        } else {
            std::cout << "Ошибка активации" << std::endl;
        }
        printCurriculumInfo(plan);

        // Попытка изменить активный план
        try {
            plan.setTitle("Сварочное производство");
        } catch (const std::logic_error& e) {
            std::cout << "ОШИБКА: " << e.what() << std::endl;
        }

        Curriculum plan2("09.03.03", "Прикладная информатика", "Имнакулов С.А.", 120, Curriculum::DegreeLevel::MASTER);
        
        // Пытаемся ввести в действие с нулями
        // Но при этом target 120, а сумма ЗЕ 0 -> activate вернет false
        if (!plan2.activate()) {
            std::cout << "Активация отклонена (сумма кредитов != цель)." << std::endl;
        }

        // 6. Проверка правила "могут быть равны 0 только одновременно"
        try {
            plan2.setDisciplinesInfo(0, 10);
        } catch (const std::invalid_argument& e) {
            std::cout << "Перехваченное исключение: " << e.what() << std::endl;
        }
        
        plan2.setDisciplinesInfo(0, 0);
        std::cout << "Успешно установлено 0 дисциплин и 0 зачётных единиц." << std::endl;
        
        // Установим правильные дисциплины и активируем
        plan2.setDisciplinesInfo(30, 120);
        plan2.activate();
        std::cout << "Состояние второго экземпляра: " << plan2.getStateString() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Непредвиденная ошибка:\n" << e.what() << std::endl;
        return 1;
    }

    return 0;
}