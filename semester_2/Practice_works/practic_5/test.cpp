#include "study_group_tree.h"

#include <stdio.h>
#include <string.h>

StudyGroup::StudyGroup(const char* group_name, StudyDirection direction, int enrollment_year, EducationLevel level)
    : direction(direction), enrollment_year(enrollment_year), level(level) {
    strncpy(this->group_name, group_name, sizeof(this->group_name) - 1);
    this->group_name[sizeof(this->group_name) - 1] = '\0';
    printf("Constructor called with group_name = %s, direction = %d, enrollment_year = %d, level = %d\n",
           this->group_name, this->direction, this->enrollment_year, this->level);
}

void StudyGroup::print() const {
    const char* dir_str = "";
    switch (direction) {
        case IS: dir_str = "IS"; break;
        case PI: dir_str = "PI"; break;
        case AI: dir_str = "AI"; break;
        case PR: dir_str = "PR"; break;
        case VT: dir_str = "VT"; break;
        default: dir_str = "DEFAULT_DIR"; break;
    }

    const char* level_str = "";
    switch (level) {
        case B: level_str = "B"; break;
        case M: level_str = "M"; break;
        default: level_str = "DEFAULT_LVL"; break;
    }

    printf("StudyGroup: name=%s, direction=%s, enrollment_year=%d, level=%s\n",
           group_name, dir_str, enrollment_year, level_str);
}

int main() { 
    StudyGroup group1("AP-526", IS, 2025, B);
    StudyGroup group2("AP-325", PI, 2024, B);
    StudyGroup group3("AP-626", AI, 2023, M);
    StudyGroup group4("AP-426", PR, 2024, B);
    StudyGroup group5("AP-726", VT, 2025, M);

    group1.print();
    group2.print();
    group3.print();
    group4.print();
    group5.print();

    return 0;
}   