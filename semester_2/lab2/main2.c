#include "study_group.h"
#include "list_structures.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdarg.h>

#define GROUP_COUNT 100
typedef struct btree {
  StudyGroup data;
  struct btree *left, *right;
} btree;

void Ins_Btree_edit(StudyGroup* group, btree **q) {
  if(*q == NULL) {
    *q = malloc(sizeof(btree));
    (*q)->left = (*q)->right = NULL;
    (*q)->data = *group;
    return;
  }

  if (is_study_group_less(&(*q)->data , group))
    Ins_Btree_edit(group, &(*q)->left);
  else if (is_study_group_less(group , &(*q)->data))
    Ins_Btree_edit(group, &(*q)->right);
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

int countNodes(btree *p){
    if (p == NULL){
        return 0;
    }
    return 1+countNodes(p->left)+countNodes(p->right);
}

int Delete_edit(StudyGroup* group, btree **node) {
  btree *t, *up;
  if(*node == NULL) return 0;
  
  if (are_study_groups_equal(&(*node)->data, group)) {
    if(((*node)->left == NULL) && ((*node)->right == NULL)) { 
      free(*node);
      *node = NULL; 
      printf("Delete List\n");
      return 1;
    }
    if((*node)->left == NULL) { 
      t = *node; 
      *node =(*node)->right; 
      free(t); 
      printf("Delete Left = 0\n");
      return 1;
    }
    if((*node)->right == NULL) { 
      t = *node; 
      *node =(*node)->left; 
      free(t); 
      printf("Delete Right = 0\n");
      return 1;
    }
    up = *node;
    if (countNodes((*node)->left) >= countNodes((*node)->right)){ //СМОТРИМ В КАКОЙ СТОРОНЕ УЗЛОВ БОЛЬШЕ 
        t = (*node)->left;
    } else t = (*node)->right;
    while (t->right != NULL) {
      up = t;
      t = t-> right; 
    }
    (*node)->data = t->data;
    if (up != (*node)) {    
      if(t->left != NULL) up->right = t->left;
      else up->right = NULL;
    }
    else (*node)->left = t->left;
    free(t);
    printf("Delete Two\n");
    return 1;
  }
  if (is_study_group_less(group, &(*node)->data))
    return Delete_edit(group, &(*node)->right);
  return Delete_edit(group, &(*node)->left);
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
    while (fgets(line, sizeof(line), file) != NULL && read_count < GROUP_COUNT) {
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

void writeNodeToFile(btree *node, FILE *file) {
    if (node == NULL) return;
    writeNodeToFile(node->left, file);
    fwrite(&node->data, sizeof(StudyGroup), 1, file);
    writeNodeToFile(node->right, file);
}

void createBin(btree *root, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Ошибка открытия файла %s для записи\n", filename);
        return;
    }
    writeNodeToFile(root, file);
    fclose(file);
    printf("Дерево успешно записано в файл %s\n", filename);
}

void readBinAndAddToTree(const char *filename, btree **root) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Ошибка открытия файла %s для чтения\n", filename);
        return;
    }
    StudyGroup temp;
    int count = 0;
    while (fread(&temp, sizeof(StudyGroup), 1, file) == 1) {
        Ins_Btree_edit(&temp, root);
    }
    
    fclose(file);
}

void export_tree_to_json_rec(FILE *file, btree *node) {
    if (node == NULL) {
        fprintf(file, "null");
        return;
    }
    
    fprintf(file, "{");
    fprintf(file, "\"value\": \"%s\", ", node->data.group_name);
    
    fprintf(file, "\"left\": ");
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

static void writeNode(FILE *file, btree *node) {
    if (node == NULL) {
        int marker = 0;
        fwrite(&marker, sizeof(int), 1, file);
        return;
    }
    
    int marker = 1;
    fwrite(&marker, sizeof(int), 1, file);
    fwrite(&node->data, sizeof(StudyGroup), 1, file);
    writeNode(file, node->left);
    writeNode(file, node->right);
}

void saveTreeToFile(btree *root, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        writeNode(file, root);
        fclose(file);
    }
}

