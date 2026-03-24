#include "study_group.h"
#include "set_list.h"
#include <stdio.h>

// Тестирующая функция для работы с множествами
// gcc -I1 -I4 3.2/main3.c 3.2/set_list.c 1/study_group.c -o main3

int main() {
    printf("\n--- Тестирование множества set()\n\n");
    
    SetNode* set1 = NULL;
    SetNode* set2 = NULL;
    ErrorCode err;
    
    StudyGroup groups[8];
    
    // Инициализация групп
    init_study_group(&groups[0], "AP-524", PI, 2024, B);
    init_study_group(&groups[1], "IS-501", IS, 2024, B);
    init_study_group(&groups[2], "VT-515", VT, 2025, M);
    init_study_group(&groups[3], "PR-503", PR, 2024, M);
    init_study_group(&groups[4], "AB-420", IS, 2024, B);
    init_study_group(&groups[5], "CD-456", PI, 2023, M);
    init_study_group(&groups[6], "EF-789", PR, 2025, B);
    init_study_group(&groups[7], "GH-101", VT, 2024, B);
    
    printf("--- Создание первого множества (5 элементов) ---\n");
    err = set_insert(&set1, &groups[0]);
    printf("Добавление %s: %s\n", groups[0].group_name, err == SUCCESS ? "OK" : "Ошибка");
    
    err = set_insert(&set1, &groups[1]);
    printf("Добавление %s: %s\n", groups[1].group_name, err == SUCCESS ? "OK" : "Ошибка");
    
    err = set_insert(&set1, &groups[2]);
    printf("Добавление %s: %s\n", groups[2].group_name, err == SUCCESS ? "OK" : "Ошибка");
    
    err = set_insert(&set1, &groups[3]);
    printf("Добавление %s: %s\n", groups[3].group_name, err == SUCCESS ? "OK" : "Ошибка");
    
    err = set_insert(&set1, &groups[4]);
    printf("Добавление %s: %s\n", groups[4].group_name, err == SUCCESS ? "OK" : "Ошибка");
    
    printf("\n--- Создание второго множества (5 элементов) ---\n");
    err = set_insert(&set2, &groups[3]);  // Дубликат с groups[3]
    printf("Добавление %s: %s\n", groups[3].group_name, err == SUCCESS ? "OK" : "Ошибка");
    
    err = set_insert(&set2, &groups[4]);  // Дубликат с groups[4]
    printf("Добавление %s: %s\n", groups[4].group_name, err == SUCCESS ? "OK" : "Ошибка");
    
    err = set_insert(&set2, &groups[5]);
    printf("Добавление %s: %s\n", groups[5].group_name, err == SUCCESS ? "OK" : "Ошибка");
    
    err = set_insert(&set2, &groups[6]);
    printf("Добавление %s: %s\n", groups[6].group_name, err == SUCCESS ? "OK" : "Ошибка");
    
    err = set_insert(&set2, &groups[7]);
    printf("Добавление %s: %s\n", groups[7].group_name, err == SUCCESS ? "OK" : "Ошибка");
    
    printf("\n--- Первое множество ---\n");
    print_set(set1);
    
    printf("--- Второе множество ---\n");
    print_set(set2);
    
    printf("--- Проверка наличия элементов ---\n");
    printf("Группа IS-501 %s в первом множестве\n", 
           set_contains(set1, "IS-501") ? "ЕСТЬ" : "ОТСУТСТВУЕТ");
    printf("Группа IS-501 %s во втором множестве\n", 
           set_contains(set2, "IS-501") ? "ЕСТЬ" : "ОТСУТСТВУЕТ");
    printf("Группа AB-420 %s в первом множестве\n", 
           set_contains(set1, "AB-420") ? "ЕСТЬ" : "ОТСУТСТВУЕТ");
    
    printf("\n--- Удаление элемента из первого множества ---\n");
    set_remove(&set1, "VT-515");
    printf("Первое множество после удаления:\n");
    print_set(set1);
    
    printf("\n--- Объединение множеств ---\n");
    SetNode* union_set = set_union(set1, set2);
    printf("Результат объединения:\n");
    print_set(union_set);
    
    printf("--- Пересечение множество ---\n");
    SetNode* intersection_set = set_intersection(set1, set2);
    printf("Результат пересечения:\n");
    print_set(intersection_set);
    
    printf("--- Очистка памяти ---\n");
    delete_set(set1);
    delete_set(set2);
    delete_set(union_set);
    delete_set(intersection_set);
    
    return 0;
}