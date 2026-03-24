#include "set_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Функция для создания нового узла с копией данных
static SetNode* create_node(const StudyGroup* group) {
    // Выделяем память под узел
    SetNode* new_node = (SetNode*)malloc(sizeof(SetNode));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти для узла\n");
        return NULL;
    }
    
    // Выделяем память под данные и копируем их
    new_node->data = (StudyGroup*)malloc(sizeof(StudyGroup));
    if (new_node->data == NULL) {
        printf("Ошибка выделения памяти для данных\n");
        free(new_node);
        return NULL;
    }
    
    // Копируем данные
    *(new_node->data) = *group;
    new_node->next = NULL;
    
    return new_node;
}

// Функция для проверки эквивалентности групп
static int groups_are_equal(const StudyGroup* g1, const StudyGroup* g2) {
    return strcmp(g1->group_name, g2->group_name) == 0;
}

// Функция для вставки с сохранением порядка
static ErrorCode insert_ordered(SetNode** head, const StudyGroup* group) {
    SetNode* new_node = create_node(group);
    if (new_node == NULL) {
        return ERR_MEMORY;
    }
    
    // Если список пуст или новый элемент должен быть в начале
    if (*head == NULL || is_study_group_less(group, (*head)->data)) {
        new_node->next = *head;
        *head = new_node;
        return SUCCESS;
    }
    
    // Поиск места для вставки
    SetNode* current = *head;
    while (current->next != NULL && is_study_group_less(current->next->data, group)) {
        current = current->next;
    }
    
    // Проверка на дубликат
    if (groups_are_equal(current->data, group)) {
        printf("Ошибка: группа %s уже существует в множестве\n", group->group_name);
        free(new_node->data);
        free(new_node);
        return ERR_DUPLICATE;
    }
    
    if (current->next != NULL && groups_are_equal(current->next->data, group)) {
        printf("Ошибка: группа %s уже существует в множестве\n", group->group_name);
        free(new_node->data);
        free(new_node);
        return ERR_DUPLICATE;
    }
    
    // Вставка элемента
    new_node->next = current->next;
    current->next = new_node;
    
    return SUCCESS;
}

// 1) Добавление элемента в множество (без повторов)
ErrorCode set_insert(SetNode** head, const StudyGroup* group) {
    if (head == NULL || group == NULL) {
        return ERR_GROUP_NAME;
    }
    ErrorCode err = validate_study_group(group);
    if (err != SUCCESS) {
        return err;
    }
    return insert_ordered(head, group);
}

// 2) Удаление заданного значения из списка
ErrorCode set_remove(SetNode** head, const char* group_name) {
    if (head == NULL || group_name == NULL) {
        return ERR_GROUP_NAME;
    }
    
    if (*head == NULL) {
        printf("Множество пусто, удаление невозможно\n");
        return ERR_GROUP_NAME;
    }
    
    SetNode* current = *head;
    SetNode* prev = NULL;
    
    // Поиск элемента для удаления
    while (current != NULL) {
        if (strcmp(current->data->group_name, group_name) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            
            printf("Удалена группа: %s\n", group_name);
            free(current->data);
            free(current);
            return SUCCESS;
        }
        
        prev = current;
        current = current->next;
    }
    
    printf("Группа %s не найдена в множестве\n", group_name);
    return ERR_GROUP_NAME;
}

// 3) Проверка, есть ли заданное значение в списке
int set_contains(const SetNode* head, const char* group_name) {
    const SetNode* current = head;
    
    while (current != NULL) {
        if (strcmp(current->data->group_name, group_name) == 0) {
            return 1;
        }
        current = current->next;
    }
    
    return 0;
}

// 4) Объединение множеств
SetNode* set_union(const SetNode* set1, const SetNode* set2) {
    SetNode* result = NULL;
    
    // Копируем все элементы из первого множества
    const SetNode* current = set1;
    while (current != NULL) {
        set_insert(&result, current->data);
        current = current->next;
    }
    
    // Добавляем элементы из второго множества
    current = set2;
    while (current != NULL) {
        set_insert(&result, current->data);
        current = current->next;
    }
    
    return result;
}

// 5) Пересечение множеств
SetNode* set_intersection(const SetNode* set1, const SetNode* set2) {
    SetNode* result = NULL;
    
    const SetNode* current = set1;
    while (current != NULL) {
        if (set_contains(set2, current->data->group_name)) {
            set_insert(&result, current->data);
        }
        current = current->next;
    }
    
    return result;
}

// Печать множества
void print_set(const SetNode* head) {
    if (head == NULL) {
        printf("Множество пусто\n");
        return;
    }
    
    const SetNode* current = head;
    int count = 1;
    
    while (current != NULL) {
        printf("Элемент %d:\n", count++);
        print_study_group(current->data);
        printf("\n");
        current = current->next;
    }
}

// Удаление всего множества
void delete_set(SetNode* head) {
    SetNode* current = head;
    int count = 0;
    
    while (current != NULL) {
        SetNode* temp = current;
        current = current->next;
        
        free(temp->data);
        free(temp);
        count++;
    }
    
    printf("Удалено %d элементов множества\n", count);
}