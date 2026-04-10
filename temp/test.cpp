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

const char* StudyGroup::get_group_name() const {
    return group_name;
}

StudyDirection StudyGroup::get_direction() const {
    return direction;
}

int StudyGroup::get_enrollment_year() const {
    return enrollment_year;
}

EducationLevel StudyGroup::get_level() const {
    return level;
}

int is_study_group_less(const StudyGroup* group1, const StudyGroup* group2) {
    if (group1 == nullptr || group2 == nullptr) return 0;
    if (group1->get_level() != group2->get_level()) return group1->get_level() < group2->get_level();
    if (group1->get_direction() != group2->get_direction()) return group1->get_direction() < group2->get_direction();
    if (group1->get_enrollment_year() != group2->get_enrollment_year()) return group1->get_enrollment_year() < group2->get_enrollment_year();
    return strcmp(group1->get_group_name(), group2->get_group_name()) < 0;
}

int are_study_groups_equal(const StudyGroup* group1, const StudyGroup* group2) {
    if (group1 == nullptr || group2 == nullptr) return 0;
    return group1->get_level() == group2->get_level()
        && group1->get_direction() == group2->get_direction()
        && group1->get_enrollment_year() == group2->get_enrollment_year()
        && strcmp(group1->get_group_name(), group2->get_group_name()) == 0;
}

void StudyGroup::print() const {
    printf("Group Name: %s, Direction: %d, Enrollment Year: %d, Level: %d\n",
           group_name, direction, enrollment_year, level);
}

btree::btree(const StudyGroup& group) : data(group), left(nullptr), right(nullptr) {
}

btree::~btree() {
    delete left;
    delete right;
}

int btree::count_nodes(const btree* node) {
    if (node == nullptr) {
        return 0;
    }

    return 1 + count_nodes(node->left) + count_nodes(node->right);
}

void btree::insert_group(const StudyGroup* group, btree** q) {
    if (*q == nullptr) {
        *q = new btree(*group);
        return;
    }

    if (is_study_group_less(&(*q)->data, group)) {
        insert_group(group, &(*q)->left);
    } else if (is_study_group_less(group, &(*q)->data)) {
        insert_group(group, &(*q)->right);
    }
}

int btree::delete_group(const StudyGroup* group, btree** node) {
    btree* t;
    btree* up;

    if (*node == nullptr) {
        return 0;
    }

    if (are_study_groups_equal(&(*node)->data, group)) {
        if ((*node)->left == nullptr && (*node)->right == nullptr) {
            delete *node;
            *node = nullptr;
            printf("Delete List\n");
            return 1;
        }

        if ((*node)->left == nullptr) {
            t = *node;
            *node = (*node)->right;
            t->right = nullptr;
            delete t;
            printf("Delete Left = 0\n");
            return 1;
        }

        if ((*node)->right == nullptr) {
            t = *node;
            *node = (*node)->left;
            t->left = nullptr;
            delete t;
            printf("Delete Right = 0\n");
            return 1;
        }

        up = *node;
        int flag = 0;

        if (count_nodes((*node)->left) >= count_nodes((*node)->right)) {
            t = (*node)->left;
        } else {
            flag = 1;
            t = (*node)->right;
        }

        while (t->right != nullptr) {
            up = t;
            t = t->right;
        }

        (*node)->data = t->data;

        if (up != *node) {
            if (t->left != nullptr) {
                up->right = t->left;
            } else {
                up->right = nullptr;
            }
        } else {
            if (flag == 1) {
                (*node)->right = t->left;
            } else {
                (*node)->left = t->left;
            }
        }

        t->left = nullptr;
        t->right = nullptr;
        delete t;
        printf("Delete Two\n");
        return 1;
    }

    if (is_study_group_less(group, &(*node)->data)) {
        return delete_group(group, &(*node)->right);
    }

    return delete_group(group, &(*node)->left);
}

void btree::print_inorder() const {
    if (left != nullptr) {
        left->print_inorder();
    }

    data.print();

    if (right != nullptr) {
        right->print_inorder();
    }
}

int main() { 
    StudyGroup group1("AP-526", IS, 2025, B);
    StudyGroup group2("AP-325", PI, 2024, B);
    StudyGroup group3("AP-626", AI, 2023, M);
    StudyGroup group4("AP-426", PR, 2024, B);
    StudyGroup group5("AP-726", VT, 2025, M);


    btree* groups = nullptr;
    btree::insert_group(&group1, &groups);
    btree::insert_group(&group2, &groups);
    btree::insert_group(&group3, &groups);
    btree::insert_group(&group4, &groups);
    btree::insert_group(&group5, &groups);

    btree::delete_group(&group2, &groups);
    btree::delete_group(&group4, &groups);
    if (groups != nullptr) {
        groups->print_inorder();
    }

    delete groups;

    return 0;
}   