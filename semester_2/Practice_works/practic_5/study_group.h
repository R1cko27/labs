#ifndef STUDY_GROUP_H
#define STUDY_GROUP_H

#include <iosfwd>
#include <iostream>
#include <string>

// Уровень образования.
enum class EducationLevel {
    Bachelor, Master
};

// Направление обучения.
enum class StudyDirection {
    IS, PI, AI, PR, VT
};

class StudentGroup {
private:
    std::string groupName;
    StudyDirection direction;
    int enrollmentYear;
    EducationLevel level;

    void init(const std::string& name, StudyDirection dir, int year, EducationLevel lvl);

public:
    StudentGroup(const std::string& name = "AP-000",
                StudyDirection dir = StudyDirection::PI,
                int year = 2020,
                EducationLevel lvl = EducationLevel::Bachelor);

    StudentGroup(const StudentGroup& other);

    void print() const;
    void rename(const std::string& newGroupName);
};

StudentGroup* createGroup(const std::string& name, StudyDirection dir, int year, EducationLevel lvl, std::ostream& out = std::cout);

#endif
<<<<<<< HEAD

=======
>>>>>>> a34c5f65c5ff711a1b1712897025384e4ca02c5a
