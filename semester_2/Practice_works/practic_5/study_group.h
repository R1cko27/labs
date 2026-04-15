#ifndef STUDY_GROUP_H
#define STUDY_GROUP_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>

// Перечисления для уровня образования и направления
enum EducationLevel { BACHELOR, MASTER };
enum StudyDirection { IS, PI, AI, PR, VT };

// Класс для учебной группы
class StudentGroup {
private:
    std::string groupName;        // Название группы
    StudyDirection direction;     // Направление обучения
    int enrollmentYear;           // Год набора
    EducationLevel level;         // Уровень подготовки (бакалавр/магистр)

public:
    // Конструктор
    StudentGroup(const std::string& name, 
                StudyDirection dir, 
                int year, 
                EducationLevel lvl);
    StudentGroup();
    // Метод для печати информации о группе
    void print() const;

    // Метод для проверки корректности данных
    static bool validate_group(const StudentGroup& group);

    // Метод для изменения названия группы
    void rename(const std::string& newGroupName);
};

#endif