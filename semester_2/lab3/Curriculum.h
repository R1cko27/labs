#ifndef CURRICULUM_H
#define CURRICULUM_H

#include <string>

class Curriculum {
    public:
        enum class ResponsiblePerson {
            TOMILOV_IN, BAKAEV_MA, PAVLOV_AV,
            GRIF_MG, IVANOV_AV, GUZHOV_VI,
            TRUSHIN_VA, ROMANOV_EL, HUDYAKOV_DS,
            NOT_ASSIGNED
        };
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
        std::string code;                       // шифр
        std::string title;                      // название
        ResponsiblePerson responsiblePerson;    // ФИО ответственного
        int targetCredits;                      // целевое количество зачётных единиц
        DegreeLevel level;                      // ступень высшего образования
        int disciplineCount;                    // количество дисциплин
        int totalDisciplineCredits;             // суммарное количество зачётных единиц за дисциплины
        State currentState;                     // состояние

        void validateState() const;
        void validateInstance(std::string errors[], int& errorCount) const;
<<<<<<< HEAD
    public:
        // Конструкторы
        Curriculum();                                           // конструктор по умолчанию
        Curriculum(const std::string& code, const std::string& title,
                   ResponsiblePerson responsiblePerson, int targetCredits, DegreeLevel level);
        
        // Конструктор копирования
        Curriculum(const Curriculum& other);
        // Деструктор
        ~Curriculum();
        // Оператор присваивания копированием
        Curriculum& operator=(const Curriculum& other);
=======

    public:
        Curriculum();
        Curriculum(const std::string& code, const std::string& title,
                   const std::string& responsiblePerson, int targetCredits, DegreeLevel level);
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885

        // Геттеры и сеттеры
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

        void setDisciplinesInfo(int count, int totalCredits);
        int getDisciplineCount() const;
        int getTotalDisciplineCredits() const;

        State getState() const;
        std::string getStateString() const;

        bool activate();
        
        void print() const;
};

#endif