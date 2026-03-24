#include "study_group.h"
#include "my_list.h"

//  gcc -I1 -I4 2/main2.c 2/my_list.c 1/study_group.c -o main2
int main() {
    printf("\n--- Тестирование односвязного спика ---\n\n");
    
    Node* head = NULL;
    ErrorCode err;

    StudyGroup group1, group2, group3;
    
    // Инициализация групп
    err = init_study_group(&group1, "AB-123", IS, 2024, B);
    if (err != SUCCESS) {
        printf("Ошибка инициализации group1: код %d\n", err);
    } else {
        printf("group1 инициализирована\n");
    }
    
    err = init_study_group(&group2, "CD-456", PI, 2023, M);
    if (err != SUCCESS) {
        printf("Ошибка инициализации group2: код %d\n", err);
    } else {
        printf("group2 инициализирована\n");
    }
    
    err = init_study_group(&group3, "EF-789", PR, 2025, B);
    if (err != SUCCESS) {
        printf("Ошибка инициализации group3: код %d\n", err);
    } else {
        printf("group3 инициализирована\n");
    }
    
    printf("\n--- Добавление трёх элементов в стек ---\n");
    head = push(head, &group1);
    printf("group1 Добавлена в стек\n");
    
    head = push(head, &group2);
    printf("group2 Добавлена в стек\n");
    
    head = push(head, &group3);
    printf("group3 Добавлена в стек\n");
    
    printf("\n--- Текущее состояние стека ---\n");
    print_list(head);
    
    printf("--- Удаление одного элемента из стека ---\n");
    head = pop(head);
    
    printf("\n--- Состояние стека после удаления ---\n");
    print_list(head);
    
    printf("--- Полная очистка стека ---\n");
    delete_list(head);
    head = NULL;
    print_list(head);

    return 0;
}