#include <stdio.h>
#include <string.h>

typedef enum { B, M, DEFAULT_LVL } EducationLevel;
typedef enum { IS, PI, AI, PR, VT, DEFAULT_DIR } StudyDirection;

class test {
    private:
        char group_name[10];    
        StudyDirection direction;
        int enrollment_year;
        EducationLevel level;
    public:
        test (int x) : enrollment_year(x), group_name("Default"), direction(DEFAULT_DIR), level(DEFAULT_LVL) { // Инициализация enrollment_year через список инициализации
            printf("Constructor called with enrollment_year = %d\n", enrollment_year);
        }
        test (const char* group_name, StudyDirection direction, int enrollment_year, EducationLevel level) 
            : direction(direction), enrollment_year(enrollment_year), level(level) {
            strncpy(this->group_name, group_name, sizeof(this->group_name)-1);
            this->group_name[sizeof(this->group_name)-1] = '\0';
            printf("Constructor called with group_name = %s, direction = %d, enrollment_year = %d, level = %d\n", 
                   this->group_name, this->direction, this->enrollment_year, this->level);
        }
        void print() {
            printf("Group Name: %s, Direction: %d, Enrollment Year: %d, Level: %d\n", 
                   group_name, direction, enrollment_year, level);
        }
};

int main() {
    printf("Hello, World!\n");
    test t(2024);   
    test t_full("AP-526", IS, 2025, B);
    t.print();
    t_full.print();
    return 0;
}   