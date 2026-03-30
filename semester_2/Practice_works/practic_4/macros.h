#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_IDENT_LEN 256
#define MAX_REPLACE_LEN 1024

typedef struct btree {
    char* identifier;      // идентификатор макроса
    char* replacement;     // строка замещения
    struct btree* left;
    struct btree* right;
} btree;

// Функции для работы с деревом
int countNodes(btree* node);
void Ins_Btree_edit(const char* ident, const char* repl, btree **q);
int Delete_edit(const char* key, btree **node);
void freeTree(btree* root);
void printTreeInOrder(btree* root);

#endif // MACROS_H