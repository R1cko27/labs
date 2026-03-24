#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include "study_group.h"
#include "list_structures.h"

#define TASK1 1 
#define TASK2 2
#define TASK3 3

#define CURRENT_TASK 2

#if CURRENT_TASK == TASK1
void print_bytes(const char* name, void* data, size_t size) {
    printf("%s (", name);
    unsigned char* bytes = (unsigned char*)data;
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", bytes[i]);
    }
    printf(")\n");
}

int main() {
    // Задание 1.1: Проверка функций _open и close с обработкой ошибок
    char pathname1[] = "test_file.bin";
    int fd = _open(pathname1, _O_RDWR | _O_CREAT | _O_TRUNC, _S_IREAD | _S_IWRITE);
    if (fd == -1) {
        printf("Ошибка при открытии файла: %s (код ошибки: %d)\n", strerror(errno), errno);
        return -1;
    }
    _close(fd);

    // Задание 1.2: Проверка на дубликат
    fd = _open(pathname1, _O_RDWR | _O_CREAT | _O_EXCL | _O_BINARY, _S_IREAD | _S_IWRITE);
    if (fd == -1) printf("ОШИБКА: файл уже существует. Ошибка: %s (код: %d)\n", strerror(errno), errno);
    else {
        printf("Файл создан заново\n");
        _close(fd);
    }
    
    // Задание 1.3: Открытие существующего файла для дозаписи
    fd = _open(pathname1, _O_RDWR | _O_CREAT | _O_APPEND, _S_IREAD | _S_IWRITE);
    if (fd == -1) {
        printf("Ошибка при открытии файла: %s (код ошибки: %d)\n", strerror(errno), errno);
        return -1;
    }
    _close(fd);

    // Задание 2.1: Создание файла и запись различных типов данных
    char pathname2[] = "data_type.bin";

    fd = _open(pathname2, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _S_IREAD | _S_IWRITE);
    if (fd == -1) return -1;

    char char_var = 'A';
    _write(fd, &char_var, sizeof(char));
    char char_array[] = {'H', 'e', 'l', 'l', 'o'};
    _write(fd, char_array, sizeof(char_array));
    short short_var = -12345;
    _write(fd, &short_var, sizeof(short));
    int int_var = 123456789;
    _write(fd, &int_var, sizeof(int));
    int int_array[] = {10, 20, 30, 40, 50};
    _write(fd, int_array, sizeof(int_array));
    float float_var = 123.456f;
    _write(fd, &float_var, sizeof(float));
    double double_var = 123456.789012;
    _write(fd, &double_var, sizeof(double));

    _close(fd);
    
    // Задание 3.1: Вывод файла
    fd = _open(pathname2, _O_RDONLY | _O_BINARY);
    if (fd == -1) return -1;

    char char_var3;
    int bytes_read = _read(fd, &char_var3, sizeof(char));
    printf("char: '%c' (значение: %d)\n", char_var3, char_var3);
    
    char char_array3[5];
    bytes_read = _read(fd, char_array3, sizeof(char_array3));
    printf("Символьный массив: ");
    for (int i = 0; i < 5; i++) printf("%c\t", char_array3[i]);
    printf("\n");
    
    short short_var3;
    bytes_read = _read(fd, &short_var3, sizeof(short));
    printf("Short: %d\n", short_var3);
    
    int int_var3;
    bytes_read = _read(fd, &int_var3, sizeof(int));
    printf("Int: %d\n", int_var3);
    
    int int_array3[5];
    bytes_read = _read(fd, int_array3, sizeof(int_array3));
    printf("Массив int\n");
    for (int i = 0; i < 5; i++) printf("%d\t", int_array3[i]);
    printf("\n");
    
    float float_var3;
    bytes_read = _read(fd, &float_var3, sizeof(float));
    printf("Float: %f\n", float_var3);
    
    double double_var3;
    bytes_read = _read(fd, &double_var3, sizeof(double));
    printf("Double: %f\n", double_var3);
    
    _close(fd);
    
    // Задание 3.2: Побайтовое представление считанных значений
    fd = _open(pathname2, _O_RDONLY | _O_BINARY);
    if (fd == -1) return -1;

    char char_var_hex;
    _read(fd, &char_var_hex, sizeof(char));
    print_bytes("char 'A'", &char_var_hex, sizeof(char));

    char char_array_hex[5];
    _read(fd, char_array_hex, sizeof(char_array_hex));
    print_bytes("char array 'Hello'", char_array_hex, sizeof(char_array_hex));

    short short_var_hex;
    _read(fd, &short_var_hex, sizeof(short));
    print_bytes("short -12345", &short_var_hex, sizeof(short));

    int int_var_hex;
    _read(fd, &int_var_hex, sizeof(int));
    print_bytes("int 123456789", &int_var_hex, sizeof(int));

    int int_array_hex[5];
    _read(fd, int_array_hex, sizeof(int_array_hex));
    print_bytes("int array [10,20,30,40,50]", int_array_hex, sizeof(int_array_hex));

    float float_var_hex;
    _read(fd, &float_var_hex, sizeof(float));
    print_bytes("float 123.456", &float_var_hex, sizeof(float));

    double double_var_hex;
    _read(fd, &double_var_hex, sizeof(double));
    print_bytes("double 123456.789012", &double_var_hex, sizeof(double));

    _close(fd);
    
    // Задание 4.1: Чтение определенных значений
    fd = _open(pathname2, _O_RDONLY | _O_BINARY);
    if (fd == -1) return -1;

    _lseek(fd, sizeof(char), SEEK_CUR);
    char char_array_lseek[5];
    bytes_read = _read(fd, char_array_lseek, sizeof(char_array_lseek));
    printf("Символьный массив: ");
    for (int i = 0; i < 5; i++) printf("%c\t", char_array_lseek[i]);
    printf("\n");

    _lseek(fd, sizeof(short), SEEK_CUR);

    int int_var_lseek;
    bytes_read = _read(fd, &int_var_lseek, sizeof(int));
    printf("int: %d\n", int_var_lseek);

    _lseek(fd, sizeof(int) * 5, SEEK_CUR);
    _lseek(fd, sizeof(float), SEEK_CUR);

    double double_var_lseek;
    bytes_read = _read(fd, &double_var_lseek, sizeof(double));
    printf("double: %f\n", double_var_lseek);

    _close(fd);
    
    // Задание 4.2: Изменение элемента символьного массива и значения float
    fd = _open(pathname2, _O_RDWR | _O_BINARY);
    if (fd == -1) return -1;

    _lseek(fd, sizeof(char), SEEK_SET);

    char char_array_before[6];
    _read(fd, char_array_before, sizeof(char_array_before)-1);
    char_array_before[5] = '\0';
    printf("Символьный массив до изменения: %s\n", char_array_before);  

    _lseek(fd, sizeof(char) + 2, SEEK_SET);

    char new_char = 'X';
    _write(fd, &new_char, sizeof(char));

    _lseek(fd, sizeof(char), SEEK_SET);
    char char_array_after[6];
    _read(fd, char_array_after, sizeof(char_array_after)-1);
    char_array_after[5] = '\0';
    printf("Символьный массив после изменения: %s\n", char_array_after);

    _lseek(fd, sizeof(char) + sizeof(char_array) + sizeof(short) + sizeof(int) + sizeof(int_array), SEEK_SET);

    float float_before;
    _read(fd, &float_before, sizeof(float));
    printf("Значение float до изменения: %f\n", float_before);

    _lseek(fd, sizeof(char) + sizeof(char_array) + sizeof(short) + sizeof(int) + sizeof(int_array), SEEK_SET);
    float new_float = 999.999f;
    _write(fd, &new_float, sizeof(float));

    _lseek(fd, sizeof(char) + sizeof(char_array) + sizeof(short) + sizeof(int) + sizeof(int_array), SEEK_SET);
    float float_after;
    _read(fd, &float_after, sizeof(float));
    printf("Значение float после изменения: %f\n", float_after);

    _close(fd);
    
    // Задание 4.3: Переписывание символьного массива в обратном порядке'
    fd = _open(pathname2, _O_RDWR | _O_BINARY);
    if (fd == -1) return -1;
    
    _lseek(fd, sizeof(char), SEEK_SET);
    char char_array_original[5];
    _read(fd, char_array_original, sizeof(char_array_original));

    char char_array_reversed[5];
    for (int i = 0; i < 5; i++) char_array_reversed[i] = char_array_original[4 - i];
    
    _lseek(fd, sizeof(char), SEEK_SET);
    _write(fd, char_array_reversed, sizeof(char_array_reversed));
    _close(fd);

    return 0;
}

