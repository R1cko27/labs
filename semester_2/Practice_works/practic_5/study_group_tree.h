#ifndef STUDY_GROUP_TREE_H
#define STUDY_GROUP_TREE_H

typedef enum { B, M, DEFAULT_LVL } EducationLevel;
typedef enum { IS, PI, AI, PR, VT, DEFAULT_DIR } StudyDirection;

class StudyGroup {
    private:
        char group_name[10];
        StudyDirection direction;
        int enrollment_year;
        EducationLevel level;

    public:
        StudyGroup(const char* group_name, StudyDirection direction, int enrollment_year, EducationLevel level);

        void print() const;
};

#endif