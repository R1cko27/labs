#include "study_group.h"

// Тестирующая функция
// gcc -I1 -I4 1/main.c 2/my_list.c 1/study_group.c -o main1
int main() {
    
    StudyGroup group1, group2, group3;
    ErrorCode err;
    
    printf("--- Инициализация групп ---\n");
    // Инициализация group1
    err = init_study_group(&group1, "AB-420", IS, 2024, B);
    if (err != SUCCESS) {
        printf("Ошибка инициализации group1: код %d\n", err);
    } else {
        printf("group1 успешно инициализирована\n");
    }
    
    // Инициализация group2
    err = init_study_group(&group2, "AP-527", PI, 2025, M);
    if (err != SUCCESS) {
        printf("Ошибка инициализации group2: код %d\n", err);
    } else {
        printf("group2 успешно инициализирована\n\n");
    }
    
    err = init_study_group(&group3, "AB-420", IS, 2024, B);
    if (err != SUCCESS) {
        printf("Ошибка инициализации group3: код %d\n", err);
    } else {
        printf("group3 успешно инициализирована\n\n");
    }

    // Вывод информации
    printf("--- Вывод информации о группах ---\n");
    print_study_group(&group1);
    printf("\n");
    print_study_group(&group2);
    printf("\n");
    print_study_group(&group3);
    printf("\n");

    // Тестирование функций сравнения
    printf("--- Тестирование функций сравнения ---\n");
    printf("group1 и group2 равны? %s\n", are_study_groups_equal(&group1, &group2) ? "Да" : "Нет");
    printf("group1 и group3 равны? %s\n", are_study_groups_equal(&group1, &group3) ? "Да" : "Нет");
    printf("group1 > group2 %s\n", is_study_group_less(&group1, &group2) ? "Да" : "Нет");
    return 0;
}