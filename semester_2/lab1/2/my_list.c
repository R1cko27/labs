#include "my_list.h"
#include <stdlib.h>
#include <stdio.h>

// Добавление элемента в начало списка (push)
Node* push(Node* head, const StudyGroup* group) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти\n");
        return head;
    }
    
    new_node->data = *group;
    new_node->next = head;
    
    return new_node;
}

// Удаление элемента из начала списка (pop)
Node* pop(Node* head) {
    if (head == NULL) {
        printf("Список пуст, удаление невозможно\n");
        return NULL;
    }
    
    Node* temp = head;
    head = head->next;
    
    printf("Удалён элемент: ");
    print_study_group(&temp->data);
    
    free(temp);
    return head;
}

// Печать всех элементов списка
void print_list(const Node* head) {
    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }
    
    const Node* current = head;
    int count = 1;
    
    while (current != NULL) {
        printf("Элемент %d:\n", count++);
        print_study_group(&current->data);
        printf("\n");
        current = current->next;
    }
}

// Удаление всего списка
void delete_list(Node* head) {
    Node* current = head;
    int count = 0;
    
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
        count++;
    }
    
    printf("Удалено %d элементов списка\n", count);
}