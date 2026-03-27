// macros.h
// Заголовочный файл для программы анализа макросов

#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_IDENT_LEN 256
#define MAX_REPLACE_LEN 1024

// Структура узла бинарного дерева
typedef struct btree {
    char* identifier;      // идентификатор макроса
    char* replacement;     // строка замещения
    struct btree* left;
    struct btree* right;
} btree;

// Функции для работы с деревом
// Подсчет количества узлов в дереве
int countNodes(btree* node);

// Вставка узла в дерево
void Ins_Btree_edit(const char* ident, const char* repl, btree **q);

// Удаление узла из дерева
int Delete_edit(const char* key, btree **node);

// Освобождение памяти дерева
void freeTree(btree* root);

// Вывод дерева в порядке возрастания
void printTreeInOrder(btree* root);

#endif // MACROS_H