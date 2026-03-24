#include "study_group.h"
#include "my_queue.h"
#include <stdio.h>

// gcc -I1 -I4 4/main4.c 4/my_queue.c 1/study_group.c -o main4
// Тестирующая функция для очереди
int main() {
    printf("\n--- Тестирование очереди на базе двухсвязного списка ---\n\n");
    
    QueueNode* queue = NULL;
    ErrorCode err;
    
    StudyGroup groups[5];
    
    // Инициализация групп
    init_study_group(&groups[0], "AP-524", PI, 2024, B);
    init_study_group(&groups[1], "IS-501", IS, 2024, B);
    init_study_group(&groups[2], "VT-515", VT, 2025, M);
    init_study_group(&groups[3], "PR-503", PR, 2024, M);
    init_study_group(&groups[4], "AB-420", IS, 2024, B);
    
    printf("--- Добавление 5 элементов в очередь (enqueue) ---\n");
    
    for (int i = 0; i < 5; i++) {
        queue = enqueue(queue, &groups[i]);
        printf("Добавлен элемент %d: %s\n", i + 1, groups[i].group_name);
    }
    
    // Печатаем всю очередь
    print_queue(queue);
    
    printf("\n--- Извлечение 3 элементов из очереди (dequeue) ---\n");
    
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
    
    printf("\n--- Оставшиеся элементы в очереди ---\n");
    print_queue(queue);
    
    printf("\n--- Очистка очереди ---\n");
    queue = delete_queue(queue);
    print_queue(queue);
    
    return 0;
}
