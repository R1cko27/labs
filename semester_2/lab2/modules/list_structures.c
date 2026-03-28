#include "list_structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ==================== СТЕК (пункт 2) ====================

// Добавление элемента в стек
Node* push(Node* head, const StudyGroup* group) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти\n");
        return head;
    }
    
    new_node->data = *group;
    new_node->next = head;
    
    printf("Добавлен гурппа:\n");
    print_study_group(group);
    
    return new_node;
}

// Удаление элемента из стека
Node* pop(Node* head) {
    if (head == NULL) {
        printf("Список пуст, удаление невозможно\n");
        return NULL;
    }
    
    Node* temp = head;
    head = head->next;
    
    printf("Удалена группа:\n");
    print_study_group(&temp->data);
    
    free(temp);
    return head;
}

// Печать всех элементов стека
void print_list(const Node* head) {
    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }
    
    const Node* current = head;
    int count = 1;
    
    while (current != NULL) {
        printf("Элемент %d:\n", count++);
        print_study_group(&current->data);
        printf("\n");
        current = current->next;
    }
}

// Удаление стека
void delete_list(Node* head) {
    Node* current = head;
    int count = 0;
    
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
        count++;
    }
    
    printf("Удалено %d элементов списка\n", count);
}

// ==================== МНОЖЕСТВО (пункт 3.2) ====================

// Создание нового узла
static SetNode* create_set_node(const StudyGroup* group) {
    SetNode* new_node = (SetNode*)malloc(sizeof(SetNode));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти для узла\n");
        return NULL;
    }
    
    new_node->data = (StudyGroup*)malloc(sizeof(StudyGroup));
    if (new_node->data == NULL) {
        printf("Ошибка выделения памяти для данных\n");
        free(new_node);
        return NULL;
    }

    *(new_node->data) = *group;
    new_node->next = NULL;
    
    return new_node;
}

// Функция для проверки эквивалентности групп
static int groups_are_equal(const StudyGroup* g1, const StudyGroup* g2) {
    return strcmp(g1->group_name, g2->group_name) == 0;
}

// Функция для вставки с сохранением порядка
static ErrorCode insert_ordered(SetNode** head, const StudyGroup* group) {
    SetNode* new_node = create_set_node(group);
    if (new_node == NULL) return ERR_MEMORY;

    // Если список пуст или новый элемент должен быть в начале
    if (*head == NULL || is_study_group_less(group, (*head)->data)) {
        new_node->next = *head;
        *head = new_node;
        return SUCCESS;
    }

    // Поиск места для вставки
    SetNode* current = *head;
    while (current->next != NULL && is_study_group_less(current->next->data, group)) current = current->next;

    // Проверка на дубликат элмента перед узлом
    if (groups_are_equal(current->data, group)) {
        printf("Ошибка: группа %s уже существует в множестве\n", group->group_name);
        free(new_node->data);
        free(new_node);
        return ERR_DUPLICATE;
    }
    
    // Вставка элемента
    new_node->next = current->next;
    current->next = new_node;
    return SUCCESS;
}

// Добавление элемента в множество
ErrorCode set_insert(SetNode** head, const StudyGroup* group) {
    if (head == NULL || group == NULL) return ERR_GROUP_NAME;
    ErrorCode err = validate_study_group(group);
    if (err != SUCCESS) return err;
    printf("Добавление группы %s\n", group->group_name);
    return insert_ordered(head, group);
}

// Удаление заданного значения из списка
ErrorCode set_remove(SetNode** head, const char* group_name) {
    if (head == NULL || group_name == NULL) return ERR_GROUP_NAME;
    if (*head == NULL) {
        printf("Множество пусто, удаление невозможно\n");
        return ERR_GROUP_NAME;
    }
    SetNode* current = *head;
    SetNode* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->data->group_name, group_name) == 0) {
            if (prev == NULL) *head = current->next;
            else prev->next = current->next;
            printf("Удалена группа: %s\n", group_name);
            free(current->data);
            free(current);
            return SUCCESS;
        }
        prev = current;
        current = current->next;
    }
    printf("Группа %s не найдена в множестве\n", group_name);
    return ERR_GROUP_NAME;
}

// Проверка, есть ли заданное значение в списке
int set_contains(const SetNode* head, const char* group_name) {
    const SetNode* current = head;
    while (current != NULL) {
        if (strcmp(current->data->group_name, group_name) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Объединение множеств
SetNode* set_union(const SetNode* set1, const SetNode* set2) {
    SetNode* result = NULL;

    const SetNode* current = set1;
    while (current != NULL) {
        set_insert(&result, current->data);
        current = current->next;
    }
    
    current = set2;
    while (current != NULL) {
        set_insert(&result, current->data);
        current = current->next;
    }
    
    return result;
}

// Пересечение множеств
SetNode* set_intersection(const SetNode* set1, const SetNode* set2) {
    SetNode* result = NULL;
    
    const SetNode* current = set1;
    while (current != NULL) {
        if (set_contains(set2, current->data->group_name)) set_insert(&result, current->data);
        current = current->next;
    }

    return result;
}

// Печать множества
void print_set(const SetNode* head) {
    if (head == NULL) {
        printf("Множество пусто\n");
        return;
    }
    
    const SetNode* current = head;
    int count = 1;
    
    while (current != NULL) {
        printf("Элемент %d:\n", count++);
        print_study_group(current->data);
        printf("\n");
        current = current->next;
    }
}

// Удаление всего множества
void delete_set(SetNode* head) {
    SetNode* current = head;
    int count = 0;
    
    while (current != NULL) {
        SetNode* temp = current;
        current = current->next;
        
        free(temp->data);
        free(temp);
        count++;
    }
    
    printf("Удалено %d элементов множества\n", count);
}


// ==================== ОЧЕРЕДЬ (пункт 4) ====================

// Создания нового узла очереди
static QueueNode* create_queue_node(const StudyGroup* group) {
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

// Функция добавления элемента в конец очереди
QueueNode* enqueue(QueueNode* tail, const StudyGroup* group) {
    ErrorCode err = validate_study_group(group);
    if (err != SUCCESS) {
        printf("Ошибка: группа некорректна (код ошибки %d)\n", err);
        return tail;
    }
    QueueNode* new_node = create_queue_node(group);
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

// Функция удаления элемента из начала очереди
QueueNode* dequeue(QueueNode* tail, StudyGroup* result) {
    if (tail == NULL) {
        printf("Очередь пуста, удаление невозможно\n");
        return NULL;
    }
    
    QueueNode* head = tail->next;
    if (result != NULL) *result = head->data;

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

// Функция удаления всей очереди
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
    free(tail);
    count++;
    printf("Удалено %d элементов очереди\n", count);
    return NULL;
}

// Функция печати всех элементов очереди
void print_queue(const QueueNode* tail) {
    if (tail == NULL) {
        printf("Очередь пуста\n");
        return;
    }
    const QueueNode* current = tail->next;
    const QueueNode* head = current;
    int position = 1;
    
    printf("\n--- Содержимое очереди ---\n");
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