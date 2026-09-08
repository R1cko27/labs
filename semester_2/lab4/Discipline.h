#ifndef DISCIPLINE_H
#define DISCIPLINE_H

#include <string>
#include <stdexcept>

enum class AttestationType {
    EXAM,   ///< Экзамен
    CREDIT  ///< Зачёт
};

inline std::string attestationTypeToString(AttestationType type) {
    switch (type) {
        case AttestationType::EXAM: return "Экзамен";
        case AttestationType::CREDIT: return "Зачёт";
        default: return "Неизвестно";
    }
}

class Discipline {
public:
    // Статические константы
    static constexpr int MIN_CREDITS = 1;       ///< Минимальное количество ЗЕ (единиц)
    static constexpr int MAX_CREDITS = 14;      ///< Максимальное количество ЗЕ (единиц)
    static constexpr int HOURS_PER_CREDIT = 32; ///< Часов на одну зачётную единицу (ч/ЗЕ)

    Discipline(const std::string& name, int credits, 
               int lectures, int laboratories, int practices, int individual,
               AttestationType attestation)
            :  name(name), credits(credits), 
            lectures(lectures), laboratories(laboratories), 
            practices(practices), individual(individual),
            attestation(attestation) {
        
        if (name.empty()) {
            throw std::invalid_argument("Название дисциплины не может быть пустым.");
        }
        if (credits < MIN_CREDITS || credits > MAX_CREDITS) {
            throw std::invalid_argument("Количество зачётных единиц должно быть в пределах от " + 
                                       std::to_string(MIN_CREDITS) + " до " + std::to_string(MAX_CREDITS) + ".");
        }
        if (lectures < 0 || laboratories < 0 || practices < 0 || individual < 0) {
            throw std::invalid_argument("Количество часов не может быть отрицательным.");
        }
        int totalHours = lectures + laboratories + practices + individual;
        int expectedHours = credits * HOURS_PER_CREDIT;
        
        if (totalHours != expectedHours) {
            throw std::invalid_argument("Сумма часов (лекции + лабораторные + практики + индивидуальные) должна быть равна " + 
                                       std::to_string(expectedHours) + " (" + std::to_string(credits) + " ЗЕ * " + 
                                       std::to_string(HOURS_PER_CREDIT) + ")");
        }
    }

    std::string getName() const { return name; }
    int getCredits() const { return credits; }
    int getLectures() const { return lectures; }
    int getLaboratories() const { return laboratories; }
    int getPractices() const { return practices; }
    int getIndividual() const { return individual; }
    int getTotalHours() const { return credits * HOURS_PER_CREDIT; }
    AttestationType getAttestation() const { return attestation; }
    std::string getAttestationString() const { return attestationTypeToString(attestation); }

private:
    std::string name;           ///< Название дисциплины (символы)
    int credits;                ///< Количество зачётных единиц (ЗЕ, от 1 до 14)

    int lectures;               ///< Количество лекционных часов (ч)
    int laboratories;           ///< Количество лабораторных часов (ч)
    int practices;              ///< Количество практических часов (ч)
    int individual;             ///< Количество часов на индивидуальные занятия (ч)
    
    AttestationType attestation; ///< Тип аттестации (экзамен/зачёт)
};

#endif // DISCIPLINE_H