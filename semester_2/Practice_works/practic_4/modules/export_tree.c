/**
 * @file export_tree.c
 * @brief Экспорт дерева макросов в JSON
 * 
 * Результат экспорта можно визуализировать на сайте:
 * https://artem.email/tree
*/

#include "../macros.h"
#include <string.h>

void escape_json_string(const char *src, char *dest, size_t dest_size) {
    size_t i = 0, j = 0;
    int len = strlen(src);

    while (i < len && j < dest_size - 1) {
        switch (src[i]) {
            case '"':
                if (j + 2 < dest_size - 1) {
                    dest[j++] = '\\';
                    dest[j++] = '"';
                }
                break;
            case '\\':
                if (j + 2 < dest_size - 1) {
                    dest[j++] = '\\';
                    dest[j++] = '\\';
                }
                break;
            case '\n':
                if (j + 2 < dest_size - 1) {
                    dest[j++] = '\\';
                    dest[j++] = 'n';
                }
                break;
            case '\r':
                if (j + 2 < dest_size - 1) {
                    dest[j++] = '\\';
                    dest[j++] = 'r';
                }
                break;
            case '\t':
                if (j + 2 < dest_size - 1) {
                    dest[j++] = '\\';
                    dest[j++] = 't';
                }
                break;
            default:
                dest[j++] = src[i];
                break;
        }
        i++;
    }
    dest[j] = '\0';
}

void truncate_and_escape(const char *str, char *output, size_t output_size) {
    char truncated[256];
    int len = strlen(str);
    
    if (len <= 5) {
        strcpy(truncated, str);
    } else {
        strncpy(truncated, str, 5);
        truncated[5] = '\0';
        strcat(truncated, "...");
    }
    escape_json_string(truncated, output, output_size);
}

void export_tree_to_json_rec(FILE *file, btree *node) {
    if (node == NULL) {
        fprintf(file, "null");
        return;
    }
    
    char escaped_ident[256];
    char escaped_replace[256];
    
    truncate_and_escape(node->ident, escaped_ident, sizeof(escaped_ident));
    truncate_and_escape(node->replace, escaped_replace, sizeof(escaped_replace));
    
    fprintf(file, "{");
    fprintf(file, "\"value\": \"%s -> %s\"", escaped_ident, escaped_replace);
    
    fprintf(file, ", \"left\": ");
    export_tree_to_json_rec(file, node->left);
    
    fprintf(file, ", \"right\": ");
    export_tree_to_json_rec(file, node->right);
    
    fprintf(file, "}");
}

int export_tree_to_json(btree *root, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
        return 0;
    }
    export_tree_to_json_rec(file, root);
    fclose(file);
    return 1;
}