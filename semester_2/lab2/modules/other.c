#include "list_structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

