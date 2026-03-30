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
    else { // Если идентификатор уже существует, обновляем строку замещения
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
        int flag = 1;
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
        printf("Введите название файла для анализа макросов: ");
        if (fgets(filename, sizeof(filename), stdin) == NULL) {
            printf("Ошибка ввода\n");
            return 1;
        }
        size_t len = strlen(filename);
        if (len > 0 && filename[len-1] == '\n') filename[len-1] = '\0';
    
    }
    
    file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка: не удалось открыть файл '%s'\n", filename);
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') line[len-1] = '\0';
        
        int pos = 0;
        
        while (line[pos] && isspace(line[pos])) pos++; // Пропускаем начальные пробелы
        
        if (line[pos] == '#') {
            pos++;
            while (line[pos] && isspace(line[pos])) pos++;// Пропускаем пробелы после '#'
            if (strncmp(line + pos, "define", 6) == 0 && (isspace(line[pos + 6]) || line[pos + 6] == '\0')) {
                // Обработка #define
                char* p = line + pos + 6;
                while (*p && isspace(*p)) p++; // Пропускаем пробелы после 'define'
                if (*p) {
                    char* ident_start = p;
                    while (*p && (isalnum(*p) || *p == '_')) p++; // Идентификатор может состоять из букв, цифр и подчеркиваний
                    
                    char ident[256];
                    int ident_len = p - ident_start; // разница указателей = длина идентификатора   
                    strncpy(ident, ident_start, ident_len); // Копируем идентификатор
                    ident[ident_len] = '\0';
                    
                    while (*p && isspace(*p)) p++; // Пропускаем пробелы между идентификатором и строкой замещения
                    
                    char replacement[MAX_REPLACE_LEN];
                    int i = 0;
                    while (*p && i < MAX_REPLACE_LEN - 1) replacement[i++] = *p++; // Копируем строку замещения
                    replacement[i] = '\0';
                    
                    while (i > 0 && isspace(replacement[--i])) replacement[i] = '\0'; // Удаляем пробелы в конце строки замещения
                    
                    Ins_Btree_edit(ident, replacement, &root); // Вставляем в дерево
                }
            }
            else if (strncmp(line + pos, "undef", 5) == 0 && (isspace(line[pos + 5]) || line[pos + 5] == '\0')) {
                // Обработка #undef
                char* p = line + pos + 5;
                while (*p && isspace(*p)) p++; // Пропускаем пробелы после 'undef'
                
                if (*p) {
                    char* ident_start = p;
                    while (*p && (isalnum(*p) || *p == '_')) p++; // Идентификатор может состоять из букв, цифр и подчеркиваний
                    
                    char ident[256];
                    int ident_len = p - ident_start; // разница указателей = длина идентификатора
                    strncpy(ident, ident_start, ident_len); // Копируем идентификатор
                    ident[ident_len] = '\0';
                    
                    Delete_edit(ident, &root); //   Удаляем из дерева
                }
            }
        }
    }
    
    fclose(file);
    
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