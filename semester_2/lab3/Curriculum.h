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

        // Перечисление для состояния
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

    public:
        Curriculum(const std::string& code, const std::string& title, const std::string& responsiblePerson, int targetCredits, DegreeLevel level);

        std::string getCode() const;
        void setCode(const std::string& newCode);

        std::string getTitle() const;
        void setTitle(const std::string& newTitle);
        
        std::string getResponsiblePerson() const;
        void setResponsiblePerson(const std::string& newPerson);

        int getTargetCredits() const;
        void setTargetCredits(int newTarget);

        DegreeLevel getDegreeLevel() const;
        void setDegreeLevel(DegreeLevel newLevel);
        
        std::string getDegreeLevelString() const;

        // Количество дисциплин и суммарное количество ЗЕ
        void setDisciplinesInfo(int count, int totalCredits);

        // Получение информации о дисциплинах
        int getDisciplineCount() const;
        int getTotalDisciplineCredits() const;

        // Состояние
        State getState() const;
        std::string getStateString() const;

        // Ввести план в действие (с проверкой условий)
        bool activate();
    };

#endif // CURRICULUM_H