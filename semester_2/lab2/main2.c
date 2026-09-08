#include "modules/list_structures.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdarg.h>

#define GROUP_COUNT 100
#define FILE_NODE_NULL (-1L)

typedef struct btree {
  StudyGroup data;
  struct btree *left, *right;
} btree;

typedef struct FileTreeNode {
  StudyGroup data;
  long left_offset;
  long right_offset;
} FileTreeNode;

static int writeRootOffset(FILE *file, long root_offset) {
    rewind(file);
    return fwrite(&root_offset, sizeof(long), 1, file) == 1;
}

static int readRootOffset(FILE *file, long *root_offset) {
    rewind(file);
    return fread(root_offset, sizeof(long), 1, file) == 1;
}

static long appendFileTreeNode(FILE *file, const StudyGroup *group) {
    FileTreeNode node;
    node.data = *group;
    node.left_offset = FILE_NODE_NULL;
    node.right_offset = FILE_NODE_NULL;

    if (fseek(file, 0, SEEK_END) != 0) return FILE_NODE_NULL;

    long offset = ftell(file);
    if (offset == -1L) return FILE_NODE_NULL;

    if (fwrite(&node, sizeof(FileTreeNode), 1, file) != 1)
        return FILE_NODE_NULL;

    return offset;
}

static int readFileTreeNode(FILE *file, long offset, FileTreeNode *node) {
    if (offset == FILE_NODE_NULL) return 0;
    if (fseek(file, offset, SEEK_SET) != 0) return 0;
    return fread(node, sizeof(FileTreeNode), 1, file) == 1;
}

static int writeFileTreeNode(FILE *file, long offset, const FileTreeNode *node) {
    if (fseek(file, offset, SEEK_SET) != 0) return 0;
    return fwrite(node, sizeof(FileTreeNode), 1, file) == 1;
}

static int insertStudyGroupToOpenedFile(FILE *file, long *root_offset, const StudyGroup *group) {
    if (group == NULL) return 0;

    if (*root_offset == FILE_NODE_NULL) {
        long new_offset = appendFileTreeNode(file, group);
        if (new_offset == FILE_NODE_NULL) return 0;

        *root_offset = new_offset;
        return writeRootOffset(file, *root_offset);
    }

    long current_offset = *root_offset;

    while (current_offset != FILE_NODE_NULL) {
        FileTreeNode current;
        if (!readFileTreeNode(file, current_offset, &current)) return 0;

        if (are_study_groups_equal(&current.data, group)) {
            return 1;
        }

        if (is_study_group_less(&current.data, group)) {
            if (current.left_offset == FILE_NODE_NULL) {
                long new_offset = appendFileTreeNode(file, group);
                if (new_offset == FILE_NODE_NULL) return 0;

                current.left_offset = new_offset;
                return writeFileTreeNode(file, current_offset, &current);
            }
            current_offset = current.left_offset;
        } else if (is_study_group_less(group, &current.data)) {
            if (current.right_offset == FILE_NODE_NULL) {
                long new_offset = appendFileTreeNode(file, group);
                if (new_offset == FILE_NODE_NULL) return 0;

                current.right_offset = new_offset;
                return writeFileTreeNode(file, current_offset, &current);
            }
            current_offset = current.right_offset;
        } else return 1;
        
    }

    return 0;
}

int insertStudyGroupToFileTree(const char *filename, const StudyGroup *group) {
    FILE *file = fopen(filename, "r+b");
    if (file == NULL) {
        file = fopen(filename, "w+b");
        if (file == NULL) {
            printf("Ошибка открытия файла %s\n", filename);
            return 0;
        }

        if (!writeRootOffset(file, FILE_NODE_NULL)) {
            fclose(file);
            return 0;
        }
    }

    long root_offset;
    if (!readRootOffset(file, &root_offset)) {
        fclose(file);
        return 0;
    }

    int result = insertStudyGroupToOpenedFile(file, &root_offset, group);
    fclose(file);
    return result;
}

static void collectGroupsFromFileTree(FILE *file, long offset, StudyGroup *groups, int *count, const StudyGroup *group_to_delete, int *deleted) {
    if (offset == FILE_NODE_NULL || *count >= GROUP_COUNT) return;

    FileTreeNode node;
    if (!readFileTreeNode(file, offset, &node)) return;

    if (group_to_delete != NULL && !(*deleted) && are_study_groups_equal(&node.data, group_to_delete)) *deleted = 1;
    else {
        groups[*count] = node.data;
        (*count)++;
    }

    collectGroupsFromFileTree(file, node.left_offset, groups, count, group_to_delete, deleted);
    collectGroupsFromFileTree(file, node.right_offset, groups, count, group_to_delete, deleted);
}

int deleteStudyGroupFromFileTree(const char *filename, const StudyGroup *group) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
        return 0;
    }

    long root_offset;
    if (!readRootOffset(file, &root_offset)) {
        fclose(file);
        return 0;
    }

    StudyGroup groups_buffer[GROUP_COUNT];
    int groups_count = 0;
    int deleted = 0;

    collectGroupsFromFileTree(file, root_offset, groups_buffer, &groups_count, group, &deleted);
    fclose(file);

    if (!deleted) return 0;
    
    file = fopen(filename, "w+b");
    if (file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
        return 0;
    }

    long new_root_offset = FILE_NODE_NULL;
    if (!writeRootOffset(file, new_root_offset)) {
        fclose(file);
        return 0;
    }

    for (int i = 0; i < groups_count; i++) {
        if (!insertStudyGroupToOpenedFile(file, &new_root_offset, &groups_buffer[i])) {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

static btree* loadNodeFromFile(FILE *file, long offset) {
    if (offset == FILE_NODE_NULL) return NULL;

    FileTreeNode stored;
    if (!readFileTreeNode(file, offset, &stored)) return NULL;

    btree *node = (btree*)malloc(sizeof(btree));
    if (node == NULL) return NULL;

    node->data = stored.data;
    node->left = loadNodeFromFile(file, stored.left_offset);
    node->right = loadNodeFromFile(file, stored.right_offset);

    return node;
}

btree* loadTreeFromFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
        return NULL;
    }

    long root_offset;
    if (!readRootOffset(file, &root_offset)) {
        fclose(file);
        return NULL;
    }

    btree *root = loadNodeFromFile(file, root_offset);
    fclose(file);

    return root;
}

