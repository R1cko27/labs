#ifndef CURRICULUM_H
#define CURRICULUM_H

#include <string>
#include <map>
#include <vector>
#include "DegreeLevel.h"
#include "Discipline.h"

class Curriculum {
    public:
        enum class ResponsiblePerson {
            TOMILOV_IN, BAKAEV_MA, PAVLOV_AV,
            GRIF_MG, IVANOV_AV, GUZHOV_VI,
            TRUSHIN_VA, ROMANOV_EL, HUDYAKOV_DS,
            NOT_ASSIGNED
        };

        using DegreeLevel = ::DegreeLevel;

        enum class State {
            EDITING,
            ACTIVE
        };
    private:
        std::string code;
        std::string title;
        ResponsiblePerson responsiblePerson;
        int targetCredits;
        DegreeLevel level;
        int semesterCount;
        std::vector<std::map<std::string, Discipline>> semesters;
        State currentState;

        void validateState() const;
        void validateSemester(int semester) const;
        void validateInstance(std::string errors[], int& errorCount) const;
        
    public:
        // Конструкторы
        Curriculum();
        Curriculum(const std::string& code, const std::string& title,
                   ResponsiblePerson responsiblePerson, int targetCredits, DegreeLevel level,
                   int semesterCount = 1);
        
        Curriculum(const Curriculum& other);
        ~Curriculum();
        Curriculum& operator=(const Curriculum& other);

        // Геттеры и сеттеры с исключениями
        std::string getCode() const;
        void setCode(const std::string& newCode);

        std::string getTitle() const;
        void setTitle(const std::string& newTitle);

        std::string getResponsiblePerson() const;
        void setResponsiblePerson(ResponsiblePerson newPerson);

        int getTargetCredits() const;
        void setTargetCredits(int newTarget);

        DegreeLevel getDegreeLevel() const;
        std::string getDegreeLevelString() const;
        void setDegreeLevel(DegreeLevel newLevel);

        int getSemesterCount() const;
        void setSemesterCount(int newCount);

        // Методы с исключениями
        void addDiscipline(int semester, const Discipline& discipline);
        void removeDiscipline(int semester, const std::string& disciplineName);
        
        // Безопасные методы
        bool safeAddDiscipline(int semester, const Discipline& discipline, std::string& errorMessage);
        bool safeRemoveDiscipline(int semester, const std::string& disciplineName, std::string& errorMessage);
        bool safeSetSemesterCount(int newCount, std::string& errorMessage);
        bool safeActivate(std::string& errorMessage);

        int getDisciplineCountInSemester(int semester) const;
        int getTotalDisciplineCreditsInSemester(int semester) const;
        int getDisciplineCount() const;
        int getTotalDisciplineCredits() const;

        State getState() const;
        std::string getStateString() const;

        bool activate();
        void print() const;
};

#endif