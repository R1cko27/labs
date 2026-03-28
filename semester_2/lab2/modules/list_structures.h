#ifndef LIST_STRUCTURES_H
#define LIST_STRUCTURES_H

#include "study_group.h"


// Стек (пункт 2)
typedef struct Node {
    StudyGroup data;
    struct Node* next;
} Node;

Node* push(Node* head, const StudyGroup* group);
Node* pop(Node* head);
void print_list(const Node* head);
void delete_list(Node* head);


// Множество (set) (пункт 3.2)
typedef struct SetNode {
    StudyGroup* data;
    struct SetNode* next;
} SetNode;

ErrorCode set_insert(SetNode** head, const StudyGroup* group);
ErrorCode set_remove(SetNode** head, const char* group_name);
int set_contains(const SetNode* head, const char* group_name);// Проверка, есть ли заданное значение в множестве
SetNode* set_union(const SetNode* set1, const SetNode* set2); // Объединение
SetNode* set_intersection(const SetNode* set1, const SetNode* set2); // Пересечение
void print_set(const SetNode* head);
void delete_set(SetNode* head);


// Очередь (пункт 4)
typedef struct QueueNode {
    StudyGroup data;
    struct QueueNode* next;
    struct QueueNode* prev;
} QueueNode;

QueueNode* enqueue(QueueNode* tail, const StudyGroup* group); // Добавление элемента
QueueNode* dequeue(QueueNode* tail, StudyGroup* result); // Удаление элемента
QueueNode* delete_queue(QueueNode* tail);
void print_queue(const QueueNode* tail);
int is_queue_empty(const QueueNode* tail);

#endif