#include "study_group.h"

#include <ctime>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>

int currentYear() {
    const std::time_t now = std::time(nullptr);
    const std::tm local = *std::localtime(&now);
    return local.tm_year + 1900;
}

const char* toString(StudyDirection dir) {
    switch (dir) {
        case StudyDirection::IS: return "Информационная безопасность";
        case StudyDirection::PI: return "Прикладная информатика";
        case StudyDirection::AI: return "Приборостроение";
        case StudyDirection::PR: return "Программная инженерия";
        case StudyDirection::VT: return "Вычислительная техника";
        default: return "Неизвестное направление";
    }
}

const char* toString(EducationLevel lvl) {
    switch (lvl) {
        case EducationLevel::Bachelor: return "Бакалавр";
        case EducationLevel::Master: return "Магистр";
        default: return "Неизвестный уровень";
    }
}

bool isDirectionValueValid(int raw) {
    return raw >= static_cast<int>(StudyDirection::IS) && raw <= static_cast<int>(StudyDirection::VT);
}

bool isLevelValueValid(int raw) {
    return raw == static_cast<int>(EducationLevel::Bachelor) ||
           raw == static_cast<int>(EducationLevel::Master);
}

void StudentGroup::init(const std::string& name, StudyDirection dir, int year, EducationLevel lvl) {
    if (name.size() < 5 || name.find('-') == std::string::npos) 
        throw std::invalid_argument("Некорректное название группы: минимум 5 символов и дефис обязательны");
    
    const int dirValue = static_cast<int>(dir);
    if (!isDirectionValueValid(dirValue)) throw std::out_of_range("Некорректное направление обучения");

    const int thisYear = currentYear();
    if (year < thisYear - 8 || year > thisYear) throw std::out_of_range("Некорректный год набора");
    
    const int levelValue = static_cast<int>(lvl);
    if (!isLevelValueValid(levelValue)) throw std::out_of_range("Некорректный уровень образования");

    groupName = name;
    direction = dir;
    enrollmentYear = year;
    level = lvl;
}

StudentGroup::StudentGroup(const std::string& name, StudyDirection dir, int year, EducationLevel lvl) {
    init(name, dir, year, lvl);
}

StudentGroup::StudentGroup(const StudentGroup& other)
    : groupName(other.groupName),
      direction(other.direction),
      enrollmentYear(other.enrollmentYear),
      level(other.level) {}

void StudentGroup::print() const {
    std::cout << "Название группы: " << groupName << '\n'
              << "Направление: " << toString(direction) << '\n'
              << "Год набора: " << enrollmentYear << '\n'
              << "Уровень подготовки: " << toString(level) << '\n';
}

void StudentGroup::rename(const std::string& newGroupName) {
    init(newGroupName, direction, enrollmentYear, level);
}

StudentGroup* createGroup(const std::string& name,
                          StudyDirection dir,
                          int year,
                          EducationLevel lvl,
                          std::ostream& out) {
    try {
        return new StudentGroup(name, dir, year, lvl);
    } catch (const std::bad_alloc&) {
        out << "Не удалось выделить память для объекта\n";
        return nullptr;
    }
}