void printFileTreeContents(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
        return;
    }

    long root_offset;
    if (!readRootOffset(file, &root_offset)) {
        fclose(file);
        return;
    }

    printf("\nСодержимое файла %s:\n", filename);
    printf("root_offset = %ld\n", root_offset);

    if (fseek(file, sizeof(long), SEEK_SET) != 0) {
        fclose(file);
        return;
    }

    FileTreeNode node;
    long offset = sizeof(long);
    int index = 0;

    while (fread(&node, sizeof(FileTreeNode), 1, file) == 1) {
        printf("[%d] offset=%ld group=%s left=%ld right=%ld\n",
               index,
               offset,
               node.data.group_name,
               node.left_offset,
               node.right_offset);
        offset = ftell(file);
        index++;
    }

    fclose(file);
}


static void printTreeRec(btree *root, int space, int level) {
    if (root == NULL) return;
    space += level;
    printTreeRec(root->right, space, level);
    printf("\n");
    for (int i = level; i < space; i++)
        printf(" ");
    printf("%s\n", root->data.group_name);
    printTreeRec(root->left, space, level);
}

void deleteTree(btree **root) {
    if (*root == NULL) return;
    
    btree* stack[1000];
    int top = -1;
    
    stack[++top] = *root;
    
    while (top >= 0) {
        btree* current = stack[top--];
        if (current->left != NULL)
            stack[++top] = current->left;
        if (current->right != NULL)
            stack[++top] = current->right;
        free(current);
    }
    
    *root = NULL;
}

StudyDirection string_to_direction(const char* str) {
    if (strcmp(str, "IS") == 0) return IS;
    if (strcmp(str, "PI") == 0) return PI;
    if (strcmp(str, "AI") == 0) return AI;
    if (strcmp(str, "PR") == 0) return PR;
    if (strcmp(str, "VT") == 0) return VT;
    return IS;
}

EducationLevel string_to_level(const char* str) {
    return (strcmp(str, "B") == 0) ? B : M;
}

int readGroupsFromFile(const char* filename, StudyGroup* groups, int maxGroups) {
    FILE* file = fopen(filename, "r");
    char line[256];
    int read_count = 0;
    while (fgets(line, sizeof(line), file) != NULL && read_count < maxGroups) {
        line[strcspn(line, "\n")] = 0;
        char* token = strtok(line, ";");
        if (token == NULL) continue;

        char group_name[11] = {0};
        strncpy(group_name, token, 10);
        
        token = strtok(NULL, ";");
        if (token == NULL) continue;
        StudyDirection dir = string_to_direction(token);
        
        token = strtok(NULL, ";");
        if (token == NULL) continue;
        int year = atoi(token);
        
        token = strtok(NULL, ";");
        if (token == NULL) continue;
        EducationLevel level = string_to_level(token);
        
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        int current_year = tm.tm_year + 1900;
        
        if (year < current_year - 4 || year > current_year) {
            year = current_year;
        }

        ErrorCode err = init_study_group(&groups[read_count], group_name, dir, year, level);
        if (err != SUCCESS) {
            printf("Ошибка при создании структуры из строки %d, используем значения по умолчанию\n", read_count);
            init_study_group(&groups[read_count], "DEFAULT", IS, 2023, B);
        }
        read_count++;
    }
    fclose(file);
    return read_count;
}

int main(){
    StudyGroup groups[GROUP_COUNT];
    int count = 0;
    count = readGroupsFromFile("groups.txt", groups, GROUP_COUNT);

    if (count > 0) {
        const char *file_tree_name = "output/file_tree_direct.bin";
        btree *root4;
        remove(file_tree_name);

        for (int i = 0; i < count; i++) {
            if (insertStudyGroupToFileTree(file_tree_name, &groups[i])) 
                printf("Добавлен в файловое дерево: %s\n", groups[i].group_name);
            
        }

        printFileTreeContents(file_tree_name);

        printf("\nУдаляем из файлового дерева группу %s\n", groups[0].group_name);
        if (deleteStudyGroupFromFileTree(file_tree_name, &groups[0])) printf("Удаление из файла выполнено успешно.\n");
        else printf("Не удалось удалить группу из файлового дерева.\n");
        

        printf("\nУдаляем из файлового дерева группу %s\n", groups[6].group_name);
        if (deleteStudyGroupFromFileTree(file_tree_name, &groups[6])) printf("Удаление из файла выполнено успешно.\n");
        else printf("Не удалось удалить группу из файлового дерева.\n");
    

        printFileTreeContents(file_tree_name);

        root4 = loadTreeFromFile(file_tree_name);
        if (root4 != NULL) {
            printf("\nСтруктура файлового дерева после удаления:\n");
            printTreeRec(root4, 0, 5);
            deleteTree(&root4);
        }
    }

    return 0;
}