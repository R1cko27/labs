#ifndef STUDY_GROUP_H
#define STUDY_GROUP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Перечислимый тип для уровня подготовки
typedef enum {
    B,  // Бакалавр
    M   // Магистр
} EducationLevel;

// Перечислимый тип для направления обучения
typedef enum {
    IS,  // Информационная безопасность
    PI,  // Прикладная информатика
    PS,  // Психология
    PR,  // Программная инженерия
    VT   // Вычислительная техника
} StudyDirection;

// Перечислимый тип для кодов ошибок
typedef enum {
    SUCCESS = 0,
    ERR_GROUP_NAME = 1,    // Ошибка в названии группы
    ERR_DIRECTION = 2,     // Ошибка в направлении обучения
    ERR_YEAR = 3,          // Ошибка в годе набора
    ERR_LEVEL = 4,         // Ошибка в уровне подготовки
    ERR_DUPLICATE = 5,     // Дубликат группы в массиве
    ERR_MEMORY = 6         // Ошибка выделения памяти
} ErrorCode;

// Структура "Учебная группа"
typedef struct {
    char group_name[10];       // Название группы
    StudyDirection direction;  // Направление обучения
    int enrollment_year;       // Год набора
    EducationLevel level;      // Уровень подготовки
} StudyGroup;

// 5) Функция проверки корректности
ErrorCode validate_study_group(const StudyGroup* group);

// 6) Функция инициализации с параметрами
ErrorCode init_study_group(StudyGroup* group, const char* group_name, 
                          StudyDirection direction, int enrollment_year, EducationLevel level);

// 8) Функция вывода информации
void print_study_group(const StudyGroup* group);

// Сравнение двух групп (меньше)
int is_study_group_less(const StudyGroup* group1, const StudyGroup* group2);

//  Проверка на равенство двух групп
int are_study_groups_equal(const StudyGroup* group1, const StudyGroup* group2);

#endif