#elif CURRENT_TASK == TASK2
int main(){
    // Задание 5.1: Работа со структурой (один экземпляр)
    char pathname3[] = "group_struct.bin";
    StudyGroup group;
    ErrorCode err = init_study_group(&group, "AP-526", PI, 2025, B);
    if (err != 0) return -1;

    int fd = _open(pathname3, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _S_IREAD | _S_IWRITE);
    if (fd == -1) return -1;

    int written_bytes = _write(fd, &group, sizeof(StudyGroup));
    if (written_bytes != sizeof(StudyGroup)) {
        _close(fd);
        return -1;
    }
    _close(fd);

    fd = _open(pathname3, _O_RDONLY | _O_BINARY);
    if (fd == -1) return -1;

    StudyGroup read_group;
    int read_bytes = _read(fd, &read_group, sizeof(StudyGroup));
    if (read_bytes != sizeof(StudyGroup)) {
        _close(fd);
        return -1;
    }
    _close(fd);

    printf("Считанная структура:\n");
    print_study_group(&read_group);
    
    // Задание 5.2: Массив структур, чтение только нечетных элементов
    char pathname4[] = "groups_array.bin";
    StudyGroup groups[5];
    const char* names[] = {"AP-526", "AP-426", "AP-326", "AB-420", "AB-520"};
    StudyDirection dirs[] = {PI, PI, PI, IS, IS};
    int years[] = {2025, 2024, 2023, 2024, 2025};
    EducationLevel levels[] = {B, B, B, B, B};

    for (int i = 0; i < 5; i++) {
        err = init_study_group(&groups[i], names[i], dirs[i], years[i], levels[i]);
        if (err != 0) return -1;
    }

    fd = _open(pathname4, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _S_IREAD | _S_IWRITE);
    if (fd == -1) return -1;

    written_bytes = _write(fd, groups, sizeof(groups)); 
    if (written_bytes != sizeof(groups)) {
        _close(fd);
        return -1;
    }
    _close(fd);

    fd = _open(pathname4, _O_RDONLY | _O_BINARY);
    if (fd == -1) return -1;

    StudyGroup odd_group;
    for (int i = 0; i < 5; i++) {
        if (i%2 != 0){
            read_bytes = _read(fd, &odd_group, sizeof(StudyGroup));
            print_study_group(&odd_group);
        }
        _lseek(fd, sizeof(StudyGroup), SEEK_CUR);
    }
    _close(fd);
    
    // Задание 5.3*: Создание файла с очередью структур и чтение всех элементов
    char pathname5[] = "groups_queue.bin";

    fd = _open(pathname5, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _S_IREAD | _S_IWRITE);
    if (fd == -1) return -1;

    QueueNode* tail = NULL;
    StudyGroup q_group1, q_group2, q_group3, q_group4, q_group5;

    init_study_group(&q_group1, "AP-526", PI, 2025, B);
    init_study_group(&q_group2, "AP-426", PI, 2024, B);
    init_study_group(&q_group3, "AP-326", PI, 2023, B);
    init_study_group(&q_group4, "AP-226", PI, 2022, B);
    init_study_group(&q_group5, "AB-420", PI, 2024, B);

    tail = enqueue(tail, &q_group1);
    tail = enqueue(tail, &q_group2);
    tail = enqueue(tail, &q_group3);
    tail = enqueue(tail, &q_group4);
    tail = enqueue(tail, &q_group5);

    QueueNode* current = NULL;
    QueueNode* head = NULL;

    if (tail != NULL) {
        current = tail->next;
        head = current;
        do {
            int written = _write(fd, &current->data, sizeof(StudyGroup));
            if (written != sizeof(StudyGroup)) {
                _close(fd);
                tail = delete_queue(tail);
                return -1;
            }
            current = current->next;
        } while (current != head);
    }

    _close(fd);
    tail = delete_queue(tail);

    // Чтение всех структур из файла и создание новой очереди
    fd = _open(pathname5, _O_RDONLY | _O_BINARY);
    if (fd == -1) return -1;

    int file_size = _lseek(fd, 0, SEEK_END);
    int num_structs = file_size / sizeof(StudyGroup);

    _lseek(fd, 0, SEEK_SET);

    StudyGroup* read_buffer = (StudyGroup*)malloc(num_structs * sizeof(StudyGroup));
    if (read_buffer == NULL) {
        _close(fd);
        return -1;
    }

    for (int i = 0; i < num_structs; i++) {
        _read(fd, &read_buffer[i], sizeof(StudyGroup));
    }

    QueueNode* new_tail = NULL;
    for (int i = 0; i < num_structs; i++) {
        new_tail = enqueue(new_tail, &read_buffer[i]);
    }

    free(read_buffer);
    print_queue(new_tail);
    new_tail = delete_queue(new_tail);

    return 0;
}

