// test_program.c
// Пример файла для тестирования анализатора макросов

#include <stdio.h>
#include <stdlib.h>

// Простые макросы
#define PI 3.14159
#define MAX_SIZE 100
#define MIN_VALUE 0

// Макросы с параметрами
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Макросы для отладки
#define DEBUG 1
#define LOG(msg) printf("[LOG] %s\n", msg)

// Макрос с многострочным определением
#define SWAP(a, b) do { \
    typeof(a) temp = (a); \
    (a) = (b); \
    (b) = temp; \
} while(0)

// Определяем макрос для тестирования #undef
#define TEST_MACRO 12345
#define TEMP_VALUE 999
#define OLD_NAME "old_value"

int main() {
    int x = 10;
    int y = 20;
    
    // Используем макросы
    printf("PI = %f\n", PI);
    printf("MAX_SIZE = %d\n", MAX_SIZE);
    printf("SQUARE(5) = %d\n", SQUARE(5));
    printf("MAX(10, 20) = %d\n", MAX(10, 20));
    
    #ifdef DEBUG
        LOG("Debug mode enabled");
    #endif
    
    // Тестируем SWAP
    printf("Before swap: x=%d, y=%d\n", x, y);
    SWAP(x, y);
    printf("After swap: x=%d, y=%d\n", x, y);
    
    // Проверяем TEST_MACRO
    printf("TEST_MACRO = %d\n", TEST_MACRO);
    
    // Отменяем некоторые макросы
    #undef TEST_MACRO
    #undef TEMP_VALUE
    #undef OLD_NAME
    
    // Попытка использовать отмененный макрос (закомментировано, так как вызовет ошибку)
    // printf("TEST_MACRO = %d\n", TEST_MACRO); // Ошибка: макрос не определен
    
    // Определяем новый макрос с тем же именем
    #define TEST_MACRO 54321
    printf("New TEST_MACRO = %d\n", TEST_MACRO);
    
    // Определяем дополнительные макросы после #undef
    #define NEW_MACRO 777
    #define ANOTHER_MACRO "another"
    
    // Еще один #undef для тестирования удаления из дерева
    #undef MAX_SIZE
    
    return 0;
}

// Макросы вне функции main
#define GLOBAL_MACRO 1000
#define STRING_MACRO "global string"

// Макрос с нестандартным именем (должен быть пропущен)
#define INVALID 456  // Невалидный идентификатор - начинается с цифры

// Макрос со сложной заменой
#define COMPLEX_MACRO(x, y) \
    do { \
        int temp = (x) + (y); \
        printf("Sum: %d\n", temp); \
    } while(0)

// Еще один макрос для проверки алфавитного порядка
#define ALPHA_MACRO 1
#define BETA_MACRO 2
#define GAMMA_MACRO 3
#define ZETA_MACRO 4