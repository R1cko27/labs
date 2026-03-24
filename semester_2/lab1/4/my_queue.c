#include "my_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Вспомогательная функция для создания нового узла
static QueueNode* create_node(const StudyGroup* group) {
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти для узла очереди\n");
        return NULL;
    }
    new_node->data = *group;
    new_node->next = NULL;
    new_node->prev = NULL;
    
    return new_node;
}

// 1) Функция добавления элемента в конец очереди
QueueNode* enqueue(QueueNode* tail, const StudyGroup* group) {
    ErrorCode err = validate_study_group(group);
    if (err != SUCCESS) {
        printf("Ошибка: группа некорректна (код ошибки %d)\n", err);
        return tail;
    }
    
    QueueNode* new_node = create_node(group);
    if (new_node == NULL) {
        return tail;
    }
    
    // Если очередь пуста
    if (tail == NULL) {
        new_node->next = new_node;
        new_node->prev = new_node;
        return new_node;
    }
    
    // Вставка в конец очереди
    QueueNode* head = tail->next;
    
    new_node->next = head;
    new_node->prev = tail;
    
    // Обновляем связи соседей
    head->prev = new_node;
    tail->next = new_node;
    
    return new_node;
}

// 2) Функция удаления элемента из начала очереди
QueueNode* dequeue(QueueNode* tail, StudyGroup* result) {
    if (tail == NULL) {
        printf("Очередь пуста, удаление невозможно\n");
        return NULL;
    }
    
    // Голова очереди - следующий за хвостом элемент
    QueueNode* head = tail->next;
    
    if (result != NULL) {
        *result = head->data;
    }

    printf("Извлечён элемент: ");
    print_study_group(&head->data);
    
    // Если в очереди только один элемент
    if (head == tail) {
        free(head);
        return NULL;
    }
    
    // Перестраиваем связи
    tail->next = head->next;
    head->next->prev = tail;
    
    free(head);
    return tail;
}

// 3) Функция удаления всей очереди
QueueNode* delete_queue(QueueNode* tail) {
    if (tail == NULL) {
        printf("Очередь уже пуста\n");
        return NULL;
    }
    
    QueueNode* current = tail->next;
    QueueNode* head = current;
    int count = 0;
    
    // Проходим по всем элементам
    while (current != tail) {
        QueueNode* temp = current;
        current = current->next;
        free(temp);
        count++;
    }
    
    // Удаляем последний элемент
    free(tail);
    count++;
    
    printf("Удалено %d элементов очереди\n", count);
    return NULL;
}

// 4) Функция печати всех элементов очереди
void print_queue(const QueueNode* tail) {
    if (tail == NULL) {
        printf("Очередь пуста\n");
        return;
    }
    
    const QueueNode* current = tail->next;
    const QueueNode* head = current;
    int position = 1;
    
    printf("\n--- Содержимое очереди (от начала к концу) ---\n");
    do {
        printf("Элемент %d (в начале %s):\n", 
               position, 
               (current == head) ? "ДА" : "нет");
        print_study_group(&current->data);
        printf("\n");
        
        current = current->next;
        position++;
    } while (current != head);
    
    printf("--- Конец очереди ---\n");
}

// 5) Вспомогательная функция проверки на пустоту
int is_queue_empty(const QueueNode* tail) {
    return tail == NULL;
}