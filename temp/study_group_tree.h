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

        const char* get_group_name() const;
        StudyDirection get_direction() const;
        int get_enrollment_year() const;
        EducationLevel get_level() const;
        void print() const;
};

int is_study_group_less(const StudyGroup* group1, const StudyGroup* group2);
int are_study_groups_equal(const StudyGroup* group1, const StudyGroup* group2);

class btree {
    private:
        StudyGroup data;
        btree* left;
        btree* right;

    public:
        btree(const StudyGroup& group);
        ~btree();

        static void insert_group(const StudyGroup* group, btree** q);
        static int delete_group(const StudyGroup* group, btree** node);
        void print_inorder() const;

    private:
        static int count_nodes(const btree* node);
};

#endif