#elif CURRENT_TASK == TASK3

const char* direction_to_string_serialize(StudyDirection dir) {
    switch (dir) {
        case IS: return "IS";
        case PI: return "PI";
        case AI: return "AI";
        case PR: return "PR";
        case VT: return "VT";
        default: return "UNKNOWN";
    }
}

StudyDirection string_to_direction(const char* str) {
    if (strcmp(str, "IS") == 0) return IS;
    if (strcmp(str, "PI") == 0) return PI;
    if (strcmp(str, "AI") == 0) return AI;
    if (strcmp(str, "PR") == 0) return PR;
    if (strcmp(str, "VT") == 0) return VT;
    return IS;
}

const char* level_to_string_serialize(EducationLevel level) {
    return (level == B) ? "B" : "M";
}

EducationLevel string_to_level(const char* str) {
    return (strcmp(str, "B") == 0) ? B : M;
}

int main() {
    // Задание 6.1: Формирование текстового файла
    StudyGroup groups[10];
    const char* names[] = {
        "AP-226", "AP-326", "AP-426", "AP-526", "AB-220",
        "AB-320", "AB-420", "AB-520", "ABT-241", "ABT-341"
    };

    StudyDirection dirs[] = {IS, PI, IS, VT, AI, PR, IS, PI, IS, VT};
    int years[] = {2022, 2023, 2024, 2025, 2022, 2023, 2024, 2025, 2022, 2023};
    EducationLevel levels[] = {B, B, B, M, B, B, B, B, B, B};

    for (int i = 0; i < 10; i++) {
        ErrorCode err = init_study_group(&groups[i], names[i], dirs[i], years[i], levels[i]);
        if (err != SUCCESS) {
            printf("Ошибка инициализации группы %d: %d\n", i, err);
            return -1;
        }
    }

    char text_filename[] = "groups.txt";
    FILE* file = fopen(text_filename, "w");
    if (file == NULL) return -1;

    for (int i = 0; i < 10; i++) {
        fprintf(file, "%s;%s;%d;%s\n", groups[i].group_name, direction_to_string_serialize(groups[i].direction), groups[i].enrollment_year, level_to_string_serialize(groups[i].level));
    }

    fclose(file);
    
    // Задание 6.2: Чтение текстового файла
    file = fopen(text_filename, "r");
    if (file == NULL) return -1;

    StudyGroup read_groups[10];
    char line[256];
    int read_count = 0;

    while (fgets(line, sizeof(line), file) != NULL && read_count < 10) {
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

        ErrorCode err = init_study_group(&read_groups[read_count], group_name, dir, year, level);
        if (err != SUCCESS) {
            printf("Ошибка при создании структуры из строки %d, используем значения по умолчанию\n", read_count);
            init_study_group(&read_groups[read_count], "DEFAULT", IS, 2023, B);
        }
        
        read_count++;
    }
    fclose(file);

    printf("\nСодержимое прочитанного массива:\n");
    for (int i = 0; i < read_count; i++) {
        print_study_group(&read_groups[i]);
    }
        return 0;
    }
#else
#endif