static btree* readNode(FILE *file) {
    int marker;
    if (fread(&marker, sizeof(int), 1, file) != 1) return NULL;
    
    if (marker == 0) return NULL;
    
    btree *node = (btree*)malloc(sizeof(btree));
    fread(&node->data, sizeof(StudyGroup), 1, file);
    node->left = readNode(file);
    node->right = readNode(file);
    
    return node;
}

btree* loadTreeFromFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
        return NULL;
    }
    
    btree *root = readNode(file);
    fclose(file);

    return root;
}

int main(){
  // =============== ПУНКТ 2 ===============
    StudyGroup groups[GROUP_COUNT];
    btree *root1 = NULL;
    int choice;
    int count = 0;
    int mode;
    
    printf("Выберите режим ввода:\n");
    printf("1) Из файла\n");
    printf("2) Вручную\n");
    printf("Ваш выбор: ");
    scanf("%d", &mode);
    
    if (mode == 1) {
        count = readGroupsFromFile("groups.txt", groups, GROUP_COUNT);
    } else if (mode == 2) {
        printf("Введите количество групп для ввода: ");
        scanf("%d", &count);
        if (count > GROUP_COUNT) count = GROUP_COUNT;
        
        for (int i = 0; i < count; i++) {
            char name[11];
            char dir_str[3];
            int year;
            char level_str[2];
            
            printf("\nВведите данные для группы %d:\n", i+1);
            printf("Название группы (макс 10 символов): ");
            scanf("%10s", name);
            printf("Направление (IS, PI, AI, PR, VT): ");
            scanf("%2s", dir_str);
            printf("Год формирования: ");
            scanf("%d", &year);
            printf("Уровень образования (B или M): ");
            scanf("%1s", level_str);
            
            StudyDirection dir = string_to_direction(dir_str);
            EducationLevel level = string_to_level(level_str);
            
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            int current_year = tm.tm_year + 1900;
            
            if (year < current_year - 4 || year > current_year) {
                year = current_year;
            }
            
            ErrorCode err = init_study_group(&groups[i], name, dir, year, level);
            if (err != SUCCESS) {
                printf("Ошибка при создании структуры для группы %s, используем значения по умолчанию\n");
                init_study_group(&groups[i], "AP-526", PI, 2025, B);
            }
        }
    }
    
    if (count > 0){
      for (int i = 0; i < count; i++) {
          Ins_Btree_edit(&groups[i], &root1);
          printf("Добавлен элемент %d: %s\n", i + 1, groups[i].group_name);
      }

      printf("\nДерево до удаления:\n");
      printTreeRec(root1, 0, 5);
      export_tree_to_json(root1, "export3.json");
      printf("\n");

      printf("\nСписок групп");
      for (int i = 0; i < count; i++){
        printf("\n %d. %s", i+1, groups[i].group_name);
      }
      printf("\nВыбирите группу для удаления:");
      scanf("%d", &choice);
      Delete_edit(&groups[choice-1], &root1);

      printf("\nПосле удаления %s:\n", groups[choice-1].group_name);
      printTreeRec(root1, 0, 5);
      printf("\n");
      export_tree_to_json(root1, "export4.json");
      createBin(root1, "tree.bin");
    }

    // =============== ПУНКТ 3 ===============
    btree *root2 = NULL;
    readBinAndAddToTree("tree.bin", &root2);
    printf("\n Дерево воссозданное из файла tree.bin");
    export_tree_to_json(root2, "export5.json");
    deleteTree(&root2);

    saveTreeToFile(root1, "full_tree.bin");
    deleteTree(&root1);

    btree *root3 = loadTreeFromFile("full_tree.bin");
    printTreeRec(root3, 0, 5);
    export_tree_to_json(root3, "export6.json");
    deleteTree(&root3);
    return 0;
}