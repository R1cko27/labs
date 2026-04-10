#include "modules/list_structures.h"
#include "modules/list_structures.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdarg.h>

#define GROUP_COUNT 100
typedef struct btree {
  StudyGroup data;
  struct btree *left, *right;
} btree;

typedef struct FileTreeNode {
  StudyGroup data;
  long left_offset;
  long right_offset;
} FileTreeNode;

#define FILE_NODE_NULL (-1L)

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
        } else {
            return 1;
        }
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

static int saveTreeNodesToFile(FILE *file, long *root_offset, btree *node) {
    if (node == NULL) return 1;

    if (!insertStudyGroupToOpenedFile(file, root_offset, &node->data))
        return 0;

    if (!saveTreeNodesToFile(file, root_offset, node->left))
        return 0;

    return saveTreeNodesToFile(file, root_offset, node->right);
}

void saveTreeToFile(btree *root, const char *filename) {
    FILE *file = fopen(filename, "w+b");
    if (file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
        return;
    }

    long root_offset = FILE_NODE_NULL;
    if (!writeRootOffset(file, root_offset)) {
        fclose(file);
        return;
    }

    if (root != NULL && !saveTreeNodesToFile(file, &root_offset, root)) {
        printf("Ошибка сохранения дерева в файл %s\n", filename);
    }

    fclose(file);
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

static void collectGroupsFromFileTree(FILE *file, long offset, StudyGroup *groups, int *count, const StudyGroup *group_to_delete, int *deleted) {
    if (offset == FILE_NODE_NULL || *count >= GROUP_COUNT) return;

    FileTreeNode node;
    if (!readFileTreeNode(file, offset, &node)) return;

    if (group_to_delete != NULL && !(*deleted) && are_study_groups_equal(&node.data, group_to_delete)) {
        *deleted = 1;
    } else {
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