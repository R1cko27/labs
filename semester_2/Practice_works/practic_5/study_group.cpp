#include "study_group.h"

// Конструктор с параметрами по умолчанию
StudentGroup::StudentGroup(const std::string& name, StudyDirection dir, int year, EducationLevel lvl)
    : groupName(name), direction(dir), enrollmentYear(year), level(lvl) {}

// Метод для печати информации о группе
void StudentGroup::print() const {
    std::cout << "Название группы: " << groupName << std::endl;
    
    // Печать направления
    std::string direction_str;
    switch (direction) {
        case IS: direction_str = "Информационная безопасность"; break;
        case PI: direction_str = "Прикладная информатика"; break;
        case AI: direction_str = "Приборостроение"; break;
        case PR: direction_str = "Программная инженерия"; break;
        case VT: direction_str = "Вычислительная техника"; break;
        default: direction_str = "Неизвестное направление"; break;
    }

    std::cout << "Направление: " << direction_str << std::endl;
    std::cout << "Год набора: " << enrollmentYear << std::endl;

    // Печать уровня
    std::string level_str = (level == BACHELOR) ? "Бакалавр" : "Магистр";
    std::cout << "Уровень подготовки: " << level_str << std::endl;
}

// Метод для валидации данных группы
bool StudentGroup::validate_group(const StudentGroup& group) {
    // Проверка имени группы (минимум 5 символов, с дефисом и цифрами в конце)
    if (group.groupName.size() < 5) return false;
    if (group.groupName.find('-') == std::string::npos) return false;

    // Проверка направления
    if (group.direction < IS || group.direction > VT) return false;

    // Проверка года набора
    time_t t = time(nullptr);
    struct tm tm = *localtime(&t);
    int current_year = tm.tm_year + 1900;
    if (group.enrollmentYear < current_year - 8 || group.enrollmentYear > current_year) return false;

    // Проверка уровня подготовки
    if (group.level != BACHELOR && group.level != MASTER) return false;

    return true;
}

// Метод для переименования группы
void StudentGroup::rename(const std::string& newGroupName) {
    groupName = newGroupName;
}