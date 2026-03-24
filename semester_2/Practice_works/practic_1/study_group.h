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
ErrorCode copy_study_group(StudyGroup* dest, const StudyGroup* src);
void print_study_group(const StudyGroup* group);
ErrorCode set_group_name(StudyGroup* group, const char* new_name);
StudyGroup* create_study_group(const char* group_name, StudyDirection direction, int enrollment_year, EducationLevel level);
void delete_study_group(StudyGroup* group);
void direction_to_string(StudyDirection dir);
ErrorCode add_group_to_array(StudyGroup** array, int* size, int* capacity, const StudyGroup* group);
void free_study_group_array(StudyGroup** array, int* size, int* capacity);

#endif