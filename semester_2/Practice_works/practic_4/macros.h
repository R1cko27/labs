/**
 * @file macros.h
 * @brief Обработка макросов препроцессора
 * 
 * Практическое занятие 4: Бинарные деревья поиска
 * 
 * @author Панфилов А.П., Иманкулов С.А.
 * 
 * GitHub: https://github.com/R1cko27/labs/tree/main/semester_2/Practice_works/practic_4
*/

#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct btree {
    char* ident;      // идентификатор макроса
    char* replace;     // строка замещения
    struct btree* left;
    struct btree* right;
} btree;


// Функции для работы с деревом
int countNodes(btree* node);
void Ins_Btree_edit(char* ident, char* repl, btree **q);
int Delete_edit(char* ident, btree **q);
void printTreeInOrder(btree* root);
void freeTree(btree* root);

// Функции для работы со строчками файла
void skipspace(char* line, int* pos);
int skipchars_ident(char* line, int* pos);
int skipchars_replace(char* line, int* pos);

#endif