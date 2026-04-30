#ifndef CURRICULUM_H
#define CURRICULUM_H

#include <string>

class Curriculum {
    public:
        enum class DegreeLevel {
            BACHELOR,
            MASTER,
            POSTGRADUATE
        };
        enum class State {
            EDITING,
            ACTIVE
        };
    private:
        std::string code;               // шифр
        std::string title;              // название
        std::string responsiblePerson;  // ФИО ответственного
        int targetCredits;              // целевое количество зачётных единиц
        DegreeLevel level;              // ступень высшего образования
        int disciplineCount;            // количество дисциплин
        int totalDisciplineCredits;     // суммарное количество зачётных единиц за дисциплины
        State currentState;             // состояние

        void validateState() const;
        void validateInstance(std::string errors[], int& errorCount) const;

    public:
        Curriculum();
        Curriculum(const std::string& code, const std::string& title,
                   const std::string& responsiblePerson, int targetCredits, DegreeLevel level);

        std::string getCode() const;
        void setCode(const std::string& newCode);

        std::string getTitle() const;
        void setTitle(const std::string& newTitle);

        std::string getResponsiblePerson() const;
        void setResponsiblePerson(const std::string& newPerson);

        int getTargetCredits() const;
        void setTargetCredits(int newTarget);

        DegreeLevel getDegreeLevel() const;
        std::string getDegreeLevelString() const;
        void setDegreeLevel(DegreeLevel newLevel);

        void setDisciplinesInfo(int count, int totalCredits);
        int getDisciplineCount() const;
        int getTotalDisciplineCredits() const;

        State getState() const;
        std::string getStateString() const;

        bool activate();
};

#endif