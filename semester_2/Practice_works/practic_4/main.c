// main.c
// Программа для анализа макросов в файлах на языке C

#include "macros.h"

// Подсчет количества узлов в дереве
int countNodes(btree* node) {
    if (node == NULL) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

// Вставка узла в дерево
void Ins_Btree_edit(const char* ident, const char* repl, btree **q) {
    if (*q == NULL) {
        *q = malloc(sizeof(btree));
        (*q)->left = (*q)->right = NULL;
        (*q)->identifier = (char*)malloc(strlen(ident) + 1);
        (*q)->replacement = (char*)malloc(strlen(repl) + 1);
        strcpy((*q)->identifier, ident);
        strcpy((*q)->replacement, repl);
        return;
    }

    if (strcmp((*q)->identifier, ident) > 0)
        Ins_Btree_edit(ident, repl, &(*q)->left);
    else if (strcmp((*q)->identifier, ident) < 0)
        Ins_Btree_edit(ident, repl, &(*q)->right);
    else {
        // Если идентификатор уже существует, обновляем строку замещения
        free((*q)->replacement);
        (*q)->replacement = (char*)malloc(strlen(repl) + 1);
        strcpy((*q)->replacement, repl);
    }
}

// Удаление узла из дерева
int Delete_edit(const char* key, btree **node) {
    btree *t, *up;
    if(*node == NULL) return 0;
    
    if(strcmp((*node)->identifier, key) == 0) {
        if(((*node)->left == NULL) && ((*node)->right == NULL)) { 
            free((*node)->identifier);
            free((*node)->replacement);
            free(*node);
            *node = NULL; 
            printf("Delete List\n");
            return 1;
        }
        if((*node)->left == NULL) { 
            t = *node;  
            *node = (*node)->right; 
            free(t->identifier);
            free(t->replacement);
            free(t); 
            printf("Delete Left = 0\n");
            return 1;
        }
        if((*node)->right == NULL) { 
            t = *node; 
            *node =(*node)->left; 
            free(t->identifier);
            free(t->replacement);
            free(t); 
            printf("Delete Right = 0\n");
            return 1;
        }
        up = *node;
        if (countNodes((*node)->left) >= countNodes((*node)->right)) {
            t = (*node)->left;
        } else t = (*node)->right;
        while (t->right != NULL) {
            up = t;
            t = t->right; 
        }
        // Копируем данные из найденного узла
        free((*node)->identifier);
        free((*node)->replacement);
        (*node)->identifier = (char*)malloc(strlen(t->identifier) + 1);
        (*node)->replacement = (char*)malloc(strlen(t->replacement) + 1);
        strcpy((*node)->identifier, t->identifier);
        strcpy((*node)->replacement, t->replacement);
        
        if (up != (*node)) {    
            if(t->left != NULL) up->right = t->left;
            else up->right = NULL;
        }
        else (*node)->left = t->left;
        
        free(t->identifier);
        free(t->replacement);
        free(t);
        printf("Delete Two\n");
        return 1;
    }
    if(strcmp((*node)->identifier, key) < 0)
        return Delete_edit(key, &(*node)->right);
    return Delete_edit(key, &(*node)->left);
}

// Освобождение памяти дерева
void freeTree(btree* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root->identifier);
    free(root->replacement);
    free(root);
}

// Вывод дерева в порядке возрастания
void printTreeInOrder(btree* root) {
    if (root == NULL) return;
    printTreeInOrder(root->left);
    printf("  %s -> %s\n", root->identifier, root->replacement);
    printTreeInOrder(root->right);
}

int main(int argc, char* argv[]) {
    char filename[512];
    FILE* file = NULL;
    btree* root = NULL;
    char line[2048];
    
    // Получение имени файла
    if (argc > 1) {
        strncpy(filename, argv[1], sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';
    } else {
        printf("Введите имя файла для анализа: ");
        if (fgets(filename, sizeof(filename), stdin) == NULL) {
            printf("Ошибка ввода\n");
            return 1;
        }
        size_t len = strlen(filename);
        if (len > 0 && filename[len-1] == '\n') {
            filename[len-1] = '\0';
        }
    }
    
    // Открываем файл
    file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка: не удалось открыть файл '%s'\n", filename);
        return 1;
    }
    
    // Последовательно считываем и обрабатываем строки
    while (fgets(line, sizeof(line), file)) {
        // Удаляем символ новой строки
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        
        // Пропускаем начальные пробелы
        int pos = 0;
        while (line[pos] && isspace(line[pos])) pos++;
        
        // Проверяем, начинается ли строка с '#'
        if (line[pos] == '#') {
            pos++;
            // Пропускаем пробелы после '#'
            while (line[pos] && isspace(line[pos])) pos++;
            
            // Проверяем на #define
            if (strncmp(line + pos, "define", 6) == 0 && (isspace(line[pos + 6]) || line[pos + 6] == '\0')) {
                // Обработка #define
                int definePos = pos + 6;
                while (line[definePos] && isspace(line[definePos])) definePos++;
                
                if (line[definePos]) {
                    // Извлекаем идентификатор
                    int identStart = definePos;
                    while (line[definePos] && (isalnum(line[definePos]) || line[definePos] == '_')) {
                        definePos++;
                    }
                    
                    int identLen = definePos - identStart;
                    char* ident = (char*)malloc(identLen + 1);
                    if (ident) {
                        strncpy(ident, line + identStart, identLen);
                        ident[identLen] = '\0';
                        
                        // Пропускаем пробелы перед строкой замещения
                        while (line[definePos] && isspace(line[definePos])) definePos++;
                        
                        // Строка замещения - всё, что осталось
                        char replacement[MAX_REPLACE_LEN];
                        int replPos = 0;
                        while (line[definePos] && replPos < MAX_REPLACE_LEN - 1) {
                            replacement[replPos++] = line[definePos++];
                        }
                        replacement[replPos] = '\0';
                        
                        // Удаляем завершающие пробелы
                        while (replPos > 0 && isspace(replacement[replPos - 1])) {
                            replacement[--replPos] = '\0';
                        }
                        
                        // Вставляем в дерево
                        Ins_Btree_edit(ident, replacement, &root);
                        free(ident);
                    }
                }
            }
            // Проверяем на #undef
            else if (strncmp(line + pos, "undef", 5) == 0 && (isspace(line[pos + 5]) || line[pos + 5] == '\0')) {
                // Обработка #undef
                int undefPos = pos + 5;
                while (line[undefPos] && isspace(line[undefPos])) undefPos++;
                
                if (line[undefPos]) {
                    // Извлекаем идентификатор
                    int identStart = undefPos;
                    while (line[undefPos] && (isalnum(line[undefPos]) || line[undefPos] == '_')) {
                        undefPos++;
                    }
                    
                    int identLen = undefPos - identStart;
                    char* ident = (char*)malloc(identLen + 1);
                    if (ident) {
                        strncpy(ident, line + identStart, identLen);
                        ident[identLen] = '\0';
                        
                        // Удаляем из дерева
                        Delete_edit(ident, &root);
                        free(ident);
                    }
                }
            }
        }
    }
    
    fclose(file);
    
    export_tree_to_json(root, "macros.json");
    // Выводим результат
    if (root == NULL) {
        printf("Файл пуст или не содержит макросов.\n");
    } else {
        printf("\nМакросы в алфавитном порядке:\n");
        printTreeInOrder(root);
        freeTree(root);
    }
    
    return 0;
}