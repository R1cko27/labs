#include "study_group.h"

#include <stdio.h>
#include <string.h>


StudyGroup:StudyGroup(const char* group_name, StudyDirection direction, int enrollment_year, EducationLevel level)
    : direction(direction), enrollment_year(enrollment_year), level(level) {
    strncpy(this->group_name, group_name, sizeof(this->group_name) - 1);
    this->group_name[sizeof(this->group_name) - 1] = '\0';
    printf("Constructor called with group_name = %s, direction = %d, enrollment_year = %d, level = %d\n",
           this->group_name, this->direction, this->enrollment_year, this->level);
}

int main(){

}