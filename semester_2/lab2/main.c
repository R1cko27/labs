#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <stdarg.h>

typedef struct btree {
  int value; // Значеник которое хранит узел
  struct btree *left, *right; // Указатели на потомков
} btree;

// Поиск с включением без дубликатов
void Ins_Btree_edit(int val, btree **q) {
  if(*q == NULL) {
    *q = malloc(sizeof(btree));
    (*q)->left = (*q)->right = NULL;
    (*q)->value = val;
    return;
  }

  if ((*q)->value > val)
    Ins_Btree_edit(val, &(*q)->left);
  else if ((*q)->value < val)
    Ins_Btree_edit(val, &(*q)->right);
}

static void printTreeRec(btree *root, int space, int level) {
    if (root == NULL) return;
    space += level;
    printTreeRec(root->right, space, level);
    printf("\n");
    for (int i = level; i < space; i++)
        printf(" ");
    printf("%d\n", root->value);
    printTreeRec(root->left, space, level);
}

int countNodes(btree *p){
    if (p == NULL){
        return 0;
    }
    return 1+countNodes(p->left)+countNodes(p->right);
}

// Удаление вершины с заданным значением key
int Delete_edit(int key, btree **node) {
  btree *t, *up;
  if(*node == NULL) return 0;
  
  if((*node)->value == key) {
    if(((*node)->left == NULL) && ((*node)->right == NULL)) { 
      free(*node);
      *node = NULL; 
      printf("Delete List\n");
      return 1;
    }
    if((*node)->left == NULL) { 
      t = *node;  
      *node = (*node)->right; 
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
    int flag = 0;
    if (countNodes((*node)->left) >= countNodes((*node)->right)){ //СМОТРИМ В КАКОЙ СТОРОНЕ УЗЛОВ БОЛЬШЕ 
        t = (*node)->left;
    } else {
      flag = 1;
      t = (*node)->right;
    }

    while (t->right != NULL) {
      up = t;
      t = t-> right; 
    }
    (*node)->value = t->value;
    if (up != (*node)) {    
      if(t->left != NULL) up->right = t->left;
      else up->right = NULL;
    }
    else {if (flag == 1) (*node)->right = t->left; 
          else (*node)->left = t->left;
      }
    free(t);
    printf("Delete Two\n");
    return 1;
  }
  if((*node)->value < key)
    return Delete_edit(key, &(*node)->right);
  return Delete_edit(key, &(*node)->left);
}

void export_tree_to_json_rec(FILE *file, btree *node) {
    if (node == NULL) {
        fprintf(file, "null");
        return;
    }
    
    fprintf(file, "{");
    fprintf(file, "\"value\": %d, ", node->value);
    
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

int main() {
  int d[] = {50,55,53,60,40,52,59,58,57,0};
  int i = 0;
  btree *root = NULL;
  
  while(1) {
    if(d[i] == 0) break;
    Ins_Btree_edit(d[i], &root); i++; // заполняем дерево массивом чисел
  }
  export_tree_to_json(root, "export/export1.json");

  printTreeRec(root, 0, 5); printf("\n"); // выводим дерево

  Delete_edit(55, &root); // удаляем узел с значением 37
  //Ins_Btree_edit(67, &root); // добавляем узел с значением 67

  export_tree_to_json(root, "export/export2.json");
  printf("After Delete and Past:\n");
  printTreeRec(root, 0, 5); printf("\n"); // выводим дерево

  return 0;
}
