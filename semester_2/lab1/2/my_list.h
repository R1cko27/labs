#ifndef MY_LIST_H
#define MY_LIST_H

#include "study_group.h"

// Структура элемента односвязного списка
typedef struct Node {
    StudyGroup data;        // Данные
    struct Node* next;      // Указатель на следующий элемент
} Node;

// Добавление элемента в начало списка
Node* push(Node* head, const StudyGroup* group);
// Удаление элемента из начала списка
Node* pop(Node* head);
// Печать всех элементов списка
void print_list(const Node* head);
// Удаление всего списка
void delete_list(Node* head);

#endif