#ifndef SET_LIST_H
#define SET_LIST_H

#include "study_group.h"

// Структура элемента списка
typedef struct SetNode {
    StudyGroup* data;        // Указатель на данные
    struct SetNode* next;    // Указатель на следующий элемент
} SetNode;

// Добавление элемента в множество (без повторов)
ErrorCode set_insert(SetNode** head, const StudyGroup* group);
// Удаление заданного значения из списка
ErrorCode set_remove(SetNode** head, const char* group_name);
// Проверка, есть ли заданное значение в списке
int set_contains(const SetNode* head, const char* group_name);
// Объединение множеств
SetNode* set_union(const SetNode* set1, const SetNode* set2);
// Пересечение множеств
SetNode* set_intersection(const SetNode* set1, const SetNode* set2);
// Печать множества
void print_set(const SetNode* head);
// Удаление всего множества
void delete_set(SetNode* head);

#endif