#ifndef STUDY_GROUP_H
#define STUDY_GROUP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Перечислимые типы
typedef enum { B, M } EducationLevel;
typedef enum { IS, PI, AI, PR, VT } StudyDirection;

// Коды ошибок
typedef enum {
    SUCCESS = 0,
    ERR_GROUP_NAME = 1,
    ERR_DIRECTION = 2,
    ERR_YEAR = 3,
    ERR_LEVEL = 4,
    ERR_DUPLICATE = 5,
    ERR_MEMORY = 6
} ErrorCode;

// Структура "Учебная группа"
typedef struct {
    char group_name[10];
    StudyDirection direction;
    int enrollment_year;
    EducationLevel level;
} StudyGroup;


// Основные функции
ErrorCode validate_study_group(const StudyGroup* group);
ErrorCode init_study_group(StudyGroup* group, const char* group_name, StudyDirection direction, int enrollment_year, EducationLevel level);
void direction_to_string(StudyDirection dir);
void print_study_group(const StudyGroup* group);
int are_study_groups_equal(const StudyGroup* group1, const StudyGroup* group2);
int is_study_group_less(const StudyGroup* group1, const StudyGroup* group2);

#endif