#include "study_group.h"
#include "list_structures.h"

#define TASK1 1  // Структура (пункт 1)
#define TASK2 2  // Стек (пункт 2)
#define TASK3 3  // Множество - set (пункт 3.2)
#define TASK4 4  // Очередь (пункт 4)


#define CURRENT_TASK TASK4

#if CURRENT_TASK == TASK1
int main() {
    StudyGroup group1, group2, group3, group4;
    ErrorCode err;
    
    init_study_group(&group1, "AB-420", IS, 2024, B);
    init_study_group(&group2, "AP-527", PI, 2025, M);
    init_study_group(&group3, "AB-420", IS, 2024, B);
    err = init_study_group(&group3, "AP-421", IS, 2027, B); // Инициализация с ошибкой
    if (err != SUCCESS) printf("Ошибка инициализации group3: код %d (неверный год)\n", err);

    print_study_group(&group1);
    print_study_group(&group2);
    print_study_group(&group3);

    // Сравнение групп
    printf("group1 и group2 равны? %s\n", are_study_groups_equal(&group1, &group2) ? "Да" : "Нет");
    printf("group1 и group3 равны? %s\n", are_study_groups_equal(&group1, &group3) ? "Да" : "Нет");
    printf("group1 < group2? %s\n", is_study_group_less(&group1, &group2) ? "Да" : "Нет");
    return 0;
}

#elif CURRENT_TASK == TASK2
int main() {
    Node* head = NULL;
    ErrorCode err;

    StudyGroup group1, group2, group3;
    
    // Инициализация групп
    init_study_group(&group1, "AB-420", IS, 2024, B);
    init_study_group(&group2, "AP-526", PI, 2025, M);
    init_study_group(&group3, "VT-441", PR, 2024, B);
    
    // Добавляем элементы в стек
    head = push(head, &group1);
    head = push(head, &group2);
    head = push(head, &group3);
    
    print_list(head);
    
    // Удаляем элемент и выводим информацию
    head = pop(head);
    print_list(head);
    
    delete_list(head);
    head = NULL;
    print_list(head);
    return 0;
}

#elif CURRENT_TASK == TASK3

int main() {
    SetNode* set1 = NULL;
    SetNode* set2 = NULL;
    ErrorCode err;
    
    StudyGroup groups[8];
    
    // Инициализация групп
    init_study_group(&groups[0], "AP-526", PI, 2025, B);
    init_study_group(&groups[1], "AP-527", PI, 2025, B);
    init_study_group(&groups[2], "VT-515", VT, 2025, M);
    init_study_group(&groups[3], "PR-503", PR, 2025, M);
    init_study_group(&groups[4], "IS-420", IS, 2024, B);
    init_study_group(&groups[5], "PI-456", PI, 2023, M);
    init_study_group(&groups[6], "PR-389", PR, 2023, B);
    init_study_group(&groups[7], "VT-201", VT, 2022, B);
    
    // 1 мн-во
    set_insert(&set1, &groups[0]);
    set_insert(&set1, &groups[1]);
    set_insert(&set1, &groups[2]);
    set_insert(&set1, &groups[3]);
    set_insert(&set1, &groups[4]);

    // 2 мн-во
    set_insert(&set2, &groups[3]);
    set_insert(&set2, &groups[4]);
    set_insert(&set2, &groups[5]);
    set_insert(&set2, &groups[6]);
    set_insert(&set2, &groups[7]);
    
    printf("\n--- Первое множество ---\n");
    print_set(set1);
    
    printf("--- Второе множество ---\n");
    print_set(set2);
    
    printf("Группа IS-501 %s в первом множестве\n", set_contains(set1, "IS-501") ? "ЕСТЬ" : "ОТСУТСТВУЕТ");
    printf("Группа IS-501 %s во втором множестве\n", set_contains(set2, "IS-501") ? "ЕСТЬ" : "ОТСУТСТВУЕТ");
    printf("Группа AB-420 %s в первом множестве\n", set_contains(set1, "AB-420") ? "ЕСТЬ" : "ОТСУТСТВУЕТ");
    
    set_remove(&set1, "VT-515");
    print_set(set1);
    
    printf("\n--- Объединение множеств ---\n");
    SetNode* union_set = set_union(set1, set2);
    print_set(union_set);
    
    printf("--- Пересечение множеств ---\n");
    SetNode* intersection_set = set_intersection(set1, set2);
    print_set(intersection_set);
    
    delete_set(set1);
    delete_set(set2);
    delete_set(union_set);
    delete_set(intersection_set);
    
    return 0;
}

#elif CURRENT_TASK == TASK4

int main() {
    QueueNode* queue = NULL;
    ErrorCode err;
    StudyGroup groups[5];
    
    init_study_group(&groups[0], "AP-524", PI, 2024, B);
    init_study_group(&groups[1], "IS-501", IS, 2024, B);
    init_study_group(&groups[2], "VT-515", VT, 2025, M);
    init_study_group(&groups[3], "PR-503", PR, 2024, M);
    init_study_group(&groups[4], "AB-420", IS, 2024, B);
    
    for (int i = 0; i < 5; i++) {
        queue = enqueue(queue, &groups[i]);
        printf("Добавлен элемент %d: %s\n", i + 1, groups[i].group_name);
    }

    print_queue(queue);
    
    StudyGroup extracted;
    for (int i = 0; i < 3; i++) {
        printf("\nИзвлечение #%d:\n", i + 1);
        queue = dequeue(queue, &extracted);
        
        if (queue != NULL) {
            printf("Текущее состояние очереди:\n");
            print_queue(queue);
        } else {
            printf("Очередь стала пустой\n");
        }
    }
    print_queue(queue);
    
    queue = delete_queue(queue);
    print_queue(queue);

    return 0;
}

#else
#error "Неверный номер задачи"
#endif