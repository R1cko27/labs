#ifndef CURRICULUM_H
#define CURRICULUM_H

#include <string>
#include <map>
#include <vector>
#include "DegreeLevel.h"
#include "Discipline.h"

class Curriculum {
    public:
        // Статические константы (допустимые пределы)
        static constexpr int MIN_TARGET_CREDITS = 240;  ///< Минимальные целевые ЗЕ (единиц)
        static constexpr int MAX_TARGET_CREDITS = 250;  ///< Максимальные целевые ЗЕ (единиц)
        static constexpr int MIN_SEMESTER_COUNT = 1;    ///< Минимальное количество семестров (шт)
        static constexpr int MAX_SEMESTER_COUNT = 10;   ///< Максимальное количество семестров (шт)
        static constexpr int MIN_TITLE_LENGTH = 5;      ///< Минимальная длина названия (символов)
        static constexpr int MAX_TITLE_LENGTH = 100;    ///< Максимальная длина названия (символов)
        static constexpr int MIN_CODE_AREA = 1;         ///< Минимальная область науки в коде
        static constexpr int MAX_CODE_AREA = 40;        ///< Максимальная область науки в коде
        static constexpr int MIN_CODE_GROUP = 1;        ///< Минимальная группа в коде
        static constexpr int MAX_CODE_GROUP = 9;        ///< Максимальная группа в коде
        static constexpr int MIN_CODE_SPECIALTY = 1;    ///< Минимальная специальность в коде
        static constexpr int MAX_CODE_SPECIALTY = 9;    ///< Максимальная специальность в коде

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
        std::string code;                                   ///< Шифр учебной программы (строка)
        std::string title;                                  ///< Название учебной программы (символы)
        ResponsiblePerson responsiblePerson;                ///< ФИО ответственного лица (перечисление)
        int targetCredits;                                  ///< Целевое количество зачётных единиц (ЗЕ)
        DegreeLevel level;                                  ///< Ступень образования (перечисление)
        int semesterCount;                                  ///< Количество семестров (шт)
        std::vector<std::map<std::string, Discipline>> semesters;  ///< Контейнер дисциплин по семестрам
        State currentState;                                 ///< Текущее состояние плана (перечисление)

        void validateState() const;
        void validateSemester(int semester) const;
        void validateInstance(std::string errors[], int& errorCount) const;
        
    public:
        // Конструкторы
        Curriculum();
        Curriculum(const std::string& code, const std::string& title,
                   ResponsiblePerson responsiblePerson, int targetCredits, DegreeLevel level,
                   int semesterCount = 1);
        
        Curriculum(const Curriculum& other); // Конструктор копирования
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

        int getDisciplineCountInSemester(int semester) const;
        int getTotalDisciplineCreditsInSemester(int semester) const;
        int getDisciplineCount() const;
        int getTotalDisciplineCredits() const;

        State getState() const;
        std::string getStateString() const;

        bool activate();
        void print() const;
        void printSemesterDetails(int semester) const;
};

#endif