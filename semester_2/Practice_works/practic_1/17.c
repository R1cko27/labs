#include "study_group.h"

int main() {
    ErrorCode err;
    StudyGroup* group_array = NULL;
    int size = 0, capacity = 0;
    StudyGroup g1, g2, g3, g4;
    
    init_study_group(&g1, "AP-524", PI, 2024, B);
    init_study_group(&g2, "IS-501", IS, 2024, B);
    init_study_group(&g3, "VT-515", VT, 2025, M);
    init_study_group(&g4, "PR-503", PR, 2024, M);
    
    add_group_to_array(&group_array, &size, &capacity, &g1);
    add_group_to_array(&group_array, &size, &capacity, &g2);
    add_group_to_array(&group_array, &size, &capacity, &g3);
    add_group_to_array(&group_array, &size, &capacity, &g4);
    
    printf("\n--- Попытка добавить дубликат ---\n");
    err = add_group_to_array(&group_array, &size, &capacity, &g1);
    if (err != SUCCESS) printf("Результат: ошибка %d (дубликат)\n", err);
    
    printf("\n--- Содержимое массива групп ---\n");
    for (int i = 0; i < size; i++) {
        printf("Элемент %d:\n", i + 1);
        print_study_group(&group_array[i]);
        printf("\n");
    }

    printf("--- Освобождение памяти ---\n");
    free_study_group_array(&group_array, &size, &capacity);
    return 0;
}