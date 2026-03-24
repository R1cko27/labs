#include "study_group.h"
#include <stddef.h>
#include <ctype.h>
#include <time.h>

// Проверка названия группы
int is_valid_group_name_pattern(const char* name) {
    if (name == NULL) return 0;
    
    int len = strlen(name);
    if (len < 5) return 0;
    
    // Поиск дефиса
    const char* hyphen = strchr(name, '-');
    if (hyphen == NULL) return 0;
    
    // Проверка части до дефиса (1-4 буквы)
    int prefix_len = hyphen - name;
    if (prefix_len < 1 || prefix_len > 4) return 0;
    
    // Проверяем, что все символы до дефиса - буквы
    for (int i = 0; i < prefix_len; i++) {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || 
              (name[i] >= 'a' && name[i] <= 'z') ||
              (name[i] >= -64 && name[i] <= -17) || 
              (name[i] >= -32 && name[i] <= -1))) {
            return 0;
        }
    }
    
    // Проверка части после дефиса (3 цифры)
    const char* suffix = hyphen + 1;
    int suffix_len = strlen(suffix);
    if (suffix_len != 3) return 0;
    
    for (int i = 0; i < suffix_len; i++) {
        if (suffix[i] < '0' || suffix[i] > '9') return 0;
    }
    
    return 1;
}

// Проверка корректности значений полей структуры
ErrorCode validate_study_group(const StudyGroup* group) {
    if (group == NULL) {
        return ERR_GROUP_NAME;
    }
    
    // Проверка паттерна названия группы
    if (!is_valid_group_name_pattern(group->group_name)) {
        return ERR_GROUP_NAME;
    }
    
    // Проверка направления обучения
    if (group->direction < IS || group->direction > VT) {
        return ERR_DIRECTION;
    }
    
    // Проверка года набора
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int current_year = tm.tm_year + 1900;
    
    if (group->enrollment_year < current_year - 8 || 
        group->enrollment_year > current_year) {
        return ERR_YEAR;
    }
    
    // Проверка уровня подготовки
    if (group->level != B && group->level != M) {
        return ERR_LEVEL;
    }
    
    return SUCCESS;
}

// Инициализация структуры с проверкой
ErrorCode init_study_group(StudyGroup* group, const char* group_name, 
                          StudyDirection direction, int enrollment_year, EducationLevel level) {
    if (group == NULL) {
        return ERR_GROUP_NAME;
    }
    
    StudyGroup temp;
    strncpy(temp.group_name, group_name, 10);
    temp.group_name[10] = '\0';
    temp.direction = direction;
    temp.enrollment_year = enrollment_year;
    temp.level = level;
    
    // Проверяем корректность
    ErrorCode err = validate_study_group(&temp);
    if (err != SUCCESS) {
        StudyGroup group1;
        err = init_study_group(&group1, "AP-526", IS, 2025, B);
        if (err != SUCCESS) {
            printf("Ошибка инициализации значений по умолчанию group1: код %d\n", err);
        } else {
            printf("Выставлены значения по умолчанию\n");
        }
    }
    
    strcpy(group->group_name, temp.group_name);
    group->direction = temp.direction;
    group->enrollment_year = temp.enrollment_year;
    group->level = temp.level;
    
    return SUCCESS;
}

// Функция для преобразования enum направления в строку
const char* direction_to_string(StudyDirection dir) {
    switch (dir) {
        case IS: return "Информационная безопасность";
        case PI: return "Прикладная информатика";
        case PS: return "Психология";
        case PR: return "Программная инженерия";
        case VT: return "Вычислительная техника";
        default: return "Неизвестное направление";
    }
}

// Функция вывода информации
void print_study_group(const StudyGroup* group) {
    if (group == NULL) {
        printf("Группа: NULL\n");
        return;
    }
    
    const char* level_str = (group->level == B) ? "Бакалавр" : "Магистр";
    const char* dir_str = direction_to_string(group->direction);
    
    printf("Название группы: %s\n", group->group_name);
    printf("Направление: %s\n", dir_str);
    printf("Год набора: %d\n", group->enrollment_year);
    printf("Уровень подготовки: %s\n", level_str);
}

//  Проверка на равенство двух групп
int are_study_groups_equal(const StudyGroup* group1, const StudyGroup* group2) {
    if (group1 == NULL || group2 == NULL) {
        return 0;
    }
    
    // Сравниваем все поля
    if (strcmp(group1->group_name, group2->group_name) != 0) return 0;
    
    if (group1->direction != group2->direction) return 0;
    
    if (group1->enrollment_year != group2->enrollment_year) return 0;
    
    if (group1->level != group2->level) return 0;
    
    return 1; // Все поля совпадают
}

// Сравнение двух групп
int is_study_group_less(const StudyGroup* group1, const StudyGroup* group2) {
    if (group1 == NULL || group2 == NULL) {
        return 0;
    }
    
    // Приоритет 1: Уровень подготовки (B < M)
    if (group1->level != group2->level) {
        return group1->level < group2->level;
    }
    
    // Приоритет 2: Направление обучения
    if (group1->direction != group2->direction) {
        return group1->direction < group2->direction;
    }
    
    // Приоритет 3: Год набора (меньший год - старше группа)
    if (group1->enrollment_year != group2->enrollment_year) {
        return group1->enrollment_year < group2->enrollment_year;
    }
    
    // Приоритет 4: Название группы
    return strcmp(group1->group_name, group2->group_name) < 0;
}