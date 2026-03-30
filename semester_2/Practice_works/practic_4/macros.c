/**
 * @file macros.c
 * @brief Обработка макросов (#define, #undef) с бинарным деревом
 * 
 * Сборка: gcc macros.c -o macros && ./macros test.c
 * GitHub: https://github.com/R1cko27/labs/tree/main/semester_2/Practice_works/practic_4
*/

#include "macros.h"
#include "modules/export_tree.c"

int countNodes(btree *p){
    if (p == NULL){
        return 0;
    }
    return 1+countNodes(p->left)+countNodes(p->right);
}

void Ins_Btree_edit(char* ident, char* repl, btree **q) {
    if(*q == NULL) {
        *q = malloc(sizeof(btree));
        (*q)->left = (*q)->right = NULL;
        (*q)->ident = ident;
        (*q)->replace = repl;
        return;
    }

    if (strcmp(ident, (*q)->ident) < 0)
        Ins_Btree_edit(ident, repl, &(*q)->left);
    else if (strcmp(ident, (*q)->ident) > 0)
        Ins_Btree_edit(ident, repl, &(*q)->right);
    else{
        free((*q)->replace);
        (*q)->replace = (char*)malloc(strlen(repl) + 1);
        strcpy((*q)->replace, repl);
    }
}

int Delete_edit(char* ident, btree **q) {
    btree *t, *up;
    if(*q == NULL) return 0;

    if (strcmp((*q)->ident, ident) == 0) {
    if (((*q)->left == NULL) && ((*q)->right == NULL)) { 
        free(*q);
        *q = NULL; 
        return 1;
    }
    if ((*q)->left == NULL) { 
        t = *q; 
        *q =(*q)->right; 
        free(t); 
        return 1;
    }
    if ((*q)->right == NULL) { 
        t = *q; 
        *q =(*q)->left; 
        free(t); 
        return 1;
    }
    up = *q;
    int flag = 0;
    if (countNodes((*q)->left) >= countNodes((*q)->right)){ 
        t = (*q)->left;
    } else {
        flag = 1;
        t = (*q)->right;
    }
    while (t->right != NULL) {
        up = t;
        t = t-> right; 
    }
    (*q)->ident = t->ident;
    if (up != (*q)) {    
        if (t->left != NULL) up->right = t->left;
        else up->right = NULL;
    }
    else {
        if (flag == 1) (*q)->right = t->left; 
        else (*q)->left = t->left;
        }
    free(t);
    return 1;
    }
    if (strcmp(ident, (*q)->ident) > 0) 
        return Delete_edit(ident, &(*q)->right);
    return Delete_edit(ident, &(*q)->left);
}

void printTreeInOrder(btree* root) {
    if (root == NULL) return;
    printTreeInOrder(root->left);
    printf("  %s -> %s\n", root->ident, root->replace);
    printTreeInOrder(root->right);
}

void freeTree(btree* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root->ident);
    free(root->replace);
    free(root);
}

void skipspace(char* line, int* pos) {
    while (line[*pos] && isspace(line[*pos])) (*pos)++;
}

int skipchars_ident(char* line, int* pos) {
    int i = 0;
    while (line[*pos] && !isspace(line[*pos])) {
        (*pos)++;
        i ++;
    }
    return i;
}

int skipchars_replace(char* line, int* pos) {
    int i = 0;
    while (line[*pos] != '\0') {
        (*pos)++;
        i ++;
    }
    return i;
}

int main(int argc, char* argv[]){
    char filename[524];
    FILE* file = NULL;
    char line[1024];
    btree* root = NULL;

    if (argc > 1){
        strncpy(filename, argv[1], sizeof(filename)-1);
        filename[sizeof(filename)-1]= '\0';
    } else {printf("No args"); return 0;}

    file = fopen(filename, "r");
    if (!file){
        printf("Error open file");
        return 0;
    }

    while (fgets(line, sizeof(line), file)){
        int len = strlen(line);
        if (len > 0 && line[len-1] == '\n') line[len-1] = '\0';
        int pos = 0;
        skipspace(line, &pos);
        if (line[pos] == '#'){
            pos++;
            skipspace(line, &pos);
            if (strncmp(line + pos, "define", 6) == 0){
                pos += 6;
                skipspace(line, &pos); 

                int identLen = skipchars_ident(line, &pos);
                char* ident = malloc(identLen + 1);
                strncpy(ident, line + pos - identLen, identLen);
                ident[identLen] = '\0';

                skipspace(line, &pos);

                int replaceLen = skipchars_replace(line, &pos);
                char* replace = malloc(replaceLen + 1);
                strncpy(replace, line + pos - replaceLen, replaceLen);
                replace[replaceLen] = '\0';

                Ins_Btree_edit(ident, replace, &root);
            } 
            else if (strncmp(line + pos, "undef", 5) == 0){
                pos += 5;
                skipspace(line, &pos);
                                
                int identLen = skipchars_replace(line, &pos);
                char* ident = malloc(identLen + 1);
                strncpy(ident, line + pos - identLen, identLen);
                ident[identLen] = '\0';

                Delete_edit(ident, &root);
                free(ident);
            }
        }
    }
    printTreeInOrder(root);
    export_tree_to_json(root, "export/export1.json");
    freeTree(root);
}