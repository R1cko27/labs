#include "study_group.h"
#include <stddef.h>
#include <time.h>

// Проверка названия группы
int is_valid_group_name_pattern(const char* name) {
    if (!name) return 0;
    int len = strlen(name);
    if (len < 5) return 0;
    
    const char* hyphen = strchr(name, '-');
    if (!hyphen) return 0;
    
    int prefix_len = hyphen - name;
    if (prefix_len < 1 || prefix_len > 4) return 0;
    
    for (int i = 0; i < prefix_len; i++) {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || 
              (name[i] >= 'a' && name[i] <= 'z') ||
              (name[i] >= -64 && name[i] <= -17) || 
              (name[i] >= -32 && name[i] <= -1))) {
            return 0;
        }
    }
    
    const char* suffix = hyphen + 1;
    int suffix_len = strlen(suffix);
    if (suffix_len != 3) return 0;
    
    for (int i = 0; i < suffix_len; i++) {
        if (suffix[i] < '0' || suffix[i] > '9') return 0;
    }
    return 1;
}

// Проверка корректности значений
ErrorCode validate_study_group(const StudyGroup* group) {
    if (!group) return ERR_GROUP_NAME;
    if (!is_valid_group_name_pattern(group->group_name)) return ERR_GROUP_NAME;
    if (group->direction < IS || group->direction > VT) return ERR_DIRECTION;
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int current_year = tm.tm_year + 1900;
    
    if (group->enrollment_year < current_year - 8 || 
        group->enrollment_year > current_year) return ERR_YEAR;
    if (group->level != B && group->level != M) return ERR_LEVEL;
    
    return SUCCESS;
}

// Инициализация структуры
ErrorCode init_study_group(StudyGroup* group, const char* group_name, 
                          StudyDirection direction, int enrollment_year, EducationLevel level) {
    if (!group) return ERR_GROUP_NAME;
    
    StudyGroup temp;
    strncpy(temp.group_name, group_name, 10);
    temp.group_name[10] = '\0';
    temp.direction = direction;
    temp.enrollment_year = enrollment_year;
    temp.level = level;
    
    ErrorCode err = validate_study_group(&temp);
    if (err != SUCCESS) return err;
    
    *group = temp;
    return SUCCESS;
}

// Копирование группы
ErrorCode copy_study_group(StudyGroup* dest, const StudyGroup* src) {
    if (!dest || !src) return ERR_GROUP_NAME;
    ErrorCode err = validate_study_group(src);
    if (err != SUCCESS) return err;
    
    *dest = *src;
    return SUCCESS;
}

// Вывод направления
void direction_to_string(StudyDirection dir) {
    switch (dir) {
        case IS: printf("Информационная безопасность"); break;
        case PI: printf("Прикладная информатика"); break;
        case AI: printf("Приборостроение"); break;
        case PR: printf("Программная инженерия"); break;
        case VT: printf("Вычислительная техника"); break;
        default: printf("Неизвестное направление");
    }
}

// Вывод информации о группе
void print_study_group(const StudyGroup* group) {
    if (!group) {
        printf("Группа: NULL\n");
        return;
    }
    
    const char* level_str = (group->level == B) ? "Бакалавр" : "Магистр";
    printf("Название группы: %s\n", group->group_name);
    printf("Направление: "); direction_to_string(group->direction); printf("\n");
    printf("Год набора: %d\n", group->enrollment_year);
    printf("Уровень подготовки: %s\n", level_str);
}

// Изменение названия группы
ErrorCode set_group_name(StudyGroup* group, const char* new_name) {
    if (!group || !new_name) return ERR_GROUP_NAME;
    
    StudyGroup temp = *group;
    strncpy(temp.group_name, new_name, 10);
    temp.group_name[10] = '\0';
    
    ErrorCode err = validate_study_group(&temp);
    if (err != SUCCESS) return err;
    
    *group = temp;
    return SUCCESS;
}

// Создание группы в динамической памяти
StudyGroup* create_study_group(const char* group_name, StudyDirection direction, 
                              int enrollment_year, EducationLevel level) {
    StudyGroup* group = malloc(sizeof(StudyGroup));
    if (!group) return NULL;
    
    ErrorCode err = init_study_group(group, group_name, direction, enrollment_year, level);
    if (err != SUCCESS) {
        free(group);
        return NULL;
    }
    
    printf("Создана группа в динамической памяти:\n");
    print_study_group(group);
    printf("\n");
    return group;
}

// Удаление группы из динамической памяти
void delete_study_group(StudyGroup* group) {
    if (group) {
        printf("Удаление группы %s из динамической памяти\n", group->group_name);
        free(group);
    }
}

// Добавление группы в динамический массив
ErrorCode add_group_to_array(StudyGroup** array, int* size, int* capacity, 
                            const StudyGroup* group) {
    if (!array || !size || !capacity || !group) return ERR_GROUP_NAME;
    
    for (int i = 0; i < *size; i++) {
        if (strcmp((*array)[i].group_name, group->group_name) == 0) {
            printf("Ошибка: группа %s уже существует\n", group->group_name);
            return ERR_DUPLICATE;
        }
    }
    
    ErrorCode err = validate_study_group(group);
    if (err != SUCCESS) return err;
    
    if (*size >= *capacity) {
        *capacity = (*capacity == 0) ? 2 : (*capacity) * 2;
        StudyGroup* temp = realloc(*array, (*capacity) * sizeof(StudyGroup));
        if (!temp) return ERR_MEMORY;
        *array = temp;
    }
    
    (*array)[*size] = *group;
    (*size)++;
    printf("Группа %s добавлена в массив\n", group->group_name);
    return SUCCESS;
}

// Освобождение динамического массива
void free_study_group_array(StudyGroup** array, int* size, int* capacity) {
    if (array && *array) {
        printf("Освобождение памяти массива групп\n");
        free(*array);
        *array = NULL;
        *size = 0;
        *capacity = 0;
    }
}