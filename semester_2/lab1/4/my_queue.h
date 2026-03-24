#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include "study_group.h"

// Структура элемента двусвязного списка
typedef struct QueueNode {
    StudyGroup data;           // Данные (объект StudyGroup) - по значению
    struct QueueNode* next;    // Указатель на следующий элемент
    struct QueueNode* prev;    // Указатель на предыдущий элемент
} QueueNode;

// Функция добавления элемента в конец очереди
QueueNode* enqueue(QueueNode* tail, const StudyGroup* group);
// Функция удаления элемента из начала очереди
QueueNode* dequeue(QueueNode* tail, StudyGroup* result);
// Функция удаления всей очереди
QueueNode* delete_queue(QueueNode* tail);
// Функция печати всех элементов очереди
void print_queue(const QueueNode* tail);
// Функция проверки на пустоту
int is_queue_empty(const QueueNode* tail);

#endif